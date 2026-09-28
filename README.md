# Gori: Cuddly Carnage - HDR Fix

<p align="center">
  <img src="images/Image%20Codex%2025%20sept.%202026,%2012_19_19.png" alt="Gori: Cuddly Carnage HDR Fix" width="100%">
</p>

A runtime HDR fix for **Gori: Cuddly Carnage** on Windows.

## Current release

**v2.0.2 / V20**

This is the current validated build.

It fixes Gori's HDR path without modifying the game executable and now includes:

- working HDR activation;
- NVIDIA / AMD / Intel support;
- synchronization with Gori's own HDR ON/OFF setting;
- a working F10 HDR control overlay;
- persistent mod settings through `GoriHDRFix.ini`;
- improved multi-monitor handling;
- no diagnostic log files.

## Download

Use the latest package from the repository's **Releases** page.

The public archive contains only:

```text
GoriHDRFix.asi
dxgi.dll
README.txt
```

Source code is kept in the repository under `Source/` and is intentionally not included in the release ZIP.

## Installation

Copy:

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
...\Steam\steamapps\common\Gori Cuddly Carnage\GoriCuddlyCarnage\Binaries\Win64\
```

Launch the game normally through Steam.

Press **F10** to open or close HDR Control.

No external ASI loader is required: the included `dxgi.dll` proxy loads `GoriHDRFix.asi`.

## HDR Control

Recommended HDR10 defaults:

```text
Enable HDR output   ON
Output device       3
Color gamut         2
Use HDR display     ON
Peak brightness     1000 nits
```

Peak brightness can be adjusted for your display.

Changes made from the mod menu are saved to:

```text
GoriHDRFix.ini
```

beside the ASI and restored at the next launch.

Gori's own HDR ON/OFF setting is also followed by the runtime fix.

## Multi-monitor behavior

The current build checks the output actually containing the game swapchain instead of assuming HDR capability from the GPU alone.

A known SDR output suspends HDR output, while a valid HDR output can use the normal HDR10 path. Moving or resizing the game causes the output state to be checked again.

## GPU support

```text
NVIDIA
AMD
Intel
```

## Supported Steam executable

```text
GoriCuddlyCarnage-Win64-Shipping.exe
SHA-256:
2bcd42db186018c3553d3e75dca34891255a3a3e0de3e6e663201febbec5e1d1
```

## Uninstallation

Delete:

```text
GoriHDRFix.asi
dxgi.dll
GoriHDRFix.ini
```

The original game executable is never modified.

## Technical information

See [Technical Notes](docs/TECHNICAL_NOTES.md).

A simple Steam Community guide draft is available in [Steam Guide](docs/STEAM_GUIDE.md).
