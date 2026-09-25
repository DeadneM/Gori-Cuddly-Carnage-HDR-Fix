# Gori: Cuddly Carnage HDR Fix v1.0.0

First public release of the validated **V4B** HDR monitor-detection fix.

## What it fixes

On affected systems, Gori can incorrectly report an HDR-capable monitor as unsupported and leave the HDR option greyed out.

The patch forces Gori's own live `DoesMonitorHaveHDRSupport` field to true after options data is loaded.

## Safety

- Exact retail SHA-256 verification before patching.
- Automatic verified backup.
- Restore option included.
- Unknown game builds are rejected.
- No original game executable is distributed.
- No DLL injection.
- No DXGI/D3D12RHI renderer patching.

See the repository README and technical notes for full details.
