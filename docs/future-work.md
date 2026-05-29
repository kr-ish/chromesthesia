# Future Work: Ambient Room Lighting Augmentation

**Status:** Scoped, not started. Do not begin until the screen-only protocol has been run for ≥3 weeks and the decision criteria below are met.

This document scopes four hardware options for replacing or augmenting the screen-based color display with synchronized ambient room lighting. All four are real engineering projects, not weekend hacks; the cheapest takes ~2 weekends, the most expensive runs into thousands of dollars and weeks of work. Read the decision criteria before assuming any of this should happen.

---

## Why consider ambient lighting at all

Three arguments for adding room lighting to the protocol:

1. **Ecological match to natural chromesthesia.** Real synesthetes describe ambient/spatial color experiences, not "a colored rectangle in front of me." Training in a colored *room* is phenomenologically closer to the target outcome.
2. **Removes screen-as-context-cue.** A trained association bound to "I am looking at a monitor" risks failing to fire when the practitioner hears music in normal listening contexts (concerts, headphones, casual playback). Ambient lighting decouples the visual signal from device-specific context.
3. **Eliminates screen-related strain.** 30–60 min daily of fullscreen-color staring is fatiguing across 9 weeks. Ambient color from peripheral fixtures is much easier on the visual system.

The strongest argument *against* is that the screen-only system is already calibrated, in-gamut, low-latency, and built. Adding ambient lighting is significant new engineering and hardware investment with no guarantee of marginal benefit.

---

## Decision criteria — when to actually do this

Do **not** start any of this work before:

- [ ] **Week 0 baseline complete** (B1, B2, P1, P2 all measured on the screen-only system).
- [ ] **Minimum 3 weeks of screen-only training** completed with daily session logs.
- [ ] **At least one of the following is true:**
  - P1/P2 phenomenological markers are flat (no spontaneous percepts, automaticity rating stuck below 3/7) while B1/B2 behavioral markers are rising. This is the signal that the *immersive/qualia* axis is the bottleneck and that a richer peripheral signal might unblock it.
  - Cross-context generalization (§4.5 condition-separation) shows the association is context-bound to dim screen viewing and fails to transfer to normal-light listening conditions. Ambient lighting would be a credible intervention.
  - The practitioner reports specific phenomenological dissatisfaction with the screen experience that ambient lighting plausibly addresses (e.g., "the color feels like a stimulus *I'm looking at* rather than something I'm *in*").

If at week 3 the screen-only protocol is producing rising markers on all four axes (B1, B2, P1, P2), **don't add this**. It's premature optimization.

---

## Options matrix

| Option | Latency | Gamut quality | Hardware cost | Plugin engineering | Calibration burden |
|---|---|---|---|---|---|
| **LIFX A19 bulbs (LAN protocol)** | 50–100 ms | Limited (RGB 3-LED) | $100–160 | ~150 LOC UDP networking | Eyeball against screen palette |
| **WLED on ESP32 + LED strips** | 10–30 ms | Limited (RGB or RGBW) | $60–120 | ~100 LOC DDP/E1.31 over UDP | Manual; optional colorimeter (~$200) |
| **DMX/ArtNet architectural fixtures** | <10 ms (entry RGB) to <10 ms (pro multi-channel) | Limited (entry RGB) to excellent (multi-channel) | $300–5000+ | ~200 LOC ArtNet + fixture profiles | Spectrometer recommended ($500+) |
| **Ketra (6-channel tunable spectrum)** | 30–60 ms | Excellent (CRI 99+; renders cyan/indigo/yellow properly) | $2500+ | Ketra API integration (~1–2 weeks) | Factory-calibrated; periodic drift checks |

The recurring gamut question: **consumer RGB-only fixtures cannot cleanly distinguish Pa (cyan, H=187°), Dha (blue, H=232°), and komal Ni (indigo, H=255°)** — exactly the swaras where hue identity matters most. Three-LED additive mixing has fundamental wavelength gaps in the cyan and yellow regions. Multi-channel fixtures (RGB + amber + cool white + warm white, or 6-channel like Ketra) fill those gaps; pure RGB cannot.

---

## Option 1 — LIFX (entry option)

**Recommended starting point** for ambient augmentation. Cheap enough to validate the concept, mature ecosystem, accessible LAN protocol.

**Hardware:**
- 2–4× LIFX A19 Color bulbs ($40 each, total $80–160)
- Standard E26 lamp sockets or fixtures
- 2.4 GHz WiFi network (existing)

**Placement:** behind the practitioner and to the sides (out of direct line of sight), bouncing off ceiling or back wall. Direct-view placement creates uncomfortable point sources and competes with the screen if used as augmentation.

**Protocol:** [LIFX LAN Protocol](https://lan.developer.lifx.com/docs/introduction) — UDP packets on port 56700, no cloud round-trip. Packet format includes HSBK (Hue, Saturation, Brightness, Kelvin) per device; broadcast or unicast.

**Plugin engineering scope:**

```
// New files
src/lighting/LIFXClient.h        // UDP socket abstraction
src/lighting/LIFXClient.cpp      // ~150 LOC: discover + send HSBK
src/lighting/LightingTarget.h    // shared interface across all 4 options

// Changes to existing
PluginProcessor.cpp              // emit color change events to LightingTarget
PluginEditor.cpp                 // UI for fixture IPs, enable toggle, test button
ColorEngine.cpp                  // add oklchToLIFXHSBK() conversion
```

**Color conversion:** OKLCH → LIFX HSBK requires mapping OKLCH hue (degrees) to LIFX hue (0–65535 over 360°), OKLCH chroma to LIFX saturation (0–65535), OKLCH lightness to LIFX brightness (0–65535). Kelvin is fixed at 6500 (neutral). Note that LIFX brightness is *not* perceptually linear, so a calibration LUT per swara may be needed.

**Calibration:** during a setup session, display each calibration swara on screen + emit it to LIFX. Eyeball whether the bulb output matches the screen. Build a per-bulb correction LUT mapping OKLCH → LIFX-corrected-HSBK. Expect to spend a few hours on this per fixture set.

**Latency reality check:** LIFX LAN claims ~50ms; in practice on a busy WiFi network it can spike to 150ms+. Measure empirically with a high-FPS camera or photodiode + scope. If latency is unacceptable, move to WLED.

**Engineering effort:** 1–2 weekends (16–24 hours).

**Pros:** lowest barrier to entry; no hub; mature; reasonable gamut; ambient WiFi already exists.
**Cons:** WiFi latency is variable; RGB-only gamut limitations on Pa/Dha/Ni/Ga; per-bulb color variation requires calibration.

---

## Option 2 — WLED on ESP32 + LED strips (low-latency bench option)

**Best price/latency option.** A real engineering build — soldering, firmware flashing, mounting strips — but unbeatable on responsiveness.

**Hardware:**
- 1–2× ESP32 DevKit boards ($10–15 each)
- 5m WS2812B or SK6812-RGBW addressable LED strip ($25–40)
- 5V 10A power supply with proper barrel jack + capacitor + level shifter ($15–25)
- Aluminum mounting channel + diffuser ($20–30 for nice diffusion)
- Optional: 3D-printed enclosure for ESP32

Total: ~$80–120.

**Mounting:** the strips need diffusion (aluminum channel with frosted cover) to avoid the point-source LED dots being visible. Mount along the back of a shelf, around a doorway, or behind a furniture piece for indirect uplight.

**Protocol:** [WLED](https://kno.wled.ge/) firmware on ESP32 supports several network protocols. Use **DDP** (Distributed Display Protocol) over UDP for direct frame-rate-uncapped control — typical latency 10–30 ms, sub-10 ms achievable with tuning. E1.31 (sACN) is an alternative if you want compatibility with DMX consoles.

**Plugin engineering scope:**

```
src/lighting/WLEDClient.h
src/lighting/WLEDClient.cpp      // ~100 LOC: DDP packet format + UDP send
```

DDP packet format is simple: header + sequence of RGB triplets. Send one packet per color change; WLED renders immediately.

**Color conversion:** OKLCH → linear RGB (skip the sRGB gamma transform since WS2812B has its own gamma response). The plugin already has OKLCH → linear RGB in `ColorEngine.cpp`; just expose it. WS2812B has notable non-linearity at low brightness; a per-channel gamma LUT (γ ≈ 2.2 conventional) gives more uniform low-end response.

**Calibration:** harder than LIFX because there's no factory color profile. Options:
- Eyeball calibration against the screen palette (acceptable for a first pass)
- Use a smartphone color picker app held to the diffuser (better)
- X-Rite ColorMunki Display or Calibrite ColorChecker Display Plus (~$200) — measures actual displayed color, generates LUT (best)

**Engineering effort:** 1 weekend hardware build + 1 weekend software = 24–32 hours. Add 4–8 hours for calibration LUT generation.

**Pros:** cheapest; lowest latency by a wide margin; fully open; hackable; integrates with existing DMX ecosystem via E1.31.
**Cons:** visible LED strip aesthetic unless well-diffused; calibration is on you; RGB-only gamut (same as LIFX); requires basic electronics comfort.

---

## Option 3 — DMX/ArtNet architectural fixtures (professional path)

**Right answer if budget allows and the goal is precise spectral control.** ArtNet is the industry standard for low-latency networked lighting control; DMX has been the architectural/theatrical standard for decades.

**Hardware spectrum, from entry to pro:**

- **Entry RGB par cans** (Chauvet SlimPAR T6, Eurolite LED PAR-56 RGB): $150–300 each. Same RGB-only gamut limitations.
- **Mid-tier RGBA / RGBW pars** (ETC ColorSource PAR, Elation SixPar): $400–1200 each. Adds amber/white for somewhat better gamut.
- **Pro multi-channel** (Robe Spiider, ChromaQ Color Force, Vari-Lite VL2600): $1500–5000 each. RGB + lime + amber, broadcast-quality CRI.

Plus: **ArtNet-to-DMX node** ($50–200, e.g., Enttec ODE Mk3, ENTTEC DMX USB Pro), DMX cable, fixture power.

**Protocol:** plugin emits [Art-Net](https://art-net.org.uk/) packets over UDP (Ethernet) to the node, which converts to DMX-512 and drives the fixtures. ArtNet refresh rates up to 44 Hz (22.7 ms cycle); DMX itself updates at 44 Hz max; total practical latency <20 ms.

**Plugin engineering scope:**

```
src/lighting/ArtNetClient.h
src/lighting/ArtNetClient.cpp        // ~150 LOC: ArtDmx packet builder
src/lighting/FixtureProfile.h        // abstraction: channels per fixture
src/lighting/FixtureProfile.cpp      // ~100 LOC: OKLCH → channel values
```

The **fixture profile abstraction** is the load-bearing piece: a fixture might be 3 channels (RGB), 4 (RGBA), 6 (RGB + amber + cool white + warm white), or more. The conversion from OKLCH to per-channel intensities is fixture-specific — a 6-channel profile gives much better color than an RGB-only profile but requires knowing the fixture's spectral characteristics. JSON-defined fixture profiles are the standard pattern (cf. [OFL](https://open-fixture-library.org/)).

**Color conversion:** for RGB fixtures, same as LIFX/WLED. For multi-channel fixtures, the conversion is a constrained optimization problem: given OKLCH target color and the fixture's per-channel spectral basis, find channel intensities that produce the closest match in tristimulus space while minimizing total power. This is a small QP solvable in microseconds but requires knowing the fixture SPDs (spectral power distributions).

**Calibration:** colorimeter or spectrometer is highly recommended. X-Rite i1Pro (entry: $500–1000 used; pro: $2000+) measures actual color emitted and lets you generate precise OKLCH → channel-vector LUTs. Without measurement, multi-channel fixtures' advantage is wasted.

**Engineering effort:** $300–5000 hardware + 1–2 weeks software (40–80 hours) + 8–16 hours calibration.

**Pros:** lowest latency at any price tier; professional standard; expandable to many fixtures and full venue-style installations; multi-channel fixtures finally render the cyan/indigo/yellow region correctly.
**Cons:** cost scales fast; ArtNet requires basic networking knowledge (subnets, broadcast); DMX universe planning; per-fixture profile work; calibration is real work, not optional.

---

## Option 4 — Ketra (6-channel tunable spectrum, gold standard)

**Best color rendering bar none.** Designed specifically for chromatic precision in architectural and broadcast applications. Used in art galleries, hospitals, and high-end residential where color quality is the entire point.

**Hardware:**
- 2–4× Ketra N4 or G2 lamps ($500–800 each)
- Ketra Design Studio controller / hub (~$1000–2000)
- Lutron Caséta or RadioRA gateway if integrating with other systems

Total: $2500–5000+.

**Protocol:** Ketra's protocol is proprietary (Lutron-owned since 2018). Integration paths:
- Via Lutron Caséta / RadioRA 3 — REST-ish APIs exist via local hub
- Via Ketra Design Studio's API (if accessible to non-integrators)
- Third-party integration may require dealer-level access

Latency: 30–60 ms reported; not as fast as DMX but acceptable for held-note ambient.

**Plugin engineering scope:** highly dependent on what API access is available. Plan for ~1–2 weeks of integration including reverse-engineering or partner-API onboarding.

**Color rendering:** the killer feature. Six channels (RGB + amber + lime + warm white, configuration varies) produce CRI 99+ with proper spectral coverage in the cyan, yellow, and deep blue/violet bands that RGB-only fixtures miss. **Pa, Dha, komal Ni, and the yellows of Ga komal/shuddha would render correctly for the first time** with Ketra.

**Calibration:** Ketra lamps are factory-calibrated and drift checked. Their controller stores per-lamp correction. This is the one option where you can plausibly skip third-party measurement.

**Engineering effort:** $2500+ hardware + 1–2 weeks software (likely more if API access is hard).

**Pros:** the only option with truly correct color rendering for the full swara spectrum; factory-calibrated; designed for precision; long fixture lifetime.
**Cons:** very expensive; proprietary ecosystem; integration may be challenging without dealer access; overkill unless gamut is *the* limiting factor.

---

## Shared engineering scaffolding (applies to all four options)

Whichever option(s) is pursued, the plugin needs:

1. **LightingTarget abstraction** — `src/lighting/LightingTarget.h` interface with `sendColor(OKLCH)` and `sendBlack()` methods; concrete subclasses for LIFX / WLED / ArtNet / Ketra. Keeps the rest of the plugin agnostic.
2. **Background networking thread** — UDP/HTTP sends must not block the audio thread or the message thread for long. Use a `juce::Thread` or `std::async` with a lock-free queue for outbound color commands. Drop intermediate commands if the queue saturates (last-wins).
3. **Configuration UI** — extend `PluginEditor` with fixture IP entries, enable toggle, "test" buttons that fire a known reference color, and a "calibrate" mode that cycles the calibration palette through the fixtures.
4. **Failure handling** — when the network is down or a fixture is unreachable, the plugin should not stall. Hold last color or go dark gracefully. Surface the failure in the UI but don't interrupt training.
5. **Latency measurement harness** — a small test mode that emits a known color sequence at known timestamps and lets the practitioner measure end-to-end latency with a phone camera or DAW input. Necessary for empirical validation regardless of vendor specs.

These shared pieces represent ~200–300 LOC of work that's reused across whichever fixture option is chosen.

---

## Evaluation methodology — is the augmentation actually helping?

If/when ambient lighting is added, evaluate it the same way the protocol evaluates the screen system: **paired-comparison stratified by condition.**

Concrete approach for, say, the LIFX phase:

1. **Two-week A/B window.** Week N: screen-only sessions. Week N+1: screen + LIFX sessions. Counterbalance order across multiple replications if possible.
2. **B1 and B2 measured at the end of each window.** Compute delta-from-pre-window.
3. **P1 (spontaneous percept count) tracked continuously.** Compare weekly counts within the augmented vs. screen-only weeks.
4. **P2 (automaticity rating) at session end.** Stratify by condition.
5. **Subjective qualitative report** at the end of each window: does the color feel more "ambient" or more "spatial" with lighting active? Does the association feel more or less automatic?

Decision: keep the augmentation if P1/P2 show meaningful gains over screen-only, accepting some cost to B1/B2 if latency is worse. Drop it if B1/B2 degrade without P1/P2 compensating.

This is itself a small experiment — n=1, no blinding possible — but the structured comparison is better than "it feels nicer."

---

## Recommended exploration path

If/when the decision criteria above are met:

1. **Start with LIFX.** Lowest commitment, lets you validate that ambient augmentation actually helps before larger investment. ~$160 + 2 weekends.
2. **If LIFX helps but latency or gamut limits the experience**, branch:
   - **Latency complaint** → WLED. Cheap upgrade, same gamut limitations but much faster response. ~$100 + 2 weekends.
   - **Gamut complaint** (Pa looks like Dha, etc.) → DMX with multi-channel fixtures. $1000+ + 2 weeks software. The shared scaffolding from the LIFX phase makes the ArtNet client a smaller incremental build.
3. **If both** latency and gamut are limiting and the protocol has genuinely reached a "lighting matters" plateau → Ketra or pro DMX (Robe / ChromaQ). $2500+ + significant engineering. At this point you're building a research-grade installation, which is its own valid project but well beyond the n=1 baseline experiment.

Most likely outcome: LIFX is sufficient for the augmented experiment, and the upgrade question never comes up. The screen+LIFX hybrid covers the immersion and ambient axes adequately for most plausible chromesthetic phenomenology. Move beyond it only if there's specific evidence the higher-tier hardware would unblock something.

---

## Related forward work (not in scope here)

These adjacent capabilities are interesting but distinct from the lighting question:

- **Audio pitch tracking** (drive colors directly from voice, including meend/gamaka) — would solve the "vanilla MIDI is discrete" problem documented in §3.3 of `science.md`. Likely a YIN or CREPE-based pitch tracker on the audio input; ~1–2 weeks of work.
- **MPE controller support** — already works in principle (the plugin handles pitch bend), but adding a Roli Seaboard or Linnstrument to the practice setup would give native continuous-pitch input without requiring audio analysis.
- **Multi-fixture spatial mapping** — assigning different swaras to different room positions for spatial-audio-style chromesthesia. Out-of-scope for the n=1 protocol but a natural extension.
- **Automated B1 reaction-time test harness** — currently §4.4 is pre-registered but the practitioner has to build their own test rig. A built-in B1 mode in the plugin would streamline the protocol. ~1 weekend of UI work.
