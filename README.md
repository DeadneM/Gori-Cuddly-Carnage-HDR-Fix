# Gori: Cuddly Carnage - HDR Fix

<p align="center">
  <img src="images/Image%20Codex%2025%20sept.%202026,%2012_19_19.png" alt="Gori: Cuddly Carnage HDR Fix" width="100%">
</p>

A runtime HDR fix for **Gori: Cuddly Carnage** on Windows.

The fix uses a small **DXGI proxy + ASI runtime module**. It repairs Gori's HDR detection, enables Unreal Engine's real HDR path, keeps the live HDR renderer CVars coherent, and provides an in-game **F10 HDR Control** overlay.

## Download

Use the latest package from the repository's **Releases** page.

**Current public version: v2.0.1**

v2.0.1 is the cleaned-up V17 runtime build. The HDR implementation is unchanged from the working universal V16 path, but automatic disk diagnostic logging has been removed.

The old EXE patcher is obsolete and is no longer used.

## Installation

1. Close Gori.
2. Download and extract `Gori_Cuddly_Carnage_HDR_Fix_v2.0.1.zip`.
3. Copy these two files next to `GoriCuddlyCarnage-Win64-Shipping.exe`:

```text
GoriHDRFix.asi
dxgi.dll
```

Typical folder:

```text
...\Gori Cuddly Carnage\GoriCuddlyCarnage\Binaries\Win64\
```

4. Launch Gori normally through Steam.
5. Press **F10** to open or hide the HDR Control overlay.

No game EXE is modified and no backup/restore step is required.

## No automatic log files

Starting with v2.0.1, launching the game no longer creates:

```text
GoriHDRFix.log
GoriHDRTrace.log
GoriHDRDXGI.log
```

Live HDR telemetry is still available directly in the F10 overlay.

If old log files from v2.0.0 or earlier are still present, they can be deleted once. v2.0.1 will not recreate them.

## What the fix does

### 1. Gori monitor-capability fix

The validated V4B discovery is preserved at runtime:

```text
GraphicSettings.DoesMonitorHaveHDRSupport
OptionsData + 0x115 = TRUE
```

### 2. Native Unreal HDR activation

When **Enable HDR output** is ON, the same runtime path is used for:

```text
NVIDIA  0x10DE
AMD     0x1002
Intel   0x8086
```

There is no vendor-specific Intel lock.

### 3. Live Unreal HDR CVars

The actual runtime console variables are set through Unreal's own CVar path:

```text
r.HDR.EnableHDROutput       = 1
r.HDR.Display.OutputDevice  = 3
r.HDR.Display.ColorGamut    = 2
```

This is the step that corrected the previously oversaturated HDR output.

### 4. DXGI HDR10 completion

The DXGI proxy does **not** blindly force HDR10 at startup.

It waits for Unreal/RHI to emit native HDR10 metadata, then checks DXGI support and completes the missing PQ / Rec.2020 color-space state only when required:

```text
Unreal/RHI SetHDRMetaData(HDR10)
        ↓
CheckColorSpaceSupport(PQ / Rec.2020)
        ↓
SetColorSpace1(PQ / Rec.2020)
```

## F10 HDR Control

Validated HDR10 defaults:

```text
Enable HDR output   ON
Output device       3
Color gamut         2
Use HDR display     ON
Peak brightness     1000 nits
```

Peak brightness can be adjusted for your display.

The overlay also reports the active swapchain format, HDR metadata state, color-space state, and runtime CVar values.

## Supported game build

Current runtime offsets are for this Steam x64 executable:

```text
GoriCuddlyCarnage-Win64-Shipping.exe
SHA-256:
2bcd42db186018c3553d3e75dca34891255a3a3e0de3e6e663201febbec5e1d1
```

## Checksums

Each release includes `SHA256SUMS.txt` generated from the exact published archive and binaries.

See [HASHES.md](HASHES.md) for the supported retail EXE hash and release notes.

## Technical history

See [Technical Notes](docs/TECHNICAL_NOTES.md) for the full reverse-engineering history from V4B through V17.

A ready-to-paste community guide is available in [Steam Guide](docs/STEAM_GUIDE.md).
