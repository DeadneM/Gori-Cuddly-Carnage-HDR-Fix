# Steam Community Guide Draft

## Gori: Cuddly Carnage - HDR Fix

This runtime fix repairs HDR in **Gori: Cuddly Carnage** without modifying the game executable.

It fixes Gori's incorrect HDR monitor state, enables Unreal Engine's native HDR path, applies the required live HDR renderer settings, and completes the HDR10 DXGI color-space state when Unreal enters HDR mode.

### Download

Download the latest release from the GitHub Releases page:

```text
Gori_Cuddly_Carnage_HDR_Fix_v2.0.0.zip
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

4. Launch the game normally through Steam.
5. Press **F10** to show or hide the HDR Control overlay.

No EXE patching, backup, or restore operation is required.

### HDR Control

The validated HDR10 runtime path uses:

```text
Enable HDR output   ON
Output device       3
Color gamut         2
Use HDR display     ON
Peak brightness     1000 nits by default
```

Peak brightness can be adjusted to suit your display.

The F10 overlay also shows live HDR pipeline telemetry.

### GPU support

The runtime uses the same HDR path for the three standard desktop GPU vendors:

```text
NVIDIA
AMD
Intel
```

### What the fix changes

At runtime the mod:

- corrects Gori's own HDR monitor-capability field;
- enables the native Unreal HDR path;
- sets the live Unreal HDR CVars;
- waits for Unreal/RHI to emit HDR10 metadata;
- completes the missing DXGI PQ / Rec.2020 color-space state when supported.

The game executable on disk is never modified.

### Supported Steam executable

```text
SHA-256:
2bcd42db186018c3553d3e75dca34891255a3a3e0de3e6e663201febbec5e1d1
```

If a future game update changes the executable, a new supported-build revision may be required.
