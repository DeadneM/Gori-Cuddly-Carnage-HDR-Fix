# Gori: Cuddly Carnage HDR Fix v2.0.1

Cleanup release based on the working universal runtime HDR implementation.

## Changed

Automatic disk diagnostic logging has been removed.

The game folder will no longer receive:

```text
GoriHDRFix.log
GoriHDRTrace.log
GoriHDRDXGI.log
```

Live telemetry remains available in the F10 overlay.

## Unchanged

The validated HDR path remains the same as v2.0.0 / V16:

- Gori V4B monitor-capability correction in memory;
- NVIDIA / AMD / Intel universal runtime path;
- native Unreal HDR activation;
- live Unreal HDR CVars set to Enable=1, OutputDevice=3, ColorGamut=2;
- Unreal-generated HDR10 metadata;
- conditional DXGI PQ / Rec.2020 color-space completion;
- F10 HDR Control;
- mouse input and fullscreen/windowed handling;
- original game EXE untouched.

## Installation

Copy `GoriHDRFix.asi` and `dxgi.dll` beside `GoriCuddlyCarnage-Win64-Shipping.exe`.

Press **F10** for HDR Control.

## Supported Steam EXE

```text
SHA-256:
2bcd42db186018c3553d3e75dca34891255a3a3e0de3e6e663201febbec5e1d1
```
