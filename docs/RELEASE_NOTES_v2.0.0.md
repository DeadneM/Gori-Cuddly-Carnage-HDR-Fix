# Gori: Cuddly Carnage HDR Fix v2.0.0

Major runtime HDR release.

## What changed

The old EXE patcher has been retired.

v2.0.0 installs as a **DXGI proxy + ASI runtime fix** beside the game's Shipping EXE and does not modify the executable on disk.

The current runtime path:

- preserves the validated V4B Gori monitor-capability correction;
- enables Unreal Engine's native HDR path;
- sets the actual live Unreal HDR CVars to the validated HDR10 configuration;
- supports NVIDIA, AMD and Intel through the same runtime path;
- waits for Unreal/RHI to emit native HDR10 metadata;
- completes the missing DXGI PQ / Rec.2020 color-space state only when supported;
- provides an in-game F10 HDR Control and live telemetry overlay.

## Validated HDR runtime values

```text
r.HDR.EnableHDROutput       = 1
r.HDR.Display.OutputDevice  = 3
r.HDR.Display.ColorGamut    = 2
```

## Installation

Copy:

```text
GoriHDRFix.asi
dxgi.dll
```

next to `GoriCuddlyCarnage-Win64-Shipping.exe`, then launch through Steam.

Press **F10** for the HDR Control overlay.

## Supported game build

```text
Steam x64 EXE SHA-256:
2bcd42db186018c3553d3e75dca34891255a3a3e0de3e6e663201febbec5e1d1
```

## Release package SHA-256

```text
2ef4c8abf2fca83511632d4482abe174a59c1268646b56dac5e0687f254e0b94
```
