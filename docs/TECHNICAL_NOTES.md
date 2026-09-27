# Technical Notes

## Current canonical build

**v2.0.1 / V17 No-Logs Universal** is the current runtime HDR fix.

Supported Steam x64 executable:

```text
SHA-256:
2bcd42db186018c3553d3e75dca34891255a3a3e0de3e6e663201febbec5e1d1
```

The game executable remains untouched on disk.

## Original problem

Gori could report a working HDR display as unsupported and grey out its HDR option. Investigation showed that several independent layers had to agree:

1. Gori's own live monitor-capability field.
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

The current runtime mod preserves this validated behavior **in memory only**.

Historical V4B locations:

```text
VA 0x141A6501D / file 0x1A6461D
VA 0x141A66387 / file 0x1A65987
tail-wrapper cave VA 0x141A66451 / file 0x1A65A51
```

Historical wrapper:

```asm
mov byte ptr [rcx+115h], 1
jmp 0x141A39450
```

## Runtime architecture

```text
dxgi.dll
    ↓ loads real System32 DXGI
    ↓ loads GoriHDRFix.asi
    ↓ hooks the real Gori DXGI/D3D12 swapchain
    ↓ renders the F10 overlay through D3D11On12

GoriHDRFix.asi
    ↓ applies supported-build runtime fixes
    ↓ drives Unreal HDR runtime state
    ↓ reads/writes the HDR profile
```

The overlay is rendered inside the game backbuffer. It is not an external topmost Windows control window.

## Reverse-engineering progression

### V1: rejected, Fatal Error

A low-level D3D12RHI/DXGI capability verdict was falsified. Unreal continued down a renderer path whose low-level HDR state was not coherent and crashed.

### V2: rejected

The Blueprint-exposed `SupportsHDRDisplayOutput()` wrapper was forced true. The menu still did not behave correctly.

### V3: rejected

`DoesMonitorHaveHDRSupport` was changed only during construction. Loaded options could overwrite it.

### V4: rejected, Fatal Error

The correct live field was found, but the first trampoline broke Win64 shadow-space rules.

### V4B: validated

The post-load write was retained with a Win64-safe tail jump. This became the stable Gori-side monitor-capability fix.

### V5 / V6B: overlay and diagnostics validated

A true DXGI/D3D12 in-game overlay was implemented. Mouse input and fullscreen/windowed swapchain rebuilding were stabilized.

Telemetry showed:

```text
Swapchain: R10G10B10A2_UNORM
initially no SetColorSpace1 observed
initially no SetHDRMetaData observed
```

### V7 / V8: rejected output, useful proof

Forcing PQ / Rec.2020 directly at DXGI activated HDR, but the image became severely oversaturated.

This proved that the hardware/DXGI path could present HDR10, while also proving that the renderer had to be configured coherently first.

### V11: native function trace

The real `UGameUserSettings::EnableHDRDisplayOutput()` path was traced. Gori repeatedly reached it while initially passing:

```text
bEnable = 0
DisplayNits = 1000
bFromUserSettings = 1
```

### V13: native HDR path reaches metadata

After correcting the UE/RHI runtime state, Unreal began emitting:

```text
SetHDRMetaData(HDR10)
```

but no matching PQ / Rec.2020 `SetColorSpace1` call was observed.

### V14: conditional DXGI colorspace completion

The proxy completed the missing color-space transition only **after** Unreal itself successfully emitted HDR10 metadata.

The DXGI state was now coherent, but the rendered image was still oversaturated.

### V15: working HDR output

The remaining issue was the live Unreal renderer state. INI values alone did not prove the active renderer CVars had changed.

V15 set Unreal's actual runtime CVar objects through the engine's own setter:

```text
r.HDR.EnableHDROutput       = 1
r.HDR.Display.OutputDevice  = 3
r.HDR.Display.ColorGamut    = 2
```

This corrected the HDR image.

### V16: universal NVIDIA / AMD / Intel

The temporary Intel-only diagnostic guard was removed.

The same runtime path recognizes:

```text
NVIDIA  0x10DE
AMD     0x1002
Intel   0x8086
```

### V17 / v2.0.1: no disk logging

V17 keeps the working V16 HDR path unchanged and removes automatic diagnostic files.

The runtime no longer creates:

```text
GoriHDRFix.log
GoriHDRTrace.log
GoriHDRDXGI.log
```

F10 live telemetry remains available in memory and on screen.

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

## Runtime values and important RVAs

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
- HDR10 color-space completion requires a successful native Unreal HDR10 metadata event.
- DXGI `CheckColorSpaceSupport` must report PRESENT support before PQ / Rec.2020 is applied.
- The old EXE patcher and patched-EXE distribution are retired.
- V17 performs no automatic diagnostic file logging.
