# Steam Community Guide Draft

## Gori: Cuddly Carnage - HDR Fix

This runtime fix repairs HDR in **Gori: Cuddly Carnage** without modifying the game executable.

### Download

Download the latest release:

```text
Gori_Cuddly_Carnage_HDR_Fix_v2.0.1.zip
```

The old EXE patcher is obsolete and is no longer used.

### Installation

1. Close Gori.
2. Extract the release archive.
3. Copy:

```text
GoriHDRFix.asi
dxgi.dll
```

next to:

```text
GoriCuddlyCarnage-Win64-Shipping.exe
```

Typical folder:

```text
...\Gori Cuddly Carnage\GoriCuddlyCarnage\Binaries\Win64\
```

4. Launch normally through Steam.
5. Press **F10** for the HDR Control overlay.

### No log-file clutter

v2.0.1 no longer creates the old diagnostic files:

```text
GoriHDRFix.log
GoriHDRTrace.log
GoriHDRDXGI.log
```

If those files remain from an older version, delete them once. They will not return with v2.0.1.

Live HDR telemetry is still visible in F10.

### HDR Control

Validated HDR10 runtime path:

```text
Enable HDR output   ON
Output device       3
Color gamut         2
Use HDR display     ON
Peak brightness     1000 nits by default
```

Peak brightness can be adjusted for your display.

### GPU support

The same runtime HDR path is used for:

```text
NVIDIA
AMD
Intel
```

### Supported Steam executable

```text
SHA-256:
2bcd42db186018c3553d3e75dca34891255a3a3e0de3e6e663201febbec5e1d1
```

The game EXE is never modified.
