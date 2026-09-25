# Steam Community Guide Draft

## Gori: Cuddly Carnage - HDR Monitor Detection Fix

Some HDR-capable displays are incorrectly reported by **Gori: Cuddly Carnage** as not supporting HDR, leaving the HDR option greyed out.

This fix corrects **Gori's own monitor-capability state after the game's options data is loaded**, allowing the HDR option to be used on affected systems.

### Installation

1. Enable **HDR in Windows before launching the game**.
2. Close Gori.
3. Download and extract the latest **HDR Fix Patcher** from the GitHub Releases page.
4. Put the patcher either in the Gori game folder or in:

```text
GoriCuddlyCarnage\Binaries\Win64\
```

5. Run the patcher and choose **Apply HDR fix**.
6. Launch the game normally through Steam.
7. Open **Graphics** and enable HDR.

The patcher automatically creates and verifies a backup of the original executable.

### Restore

Run the patcher again and choose:

```text
Restore original EXE
```

### What the patch changes

The fix only changes Gori's own saved/live HDR monitor-support state.

It does **not** inject a DLL and does **not** patch Unreal Engine's low-level DXGI/D3D12RHI HDR detection.

The patcher checks the exact retail executable SHA-256 before modifying anything. If the game has been updated or the executable is unknown, it refuses to patch it.

### Supported retail executable

```text
SHA-256:
2bcd42db186018c3553d3e75dca34891255a3a3e0de3e6e663201febbec5e1d1
```

### Notes

- Enable Windows HDR before starting Gori.
- If Steam updates the game and the executable changes, restore/verify the game and wait for a compatible patch revision.
- No original game executable is distributed by this project.
- Source code is available on GitHub.
