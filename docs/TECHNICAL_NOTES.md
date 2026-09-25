# Technical Notes

## Validated base

The public fix is based on the **V4B** test build validated on the Steam x64 executable with SHA-256:

```text
2bcd42db186018c3553d3e75dca34891255a3a3e0de3e6e663201febbec5e1d1
```

The expected patched executable SHA-256 is:

```text
eaf1f82889201c0751f256560220611eafcf0533c37a8e2013ab6c9caa028748
```

## Problem

On affected systems, Gori displays the HDR row as unavailable and reports that the monitor does not support High Dynamic Range, even though Windows HDR and the display's HDR capability are working.

The investigation deliberately separated two different layers:

1. Unreal Engine / DXGI low-level HDR output detection.
2. Gori's own menu and saved graphics-option state.

The validated solution changes only the second layer.

## Live game field

Static analysis identified the game-side capability field:

```text
GraphicSettings.DoesMonitorHaveHDRSupport
```

The live `GraphicSettings` block is embedded in `OptionsData` at offset `+0xB0`, while `DoesMonitorHaveHDRSupport` is at `GraphicSettings + 0x65`.

Therefore:

```text
OptionsData + 0x115 = DoesMonitorHaveHDRSupport
```

V4B writes this byte to `1` immediately before Gori's normal initialization routine runs after options creation/load.

## V4B patch

### Original call sites redirected

```text
VA 0x141A6501D
File offset 0x1A6461D

Original:
E8 2E 44 FD FF

Patched:
E8 2F 14 00 00
```

```text
VA 0x141A66387
File offset 0x1A65987

Original:
E8 C4 30 FD FF

Patched:
E8 C5 00 00 00
```

### Tail wrapper

An existing INT3 padding region is used at:

```text
VA 0x141A66451
File offset 0x1A65A51
```

Original 12 bytes:

```text
CC CC CC CC CC CC CC CC CC CC CC CC
```

V4B:

```text
C6 81 15 01 00 00 01 E9 F3 2F FD FF
```

Equivalent logic:

```asm
mov byte ptr [rcx+115h], 1
jmp 0x141A39450
```

The **tail jump is intentional**. It preserves the caller's original Win64 stack and shadow-space layout, allowing the original routine to return directly to its original caller.

## Rejected branches

### V1 - rejected: Fatal Error

V1 forced Unreal's low-level D3D12RHI/DXGI HDR color-space verdict. This was too deep in the renderer. Unreal then continued down a path that expected valid low-level HDR state and crashed.

**Lesson:** do not falsify the renderer's physical HDR capability merely to unlock Gori's menu.

### V2 - rejected: no effect on menu

V2 forced the generic Blueprint-exposed `SupportsHDRDisplayOutput()` result.

Gori's HDR row remained greyed out, showing that its menu did not depend solely on that generic Unreal wrapper.

### V3 - rejected: no effect on menu

V3 forced `GraphicSettings.DoesMonitorHaveHDRSupport` during constructor paths.

The menu still reported the monitor as unsupported. Further analysis showed that loaded `OptionsData` could overwrite constructor-time values.

### V4 - rejected: Fatal Error

V4 correctly targeted the post-load value but used a nested Win64 `CALL` from the trampoline without allocating a fresh 32-byte shadow space.

The called function could overwrite the trampoline's return address.

### V4B - validated

V4B retained the post-load target but replaced the nested call with a **tail jump**.

This preserved the ABI correctly and unlocked the HDR option without touching the renderer.

## Scope intentionally left vanilla

The validated patch does not modify:

- DXGI output enumeration
- DXGI color-space detection
- D3D12RHI
- `GRHISupportsHDROutput`
- swapchain creation
- HDR tone mapping
- display resolution
- fullscreen handling

This narrow scope is deliberate.
