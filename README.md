# Gori: Cuddly Carnage - HDR Monitor Detection Fix

A small Windows patch for **Gori: Cuddly Carnage** that fixes a case where the game incorrectly reports an HDR-capable display as unsupported, leaving the in-game HDR option greyed out.

The validated fix works at **Gori's own options-data layer**. It does **not** replace the renderer, inject a DLL, or force Unreal Engine's low-level DXGI/D3D12 HDR detection.

## Download

Use the latest package from the repository's **Releases** page.

Current public version: **v1.0.0**

## Installation

1. Enable **HDR in Windows before launching the game**.
2. Close Gori.
3. Extract `Gori_Cuddly_Carnage_HDR_Fix_v1.0.0.zip`.
4. Put `Gori_Cuddly_Carnage_HDR_Fix_Patcher.exe` either:
   - in the Gori game root folder, or
   - in `GoriCuddlyCarnage\Binaries\Win64\`
5. Run the patcher.
6. Choose **Apply HDR fix**.
7. Launch Gori normally through Steam.
8. Open **Graphics** and enable HDR.

The patcher automatically creates and verifies:

```text
GoriCuddlyCarnage-Win64-Shipping.exe.Backup
```

To undo the patch, run the patcher again and choose **Restore original EXE**.

## Supported game build

The patcher intentionally refuses unknown executables.

```text
Supported retail EXE SHA-256:
2bcd42db186018c3553d3e75dca34891255a3a3e0de3e6e663201febbec5e1d1

Expected patched EXE SHA-256:
eaf1f82889201c0751f256560220611eafcf0533c37a8e2013ab6c9caa028748
```

If a future game update changes the Shipping EXE, the patcher stops without modifying it.

## What the fix changes

Static analysis of this game build identified Gori's live HDR monitor-capability state as:

```text
GraphicSettings.DoesMonitorHaveHDRSupport
OptionsData + 0x115
```

The validated **V4B** patch redirects two existing game-side initialization calls through a tiny Win64-safe tail wrapper:

```asm
mov byte ptr [rcx+115h], 1
jmp 0x141A39450
```

This forces only Gori's saved/live monitor-support field to `true` after options data is created or loaded.

The fix does **not** modify:

- DXGI output enumeration
- D3D12RHI
- `GRHISupportsHDROutput`
- swapchain creation
- tone mapping
- resolution or fullscreen behavior

See [Technical Notes](docs/TECHNICAL_NOTES.md) for the full audit trail.

## Patcher commands

```text
--apply
--restore
--check
```

The interactive menu provides the same operations.

## Source

The patcher source is in [Source/gori_hdr_patcher.go](Source/gori_hdr_patcher.go).

No original game executable is distributed in this repository.

## Steam Guide

A ready-to-paste Steam Community Guide draft is available in [docs/STEAM_GUIDE.md](docs/STEAM_GUIDE.md).

## Status

- **V4B**: validated
- **v1.0.0 public patcher**: based on V4B
