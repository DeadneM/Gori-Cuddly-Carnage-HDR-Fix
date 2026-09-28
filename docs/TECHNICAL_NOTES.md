# Technical Notes

## Current canonical build

**v2.0.2 / V20** is the current validated runtime HDR fix.

Supported Steam x64 executable:

```text
SHA-256:
2bcd42db186018c3553d3e75dca34891255a3a3e0de3e6e663201febbec5e1d1
```

The original game executable remains untouched on disk.

## Core HDR path

The validated runtime chain remains:

```text
Gori monitor capability corrected
        ↓
native Unreal HDR path
        ↓
live HDR CVars
        ↓
native HDR10 metadata
        ↓
conditional DXGI PQ / Rec.2020 completion
        ↓
HDR10 output
```

Validated runtime values when HDR is enabled:

```text
r.HDR.EnableHDROutput       = 1
r.HDR.Display.OutputDevice  = 3
r.HDR.Display.ColorGamut    = 2
```

## V4B foundation

The original game-side monitor capability discovery remains part of the runtime behavior:

```text
GraphicSettings.DoesMonitorHaveHDRSupport
OptionsData + 0x115
```

The old historical EXE patcher is retired. V20 applies the equivalent correction in memory only.

## V15 / V16 foundation

V15 established the working live Unreal HDR CVar path.

V16 removed the temporary Intel-only diagnostic restriction and applied the same supported runtime path to:

```text
NVIDIA  0x10DE
AMD     0x1002
Intel   0x8086
```

## V17

Removed automatic diagnostic disk logging.

The mod no longer creates:

```text
GoriHDRFix.log
GoriHDRTrace.log
GoriHDRDXGI.log
```

F10 live telemetry remains available.

## V18 / V19 investigation

V18 introduced persistence and output-aware multi-monitor logic but exposed a startup deadlock: an output that had not yet been positively identified could be treated as SDR early enough to prevent Unreal from entering HDR.

V19 removed that bootstrap deadlock and improved the swapchain/output checks, but two issues remained during testing:

- Gori's own HDR ON/OFF setting was not reliably reflected by the mod;
- saved settings could still be lost after restarting the game.

## V20 validated fixes

V20 resolves both remaining issues.

### Native Gori HDR setting synchronization

The runtime now follows Gori's actual live HDR preference from the game's user settings rather than relying only on a pre-gated function argument.

Relevant live field:

```text
UGameUserSettings + 0x10C
```

Changing HDR in Gori's own graphics menu now updates the runtime HDR state.

Changing HDR from F10 also mirrors the state back into the live user settings.

### Persistent mod profile

The mod profile is stored beside the ASI:

```text
GoriHDRFix.ini
```

The saved profile is loaded before normal runtime HDR forcing takes over, preventing startup defaults from overwriting the user's saved F10 values.

### Multi-monitor handling

The DXGI proxy identifies the output containing the game swapchain and cross-checks it against the game window monitor.

Behavior:

```text
unknown output  → allow HDR bootstrap, do not blindly force PQ
known SDR       → suspend effective HDR
known HDR       → allow validated HDR10 completion
```

Output state is re-evaluated after relevant window, resize and fullscreen transitions.

The user's requested HDR preference is kept separate from temporary display eligibility, so passing through an SDR output does not erase the stored HDR preference.

## Runtime architecture

```text
dxgi.dll
    ↓ loads the real System32 DXGI
    ↓ loads GoriHDRFix.asi
    ↓ observes/hooks the D3D12 swapchain
    ↓ renders the F10 overlay

GoriHDRFix.asi
    ↓ supported-build runtime hooks
    ↓ Gori HDR preference synchronization
    ↓ persistent GoriHDRFix.ini profile
    ↓ Unreal HDR runtime state
```

No separate ASI loader is required.

## Distribution model

Public release ZIPs intentionally contain only:

```text
GoriHDRFix.asi
dxgi.dll
README.txt
```

Source code is maintained in the repository under `Source/`, not duplicated inside the distributed ZIP.

## Important supported-build RVAs

```text
GPU vendor runtime state          RVA 0x065148E4
GRHISupportsHDROutput             RVA 0x06514A15

r.HDR.Display.ColorGamut CVar*    RVA 0x0651A3D0
r.HDR.Display.OutputDevice CVar*  RVA 0x0651A3E8
r.HDR.EnableHDROutput CVar*       RVA 0x0651A460

UE integer CVar setter            RVA 0x00AB6EB0
```

These addresses are for the supported Steam build only.
