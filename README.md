# Gori: Cuddly Carnage - HDR Fix

<p align="center">
  <img src="images/Image%20Codex%2025%20sept.%202026,%2012_19_19.png" alt="Gori: Cuddly Carnage HDR Fix" width="100%">
</p>

A runtime HDR fix for **Gori: Cuddly Carnage** on Windows.

The current version no longer patches the game executable. It uses a small **DXGI proxy + ASI runtime module** to repair Gori's HDR detection, enable Unreal Engine's real HDR path, keep the live HDR renderer CVars coherent, and expose an in-game **F10 HDR Control** overlay.

## Download

Use the latest package from the repository's **Releases** page.

**Current public version: v2.0.0**

The old v1.0.0 EXE patcher is obsolete and has been removed from the current distribution.

## Installation

1. Close Gori.
2. Download and extract `Gori_Cuddly_Carnage_HDR_Fix_v2.0.0.zip`.
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

## What the fix does

The runtime fix combines several validated pieces.

### 1. Gori monitor-capability fix

The original V4B discovery is preserved at runtime:

```text
GraphicSettings.DoesMonitorHaveHDRSupport
OptionsData + 0x115 = TRUE
```

This removes the incorrect game-side "HDR unsupported" state.

### 2. Native Unreal HDR activation

When the mod's **Enable HDR output** setting is ON, the runtime path is enabled for the standard desktop GPU vendors:

```text
NVIDIA  0x10DE
AMD     0x1002
Intel   0x8086
```

The same HDR path is used for all three vendors. There is no Intel-only lock in v2.0.0.

### 3. Live Unreal HDR CVars

The fix sets the actual runtime console variables through Unreal's own CVar path:

```text
r.HDR.EnableHDROutput       = 1
r.HDR.Display.OutputDevice  = 3
r.HDR.Display.ColorGamut    = 2
```

This was the key step that corrected the previously oversaturated HDR output.

### 4. DXGI HDR10 completion

The DXGI proxy does **not** blindly force HDR10 at startup.

It waits for Unreal/RHI to emit native HDR10 metadata first. Only then it checks DXGI support and completes the missing PQ / Rec.2020 color-space state when required:

```text
Unreal/RHI SetHDRMetaData(HDR10)
        ↓
CheckColorSpaceSupport(PQ / Rec.2020)
        ↓
SetColorSpace1(PQ / Rec.2020)
```

This avoids the incorrect V7/V8 behavior where PQ was forced before Unreal's tonemapper was actually configured for HDR.

## F10 HDR Control

The in-game overlay exposes the HDR settings and live pipeline telemetry.

Validated HDR10 defaults:

```text
Enable HDR output   ON
Output device       3
Color gamut         2
Use HDR display     ON
Peak brightness     1000 nits
```

Peak brightness can be adjusted for your display.

The telemetry also reports the active swapchain format, HDR metadata state, color-space state, and runtime CVar values.

## Supported game build

Current runtime offsets are for this Steam x64 executable:

```text
GoriCuddlyCarnage-Win64-Shipping.exe
SHA-256:
2bcd42db186018c3553d3e75dca34891255a3a3e0de3e6e663201febbec5e1d1
```

The runtime patch validates the expected code/data before applying the supported-build hooks.

## Release hashes

```text
GoriHDRFix.asi
c2817878995a439f3fe625a5af08e513808a32ef06b931914e057f820db4cbeb

dxgi.dll
46c5df2926d2ba2d1f35a3f35d1beeed22e0bab9557d069556bd061c157acc0b

Gori_Cuddly_Carnage_HDR_Fix_v2.0.0.zip
2ef4c8abf2fca83511632d4482abe174a59c1268646b56dac5e0687f254e0b94
```

The release archive also contains the exact V16 runtime source used for the public build.

## Technical history

See [Technical Notes](docs/TECHNICAL_NOTES.md) for the reverse-engineering history from the original V4B monitor fix through the working runtime HDR pipeline.

A ready-to-paste community guide is available in [Steam Guide](docs/STEAM_GUIDE.md).
