# Technical Notes

## Current canonical build

**v2.0.0 / V16 Universal** is the current runtime HDR fix.

Supported Steam x64 executable:

```text
SHA-256:
2bcd42db186018c3553d3e75dca34891255a3a3e0de3e6e663201febbec5e1d1
```

The old EXE patcher is obsolete. The current fix leaves the game executable untouched on disk.

## Original problem

Gori could report a working HDR display as unsupported and grey out its HDR option. Investigation eventually showed that the problem was not one single switch. Several independent layers had to agree:

1. Gori's own saved/live monitor-capability field.
2. Unreal's native HDR enable path.
3. The live renderer HDR CVars.
4. The DXGI swapchain HDR metadata/color-space state.

## V4B: validated Gori monitor-capability fix

Static analysis identified:

```text
GraphicSettings.DoesMonitorHaveHDRSupport
GraphicSettings offset in OptionsData = +0xB0
DoesMonitorHaveHDRSupport             = +0x65

OptionsData + 0x115
```

The original V4B disk patch set this byte to `1` after options creation/load through a Win64-safe tail wrapper.

The runtime mod preserves the same validated behavior **in memory only**. The EXE is no longer patched on disk.

### Historical V4B locations

```text
VA 0x141A6501D / file 0x1A6461D
VA 0x141A66387 / file 0x1A65987
tail-wrapper cave VA 0x141A66451 / file 0x1A65A51
```

Historical wrapper logic:

```asm
mov byte ptr [rcx+115h], 1
jmp 0x141A39450
```

## Runtime overlay architecture

The current mod consists of:

```text
dxgi.dll
    ↓ loads real System32 DXGI
    ↓ loads GoriHDRFix.asi
    ↓ observes/hooks Gori's DXGI/D3D12 swapchain
    ↓ renders F10 overlay through D3D11On12

GoriHDRFix.asi
    ↓ applies supported-build runtime fixes
    ↓ drives Unreal HDR runtime state
    ↓ reads/writes HDR profile values
```

The overlay is rendered inside the game backbuffer. It is not an external topmost Win32 control window.

## Reverse-engineering progression

### V1: rejected, Fatal Error

A low-level D3D12RHI/DXGI capability verdict was falsified. Unreal continued down a renderer path whose low-level HDR state was not actually coherent and crashed.

**Lesson:** do not lie to the deepest physical HDR check just to unlock the UI.

### V2: rejected, no menu effect

The Blueprint-exposed `SupportsHDRDisplayOutput()` wrapper was forced true. Gori's menu remained locked.

### V3: rejected, no menu effect

`DoesMonitorHaveHDRSupport` was changed only during construction. Loaded options could overwrite it.

### V4: rejected, Fatal Error

The correct post-load field was found, but the first trampoline used a nested Win64 `CALL` without a fresh shadow-space frame.

### V4B: validated

The post-load write was retained and the trampoline changed to a tail jump. This became the stable monitor-detection fix.

### V5 / V6B: overlay and diagnostics validated

A true DXGI/D3D12 in-game overlay was implemented. Input handling and fullscreen/windowed swapchain rebuilds were fixed.

Telemetry then proved:

```text
Swapchain: R10G10B10A2_UNORM
Gori initially: no SetColorSpace1 observed
Gori initially: no SetHDRMetaData observed
```

### V7 / V8: rejected output, useful proof

Forcing the swapchain directly to HDR10 PQ / Rec.2020 successfully activated HDR output, but colors became severely oversaturated.

This proved the display and DXGI path could present HDR10, while also proving that **forcing only the final DXGI color space was insufficient**.

### V11: native function trace

The real `UGameUserSettings::EnableHDRDisplayOutput()` path was traced. Gori repeatedly reached the function but initially supplied:

```text
bEnable = 0
DisplayNits = 1000
bFromUserSettings = 1
```

This moved the investigation from speculation to the actual engine call path.

### V13: native HDR path reaches metadata

After correcting the runtime UE/RHI enable state, Unreal began emitting:

```text
SetHDRMetaData(HDR10)
```

but no matching `SetColorSpace1(PQ / Rec.2020)` was observed.

### V14: DXGI color-space completion

The proxy began completing the missing color-space transition only **after** Unreal itself successfully emitted HDR10 metadata.

That established a coherent DXGI HDR10 state, but the rendered image was still oversaturated.

### V15: working HDR output

The remaining issue was the live Unreal renderer state. INI values did not prove the active runtime CVars had actually changed.

V15 set Unreal's actual runtime CVar objects through the engine's own setter:

```text
r.HDR.EnableHDROutput       = 1
r.HDR.Display.OutputDevice  = 3
r.HDR.Display.ColorGamut    = 2
```

This corrected the HDR image.

### V16: universal NVIDIA / AMD / Intel path

The temporary Intel-only diagnostic guard was removed.

The same runtime path now recognizes:

```text
NVIDIA  0x10DE
AMD     0x1002
Intel   0x8086
```

When the mod's HDR output toggle is ON, the runtime enables the native UE HDR path and the validated live CVars for all three vendors.

## Current HDR pipeline

```text
Gori monitor-capability field corrected
        ↓
native UE HDR enable path
        ↓
live Unreal HDR CVars = 1 / 3 / 2
        ↓
Unreal/RHI emits HDR10 metadata
        ↓
DXGI checks PQ / Rec.2020 PRESENT support
        ↓
missing SetColorSpace1 completed if required
        ↓
HDR10 output
```

The proxy does not generate fake HDR metadata. Unreal must enter its own native HDR path first.

## Runtime values and important RVAs

Retail build values used by the current V16 branch include:

```text
GPU vendor runtime state          RVA 0x065148E4
GRHISupportsHDROutput             RVA 0x06514A15

r.HDR.Display.ColorGamut CVar*    RVA 0x0651A3D0
r.HDR.Display.OutputDevice CVar*  RVA 0x0651A3E8
r.HDR.EnableHDROutput CVar*       RVA 0x0651A460

UE integer CVar setter            RVA 0x00AB6EB0
```

These are supported-build addresses, not universal UE5 offsets.

## Safety model

- The original game EXE is not modified.
- Runtime byte hooks validate the expected supported-build bytes before applying.
- HDR10 color-space completion is conditional on a successful native Unreal HDR10 metadata event.
- DXGI `CheckColorSpaceSupport` must report PRESENT support before PQ / Rec.2020 is applied.
- The old EXE patcher and patched-EXE distribution are retired.
