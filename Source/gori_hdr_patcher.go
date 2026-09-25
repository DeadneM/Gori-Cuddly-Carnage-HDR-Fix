package main

import (
	"bufio"
	"crypto/sha256"
	"encoding/hex"
	"errors"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
)

const (
	exeName     = "GoriCuddlyCarnage-Win64-Shipping.exe"
	backupName  = "GoriCuddlyCarnage-Win64-Shipping.exe.Backup"
	originalSHA = "2bcd42db186018c3553d3e75dca34891255a3a3e0de3e6e663201febbec5e1d1"
	patchedSHA  = "eaf1f82889201c0751f256560220611eafcf0533c37a8e2013ab6c9caa028748"
)

type patch struct {
	offset int64
	before []byte
	after  []byte
	label  string
}

var patches = []patch{
	{
		offset: 0x1A6461D,
		before: []byte{0xE8, 0x2E, 0x44, 0xFD, 0xFF},
		after:  []byte{0xE8, 0x2F, 0x14, 0x00, 0x00},
		label:  "OptionsData default/init path",
	},
	{
		offset: 0x1A65987,
		before: []byte{0xE8, 0xC4, 0x30, 0xFD, 0xFF},
		after:  []byte{0xE8, 0xC5, 0x00, 0x00, 0x00},
		label:  "OptionsData post-load path",
	},
	{
		offset: 0x1A65A51,
		before: []byte{0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC},
		after:  []byte{0xC6, 0x81, 0x15, 0x01, 0x00, 0x00, 0x01, 0xE9, 0xF3, 0x2F, 0xFD, 0xFF},
		label:  "HDR support tail-wrapper",
	},
}

func sha256File(path string) (string, error) {
	f, err := os.Open(path)
	if err != nil {
		return "", err
	}
	defer f.Close()
	h := sha256.New()
	if _, err := io.Copy(h, f); err != nil {
		return "", err
	}
	return hex.EncodeToString(h.Sum(nil)), nil
}

func copyFile(src, dst string) error {
	in, err := os.Open(src)
	if err != nil {
		return err
	}
	defer in.Close()

	st, err := in.Stat()
	if err != nil {
		return err
	}

	out, err := os.OpenFile(dst, os.O_WRONLY|os.O_CREATE|os.O_TRUNC, st.Mode())
	if err != nil {
		return err
	}
	ok := false
	defer func() {
		out.Close()
		if !ok {
			_ = os.Remove(dst)
		}
	}()

	if _, err := io.Copy(out, in); err != nil {
		return err
	}
	if err := out.Sync(); err != nil {
		return err
	}
	if err := out.Close(); err != nil {
		return err
	}
	ok = true
	return nil
}

func uniqueCandidates() []string {
	seen := map[string]bool{}
	var out []string
	add := func(p string) {
		p = filepath.Clean(p)
		if !seen[strings.ToLower(p)] {
			seen[strings.ToLower(p)] = true
			out = append(out, p)
		}
	}

	wd, _ := os.Getwd()
	self, _ := os.Executable()
	selfDir := filepath.Dir(self)

	roots := []string{wd, selfDir}
	for _, r := range roots {
		add(filepath.Join(r, exeName))
		add(filepath.Join(r, "GoriCuddlyCarnage", "Binaries", "Win64", exeName))
		add(filepath.Join(r, "Binaries", "Win64", exeName))
	}
	return out
}

func findTarget() (string, error) {
	for _, p := range uniqueCandidates() {
		if st, err := os.Stat(p); err == nil && !st.IsDir() {
			return p, nil
		}
	}
	return "", errors.New("game EXE not found automatically")
}

func verifyPatchBytes(data []byte, useAfter bool) error {
	for _, p := range patches {
		want := p.before
		if useAfter {
			want = p.after
		}
		end := p.offset + int64(len(want))
		if p.offset < 0 || end > int64(len(data)) {
			return fmt.Errorf("%s: patch offset outside file", p.label)
		}
		got := data[p.offset:end]
		if !equal(got, want) {
			return fmt.Errorf("%s: unexpected bytes at 0x%X", p.label, p.offset)
		}
	}
	return nil
}

func equal(a, b []byte) bool {
	if len(a) != len(b) {
		return false
	}
	for i := range a {
		if a[i] != b[i] {
			return false
		}
	}
	return true
}

func apply(target string) error {
	sum, err := sha256File(target)
	if err != nil {
		return err
	}
	if sum == patchedSHA {
		fmt.Println("[OK] HDR fix is already installed.")
		return nil
	}
	if sum != originalSHA {
		return fmt.Errorf("unsupported EXE\nExpected original SHA-256: %s\nFound: %s", originalSHA, sum)
	}

	data, err := os.ReadFile(target)
	if err != nil {
		return err
	}
	if err := verifyPatchBytes(data, false); err != nil {
		return err
	}

	backup := filepath.Join(filepath.Dir(target), backupName)
	if _, err := os.Stat(backup); err == nil {
		bsum, herr := sha256File(backup)
		if herr != nil {
			return herr
		}
		if bsum != originalSHA {
			return fmt.Errorf("backup already exists but is not the expected original EXE: %s", backup)
		}
		fmt.Println("[OK] Existing verified backup found.")
	} else if os.IsNotExist(err) {
		fmt.Println("[ .. ] Creating backup...")
		if err := copyFile(target, backup); err != nil {
			return fmt.Errorf("backup failed: %w", err)
		}
		bsum, err := sha256File(backup)
		if err != nil || bsum != originalSHA {
			return errors.New("backup verification failed")
		}
		fmt.Println("[OK] Backup created and verified.")
	} else {
		return err
	}

	patched := append([]byte(nil), data...)
	for _, p := range patches {
		copy(patched[p.offset:p.offset+int64(len(p.after))], p.after)
	}

	h := sha256.Sum256(patched)
	outsum := hex.EncodeToString(h[:])
	if outsum != patchedSHA {
		return fmt.Errorf("internal verification failed: generated SHA-256 %s", outsum)
	}

	temp := target + ".hdrfix.tmp"
	if err := os.WriteFile(temp, patched, 0755); err != nil {
		return err
	}
	tsum, err := sha256File(temp)
	if err != nil || tsum != patchedSHA {
		_ = os.Remove(temp)
		return errors.New("temporary patched EXE verification failed")
	}

	swap := target + ".hdrfix.swap"
	_ = os.Remove(swap)
	if err := os.Rename(target, swap); err != nil {
		_ = os.Remove(temp)
		return fmt.Errorf("cannot move original EXE out of the way: %w", err)
	}
	if err := os.Rename(temp, target); err != nil {
		_ = os.Rename(swap, target)
		_ = os.Remove(temp)
		return fmt.Errorf("cannot install patched EXE: %w", err)
	}
	_ = os.Remove(swap)

	final, err := sha256File(target)
	if err != nil || final != patchedSHA {
		return errors.New("final patched EXE verification failed")
	}

	fmt.Println("[OK] HDR monitor capability fix installed.")
	fmt.Println("[OK] Patched EXE SHA-256:", final)
	return nil
}

func restore(target string) error {
	sum, err := sha256File(target)
	if err != nil {
		return err
	}
	if sum == originalSHA {
		fmt.Println("[OK] Retail EXE is already restored.")
		return nil
	}
	if sum != patchedSHA {
		return fmt.Errorf("current EXE is neither the supported retail build nor this HDR patch\nFound SHA-256: %s", sum)
	}

	backup := filepath.Join(filepath.Dir(target), backupName)
	bsum, err := sha256File(backup)
	if err != nil {
		return fmt.Errorf("verified backup not found: %w", err)
	}
	if bsum != originalSHA {
		return fmt.Errorf("backup hash mismatch; refusing to restore\nFound backup SHA-256: %s", bsum)
	}

	temp := target + ".restore.tmp"
	if err := copyFile(backup, temp); err != nil {
		return err
	}
	tsum, err := sha256File(temp)
	if err != nil || tsum != originalSHA {
		_ = os.Remove(temp)
		return errors.New("temporary restore verification failed")
	}

	swap := target + ".restore.swap"
	_ = os.Remove(swap)
	if err := os.Rename(target, swap); err != nil {
		_ = os.Remove(temp)
		return err
	}
	if err := os.Rename(temp, target); err != nil {
		_ = os.Rename(swap, target)
		_ = os.Remove(temp)
		return err
	}
	_ = os.Remove(swap)

	fmt.Println("[OK] Original retail EXE restored from verified backup.")
	return nil
}

func check(target string) error {
	sum, err := sha256File(target)
	if err != nil {
		return err
	}
	fmt.Println("EXE:", target)
	fmt.Println("SHA-256:", sum)
	switch sum {
	case originalSHA:
		fmt.Println("Status: supported retail build, HDR fix not installed")
	case patchedSHA:
		fmt.Println("Status: HDR fix installed and verified")
	default:
		fmt.Println("Status: unknown/unsupported build")
	}
	return nil
}

func pause() {
	fmt.Print("\nPress Enter to close...")
	_, _ = bufio.NewReader(os.Stdin).ReadString('\n')
}

func main() {
	fmt.Println("============================================================")
	fmt.Println("Gori: Cuddly Carnage - HDR Monitor Capability Fix Patcher")
	fmt.Println("Validated patch: V4B | Steam x64")
	fmt.Println("============================================================")
	fmt.Println()

	target, err := findTarget()
	if err != nil {
		fmt.Println("[ERROR]", err)
		fmt.Println("Place this patcher either in the game root or in:")
		fmt.Println(`GoriCuddlyCarnage\Binaries\Win64\`)
		pause()
		os.Exit(1)
	}
	fmt.Println("[OK] Game EXE:", target)

	args := os.Args[1:]
	if len(args) > 0 {
		var actionErr error
		switch strings.ToLower(args[0]) {
		case "--apply", "/apply":
			actionErr = apply(target)
		case "--restore", "/restore":
			actionErr = restore(target)
		case "--check", "/check":
			actionErr = check(target)
		default:
			actionErr = errors.New("unknown argument; use --apply, --restore or --check")
		}
		if actionErr != nil {
			fmt.Println("[ERROR]", actionErr)
			pause()
			os.Exit(1)
		}
		pause()
		return
	}

	reader := bufio.NewReader(os.Stdin)
	for {
		fmt.Println()
		fmt.Println("1) Apply HDR fix")
		fmt.Println("2) Restore original EXE")
		fmt.Println("3) Check status")
		fmt.Println("4) Exit")
		fmt.Print("> ")
		s, _ := reader.ReadString('\n')
		s = strings.TrimSpace(s)

		switch s {
		case "1":
			if err := apply(target); err != nil {
				fmt.Println("[ERROR]", err)
			}
		case "2":
			if err := restore(target); err != nil {
				fmt.Println("[ERROR]", err)
			}
		case "3":
			if err := check(target); err != nil {
				fmt.Println("[ERROR]", err)
			}
		case "4":
			return
		default:
			fmt.Println("Choose 1, 2, 3 or 4.")
		}
	}
}
