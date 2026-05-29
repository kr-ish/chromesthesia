# Chromesthesia

A VST3/AU plugin for inducing pitch-to-color associations through daily, high-immersion practice. Designed for an n=1 self-experiment combining MIDI-driven full-screen color display with active Hindustani classical vocal training.

**By Handsome Labs** — experimental / self-research

---

## What It Does

Chromesthesia maps musical pitch to a perceptually calibrated, fullscreen color display. You play notes on a MIDI keyboard in your DAW while a chosen monitor fills with the associated color, providing the consistent audio-visual pairing that the synesthesia induction literature indicates is necessary for cross-modal association learning.

The goal is to test whether a non-synesthetic individual can develop automatic color percepts in response to musical pitch through 6–9 weeks of daily 30–60 min practice. The full scientific rationale, evidence base, protocol, and pre-registered success criteria are in [`docs/science.md`](docs/science.md).

---

## The Mapping

Colors are computed from audio frequency, in OKLCH (Ottosson, 2020) — a perceptually uniform color space — and converted to sRGB with CSS Color 4 gamut mapping (chroma reduction at constant hue and lightness). The reference frequency is **Sa-anchored at C#0 = 17.3239 Hz**, so for a vocalist working in scale C#, every Sa renders red and the swaras trace a clean rainbow.

| OKLCH dimension | Maps to | Formula |
|---|---|---|
| **Hue (H)** | Pitch class | `29° + phase × 271°` — Sa = red (29°) → Ni = violet (277°) |
| **Lightness (L)** | Pitch height | `0.25 + (clamp(octave_float, 1, 7) − 1) / 6 × 0.65` — monotonic across C1–C7 |
| **Chroma (C)** | MIDI velocity | `0.12 + (velocity/127) × 0.06` — soft = muted, loud = vivid (gamut-clamped per hue) |

where `phase = log₂(f / 17.3239 Hz) − floor(…)` and `octave_float = log₂(f / 17.3239 Hz)`.

**Swara → color (madhya saptak, A4 = 440 Hz):**

| Swara | Western | Freq (Hz) | OKLCH H | Color |
|---|---|---|---|---|
| Sa | C#4 | 277.2 | 29.0° | red |
| re (komal) | D4 | 293.7 | 51.6° | red-orange |
| Re | D#4 | 311.1 | 74.2° | orange |
| ga (komal) | E4 | 329.6 | 96.8° | yellow |
| Ga | F4 | 349.2 | 119.3° | yellow-green |
| Ma | F#4 | 370.0 | 141.9° | green |
| MA (teevra) | G4 | 392.0 | 164.5° | teal |
| Pa | G#4 | 415.3 | 187.1° | cyan |
| dha (komal) | A4 | 440.0 | 209.7° | light blue |
| Dha | A#4 | 466.2 | 232.2° | blue |
| ni (komal) | B4 | 493.9 | 254.8° | indigo |
| Ni | C5 | 523.3 | 277.4° | violet |

(Lowercase = komal, uppercase = shuddha, `MA` = teevra Ma — Bhatkhande shorthand.)

The mapping *function* is continuous in frequency, but the *display* is only as continuous as the pitch input. Vanilla MIDI note-on/off gives discrete 12-TET-stepped colors; continuous color sweeps during meend/gamaka require **MIDI pitch bend**, **MPE**, a continuous controller, or future audio pitch tracking.

The empirical basis for the spectral/linear arrangement: Itoh, Sakata, Kwee & Nakada (2017) observed an aggregate linear rainbow hue progression across 15 pitch-class-color synesthetes — though the same study found color was predominantly determined by note *name*, not raw frequency. This project deliberately departs from that finding by training a frequency-mediated continuous mapping with name reinforcement (Hindustani vocalization) riding alongside. See `docs/science.md` §3 for the design rationale and the disambiguation of what gets induced.

---

## Building

**Requirements:**
- macOS (VST3 + AU) or Windows (VST3)
- CMake ≥ 3.22
- JUCE 6.x at `../JUCE` (sibling of this project directory)
- Xcode (macOS) or Visual Studio (Windows)

**JUCE setup:**
```bash
# From the parent directory of this project:
git clone --depth 1 --branch 6.1.6 https://github.com/juce-framework/JUCE.git JUCE
```

**Build:**
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

Built artifacts are in `build/Chromesthesia_artefacts/`.

**Install (macOS):**
```bash
make install   # copies VST3 + AU into /Library/Audio/Plug-Ins/ (uses sudo)
```

Or manually:
```bash
cp -r build/Chromesthesia_artefacts/Release/AU/Chromesthesia.component \
      ~/Library/Audio/Plug-Ins/Components/
cp -r build/Chromesthesia_artefacts/Release/VST3/Chromesthesia.vst3 \
      ~/Library/Audio/Plug-Ins/VST3/
```

---

## Usage

Chromesthesia is a silent instrument — it receives MIDI and drives the color display but produces no audio. Load your actual instrument (synth, sampler, tanpura) on one track, and Chromesthesia on a **separate MIDI track**.

**Important — input routing:** route only your *training* MIDI to Chromesthesia. Tanpura/drone MIDI should go to a different plugin instance or a different track, otherwise the drone's sustained Sa/Pa will dominate the visual field and contaminate training. See `docs/science.md` §4.2.

**Setup (all DAWs):**
1. Create a MIDI/instrument track for your synth/tanpura as normal.
2. Create a second MIDI/instrument track for **Chromesthesia**.
3. Send only the training keyboard MIDI to the Chromesthesia track (not tanpura/drone).
4. In the Chromesthesia plugin UI, select your practice display from the **Display** dropdown.
5. Click **Go Fullscreen** — the color window opens on your chosen screen; the plugin UI collapses to a thin status bar.
6. Play notes — the screen fills with the associated color; releasing a note fades to black over ~500 ms.
7. Press **Esc** on the fullscreen window to exit (the plugin UI reappears), or press **C** to toggle the calibration palette.

---

## Display Setup

The plugin's hue mapping assumes a neutral display white point (~D65 / 6500 K). macOS has three settings that will silently shift your trained hues and **must be disabled** before training:

| Setting | Effect if active | Where |
|---|---|---|
| **Night Shift** | Warms display globally; deep blue Dha (OKLCH H=232°) looks teal-green | System Settings → Displays → Night Shift → set to *Off* (not just "less warm") |
| **True Tone** | Continuously adjusts white point to match *ambient* room light via the front sensor — colors literally change as the sun sets or you move rooms | System Settings → Displays → uncheck *True Tone* |
| **Auto-brightness** | Drifts display brightness with ambient. Since L encodes pitch height, this drifts your pitch-height encoding session-to-session | System Settings → Displays → uncheck *Automatically adjust brightness* |
| Third-party warmth (f.lux, Lunar, etc.) | Same as Night Shift | Disable during training, or schedule outside your practice window |

**External monitor:** if you're using a secondary monitor for the fullscreen display, set its OSD to **Standard / Native / 6500K / sRGB** mode — never "warm" or "reading mode."

**Brightness:** **don't go 100%**. Three reasons: (1) sustained 100% over 30–60 min/day in a dim room causes real eye strain; you'll start skipping sessions by week 2. (2) Consistency matters more than intensity for associative learning — the brain learns the *relative* OKLCH mapping, which transfers across brightness levels. (3) High saliency can actually impair conditioning at the margin (saccadic avoidance, attentional overload). Pick **40–60%** on a modern MacBook, set once, and lock it. If you ever do change it, note the date in your session log so you can correlate any anomalies later.

**Room lighting — dim, not dark.** Two reasons against pitch-black training: (1) **generalization risk** — an association trained only in a dark room may become context-bound to "dark room" and fail to fire when you hear music in normal light. The Nair & Brang (2019) result you may have seen cited for dark adaptation used 5 min of darkness as an *acute facilitation*, not a chronic training condition. (2) **Operational** — you need to see the keyboard and your hands. Dim the room enough that the fullscreen color dominates peripheral vision and isn't competing with bright lights or windows; keep a small warm-toned task light on the keyboard if needed. **Practice ~80% of sessions in dim conditions, ~20% in normal room light** to train cross-context generalization. Log which condition each session was in (one extra line in your journal) so you can stratify B1/B2 results at the retest.

**Verify with the built-in calibration palette:** press **C** in fullscreen mode to toggle a 12-stripe palette showing all swara reference colors with labels. Sa should look pure red, Pa cyan, Dha blue, Ni violet. If anything looks warm or off-spectrum, one of the settings above is still active. Press **C** again to return to live color, or **Esc** to exit fullscreen.

---

## Training Protocol

Brief summary; full protocol in [`docs/science.md`](docs/science.md):

- **Duration**: 9 weeks active induction, 12 weeks target. Plan an indefinite maintenance phase past that — Bor et al. (2014) found phenomenological effects largely faded by 3 months without ongoing practice.
- **Daily time**: 30–60 min of active playing (not passive listening). Combine MIDI keyboard reference + Hindustani vocal practice with swara vocalization (the name reinforcement that aligns with Itoh's mechanism).
- **Mapping consistency**: never change the mapping once started — stability of the mapping is the load-bearing variable.
- **Environment**: dim (not pitch-dark) room — ~80% of sessions dim, ~20% in normal room light for cross-context generalization; fullscreen on a secondary monitor at 40–60% brightness; neutral white point (see Display Setup above).
- **Pre-register success criteria at week 0** before starting. See `docs/science.md` §4.4 for the full B1/B2/P1/P2 marker definitions and §4.5 for the sound-only/name-only/motor-only condition-separation subprotocol.

Future-work scoping (post-baseline only — don't optimize prematurely): see [`docs/future-work.md`](docs/future-work.md) for ambient room lighting augmentation options (LIFX, WLED, DMX/ArtNet, Ketra) with decision criteria, engineering scope, and recommended exploration path.

---

## License

[PolyForm Noncommercial License 1.0.0](LICENSE)

Free to use, modify, and distribute for non-commercial purposes with attribution. Commercial use requires a separate license — contact Handsome Labs.

---

## Research Basis

Key sources (full citations in `docs/science.md`):

- Bor et al. (2014). Adults can be trained to acquire synesthetic experiences. *Scientific Reports*.
- Colizoli et al. (2012). Pseudo-synesthesia through reading books with colored letters. *PLOS ONE*.
- Itoh, Sakata, Kwee & Nakada (2017). Musical pitch classes have rainbow hues. *Scientific Reports*.
- Nair & Brang (2019). Inducing synesthesia in non-synesthetes. *Consciousness and Cognition*.
- Ottosson (2020). A perceptual color space for image processing.
- Spence & Di Stefano (2022). Coloured hearing, colour music, colour organs. *i-Perception*.
- Ward et al. (2024). Synesthesia is linked to large and extensive differences in brain structure and function. *Cerebral Cortex*.
