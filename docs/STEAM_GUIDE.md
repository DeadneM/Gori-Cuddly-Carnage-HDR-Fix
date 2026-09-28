# Gori: Cuddly Carnage - HDR Fix

This mod fixes HDR support in **Gori: Cuddly Carnage** on PC.

It restores proper HDR output and adds a small in-game HDR control menu.

## Features

- Fixes HDR detection
- Enables HDR properly in-game
- Supports NVIDIA, AMD and Intel GPUs
- Includes an in-game HDR menu
- Remembers your HDR settings
- Improved support for multiple monitors
- Does not modify the game executable
- No log files are created
- Easy installation

## Download

Download the latest release from GitHub:

https://github.com/DeadneM/Gori-Cuddly-Carnage-HDR-Fix/releases/latest

## Installation

Extract the archive and copy:

```text
GoriHDRFix.asi
dxgi.dll
```

into the folder containing:

```text
GoriCuddlyCarnage-Win64-Shipping.exe
```

Usually:

```text
...\Steam\steamapps\common\Gori Cuddly Carnage\GoriCuddlyCarnage\Binaries\Win64\
```

Then launch the game normally through Steam.

No additional ASI loader is required.

## HDR Menu

Press:

```text
F10
```

to open or close HDR Control.

Recommended settings:

```text
Enable HDR output   ON
Output device       3
Color gamut         2
Use HDR display     ON
Peak brightness     1000 nits
```

You can adjust peak brightness for your monitor or TV.

Your mod settings are remembered after restarting the game.

Gori's own HDR ON/OFF option also works with the fix.

## Uninstallation

Delete:

```text
GoriHDRFix.asi
dxgi.dll
GoriHDRFix.ini
```

The original game files are not modified.

## Notes

Make sure HDR is enabled in Windows and on your display.

The current build also handles systems with multiple monitors more safely than older versions.

## Source Code

https://github.com/DeadneM/Gori-Cuddly-Carnage-HDR-Fix
