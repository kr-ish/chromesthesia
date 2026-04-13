# Chromesthesia

A VST3/AU plugin for inducing chromesthesia (sound-to-color synesthesia) through daily associative practice.

**By Handsome Labs** — experimental / self-research

---

## What It Does

Chromesthesia maps musical pitch to a perceptually calibrated, fullscreen color display. You play notes on a MIDI keyboard in your DAW while a screen fills with the associated color — providing the consistent audio-visual pairing that the synesthesia induction literature indicates is necessary for cross-modal association learning.

The goal is to test whether a non-synesthetic individual can develop automatic color percepts in response to musical pitch through six-to-nine weeks of daily, high-immersion associative practice.

See [`docs/science.md`](docs/science.md) for the full scientific rationale, research citations, and experimental protocol.

---

## The Mapping

Colors are grounded in actual audio frequency (Hz), not MIDI note number — so the mapping is tuning-agnostic and continuous. Just intonation, microtonal pitches, and pitch bend all shift the color in real time.

| OKLCH dimension | Maps to | Formula |
|---|---|---|
| Hue (H) | Pitch class (position within octave) | `29° + phase × 271°` — red (C) → violet (B) |
| Lightness (L) | Pitch height (continuous) | `0.10 + (octave_float/8) × 0.80` — fully continuous; every semitone is a distinct brightness |
| Chroma (C) | MIDI velocity | `0.12 + (velocity/127) × 0.15` — soft=muted, loud=vivid |

Where `phase = log₂(f / 16.3516 Hz) mod 1.0` and `octave_float = log₂(f / 16.3516 Hz)` (no flooring — brightness is fully continuous across the pitch range).

Colors are computed in [OKLCH](https://bottosson.github.io/posts/oklab/) (Ottosson, 2020), a perceptually uniform color space, rather than HSL — ensuring that equal musical intervals produce equal perceived color changes.

The spectral progression (C=red → D=orange → E=yellow-green → G=cyan → A=blue → B=violet) matches the empirically observed rainbow hue pattern found across genuine pitch-class color synesthetes (Itoh et al., 2017, *Scientific Reports*).

---

## Building

**Requirements:**
- macOS (VST3 + AU) or Windows (VST3)
- CMake ≥ 3.22
- JUCE 6.x at `../JUCE` (sibling of this project directory — see below)
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

Built artifacts will be in `build/Chromesthesia_artefacts/`.

**Install (macOS):**
```bash
cp -r build/Chromesthesia_artefacts/Release/AU/Chromesthesia.component \
      ~/Library/Audio/Plug-Ins/Components/

cp -r build/Chromesthesia_artefacts/Release/VST3/Chromesthesia.vst3 \
      ~/Library/Audio/Plug-Ins/VST3/
```

---

## Usage

1. Load **Chromesthesia** on an Instrument track in your DAW (Ableton, Logic, Reaper, etc.)
2. Connect a MIDI keyboard
3. In the plugin UI, select your practice display from the **Display** dropdown
4. Click **Go Fullscreen** — the color window opens on your chosen screen
5. Play notes. The screen fills instantly with the associated color; releasing a note fades to black over 500ms
6. Practice daily for 30–60 minutes

**Recommended environment:** darkened room, fullscreen on a large monitor at comfortable viewing distance. The research suggests peripheral vision engagement helps with immersive visual conditioning.

---

## Training Protocol

Based on the induction literature:

- **Duration:** 6–9 weeks minimum; expect measurable effects in 2–3 weeks
- **Daily time:** 30–60 minutes of active playing (not passive listening)
- **Consistency:** Never change the mapping once you begin — the stability of the mapping is as important as its specific form
- **Suggested practice:** scales, arpeggios, melodies. Eventually try to anticipate the color before each note sounds.

Full protocol and scientific rationale: [`docs/science.md`](docs/science.md)

---

## License

[PolyForm Noncommercial License 1.0.0](LICENSE)

Free to use, modify, and distribute for non-commercial purposes with attribution. Commercial use requires a separate license — contact Handsome Labs.

---

## Research Basis

- Bor et al. (2014). Adults can be trained to acquire synesthetic experiences. *Scientific Reports*.
- Colizoli et al. (2012). Pseudo-synesthesia through reading books with colored letters. *PLOS ONE*.
- Itoh et al. (2017). Musical pitch classes have rainbow hues. *Scientific Reports*.
- Ottosson (2020). A perceptual color space for image processing. https://bottosson.github.io/posts/oklab/
- Shankar et al. (2019). Inducing synesthesia in non-synesthetes. *Cognition*.

Full citations: [`docs/science.md`](docs/science.md)
