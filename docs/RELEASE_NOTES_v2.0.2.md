# Gori: Cuddly Carnage HDR Fix v2.0.2

This release promotes the validated **V20** runtime build.

## Fixed

- Gori's own HDR ON/OFF setting is now followed by the mod.
- F10 HDR ON/OFF continues to work and mirrors the live game setting.
- F10 settings are now persisted through `GoriHDRFix.ini` beside the ASI.
- Saved settings are restored before startup HDR forcing can overwrite them.
- Multi-monitor handling keeps the requested HDR preference separate from temporary output eligibility.
- HDR is suspended on a known SDR output without permanently erasing the saved HDR preference.

## Preserved

- V4B monitor-capability correction in memory
- native Unreal HDR path
- NVIDIA / AMD / Intel support
- live HDR CVars
- native HDR10 metadata
- conditional PQ / Rec.2020 completion
- F10 overlay and mouse input
- fullscreen/windowed handling
- no diagnostic log files
- original game EXE untouched

## Distribution cleanup

The public ZIP contains only:

```text
GoriHDRFix.asi
dxgi.dll
README.txt
```

Source code is kept in the GitHub repository under `Source/`.

## Supported Steam EXE

```text
SHA-256:
2bcd42db186018c3553d3e75dca34891255a3a3e0de3e6e663201febbec5e1d1
```

## Validated release hashes

```text
GoriHDRFix.asi
e95c90d48c49e4ef94b5f7ad12c95524025add9dab5ba4a7cf2be57768e008c7

dxgi.dll
89487954807a1751321f0392cd36a1819e5db4e9fb5c721da5a0e0ef72f1d0cf

Gori_Cuddly_Carnage_HDR_Fix_v2.0.2.zip
179468f462354c0319a96ef4b69a66b758b72c34a57dddbc93585708cdb04979
```
