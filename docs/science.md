# Chromesthesia VST: Scientific Basis and Design Rationale

**Project:** Chromesthesia — A pitch-to-color synesthesia induction tool  
**Author:** Handsome Labs  
**Status:** Experimental / self-research

---

## Abstract

This document describes the scientific foundations underlying the Chromesthesia VST plugin, a tool designed to test whether chromesthesia (sound-to-color synesthesia) can be induced in a non-synesthetic individual through daily, high-immersion associative practice. The plugin maps musical pitch to a perceptually calibrated fullscreen color display, grounded in published research on synesthesia induction, cross-modal correspondence, and perceptual color science. The approach represents a structured self-experiment informed by cognitive neuroscience literature.

---

## 1. Background: What Is Chromesthesia?

Chromesthesia is a form of synesthesia in which auditory stimuli — typically musical pitch or timbre — automatically and involuntarily evoke visual color experiences. It is one of the most common forms of synesthesia, estimated to affect approximately 1–4% of the population (Cytowic & Eagleman, 2011; Simner et al., 2006).

Key established properties of chromesthesia include:

- **Automaticity**: Color experiences are involuntary, not deliberate visualizations (Cytowic, 1989).
- **Consistency**: Individual mappings are highly stable over time, with test-retest reliability >90% over intervals of up to one year (Simner et al., 2006).
- **Idiosyncrasy**: No universal pitch-to-color mapping exists across individuals. Notably, composers Scriabin and Rimsky-Korsakov — both reportedly synesthetic — agreed on almost no color assignments, despite working in the same musical tradition (Day, 2019).
- **Pitch-height–brightness covariance**: The single most consistent cross-individual pattern is that higher pitches are associated with lighter/brighter colors and lower pitches with darker colors. This holds among both synesthetes and non-synesthetes (Marks, 1974; Ward et al., 2008).
- **Structural brain differences**: Synesthetes show altered myelin content across the cortex (32 regions increased, 38 decreased) and enhanced functional connectivity between auditory and visual networks, particularly from the superior parietal lobe to visual area V4 (Ward et al., 2024; Hupé et al., 2012).

### 1.1 Neurological Models

Two principal mechanistic accounts of synesthesia are debated:

**Cross-activation model** (Ramachandran & Hubbard, 2001): Synesthesia arises from anomalously dense structural connections between adjacent cortical regions — in the case of grapheme-color synesthesia, between the visual word form area and color processing area V4 in the fusiform gyrus.

**Disinhibited feedback model** (Grossenbacher & Lovelace, 2001): Synesthetic percepts arise not from structural hyperconnectivity, but from disinhibited feedback from higher-order multimodal regions to primary sensory areas. Under this model, the connections exist in all brains but are normally suppressed.

Critically, a 2019 study found that approximately 5 minutes of visual deprivation facilitated auditory-evoked visual percepts (synesthesia-like experiences) in ~50% of non-synesthetes (Nair & Brang, 2019). This rapid timescale is incompatible with structural change but consistent with altered inhibitory tone, providing strong support for the disinhibited feedback model. It also suggests that synesthetic cross-modal coupling may be a latent capacity present in most human brains.

---

## 2. Can Synesthesia Be Induced?

The central hypothesis of this project rests on a substantial body of evidence that synesthesia-like associations can be acquired through training.

### 2.1 Key Induction Studies

**Colizoli, Murre, & Rouw (2012)** — *PLOS ONE*  
Non-synesthetes read a novel (~49,000 words) printed with specific letters colored (e.g., all 'e's in red, all 't's in green). Modified Stroop interference tests before and after demonstrated that participants acquired automatic letter-color associations with behavioral markers matching genuine synesthesia. A single book was sufficient to produce measurable effects.

**Bor, Rothen, Schwartzman, Clayton, & Seth (2014)** — *Scientific Reports*  
This landmark study ran a nine-week adaptive training protocol in which participants learned 13 specific grapheme-color pairings. Following training, most participants exhibited both standard behavioral markers and physiological markers (event-related potentials) of genuine grapheme-color synesthesia, including early visual cortex activation to achromatic graphemes. The training was "adaptive" — tasks progressively increased in difficulty.

**Terhune, Tai, Cowey, Popescu, & Kadosh (2011)** — *Neuropsychologia*  
Demonstrated coordinated neural, behavioral, and phenomenological changes following overtraining of synesthetic associations, including EEG and TMS evidence. Grapheme-color synesthetes showed significantly lower phosphene thresholds in visual cortex than non-synesthetes — an index of enhanced visual cortex excitability that emerged with training.

**Inducing Synesthesia in Non-Synesthetes: Short-Term Visual Deprivation Facilitates Auditory-Evoked Visual Percepts** — *Consciousness and Cognition* (Nair & Brang, 2019)
After just 5 minutes of dark adaptation, ~50% of non-synesthetes reported synesthesia-like visual percepts in response to sounds. This suggests synesthetic coupling is latent in most individuals and implicates sensory gating rather than purely structural factors.

### 2.2 Training Characteristics That Matter

From the aggregate of induction literature:

- **Duration**: Effects require weeks to months. Short protocols (≤10 days) produce automatic associations but not full phenomenological experience. Robust synesthesia markers emerged after ~9 weeks of daily training (Bor et al., 2014).
- **Daily practice**: Studies suggest ~30 minutes/day is effective. Longer or more frequent sessions likely accelerate induction.
- **Active engagement**: Active training produces effects that passive exposure controls do not — the learner must actively engage with the association, not merely be exposed to it.
- **Consistency**: Once established, synesthetic associations are highly stable. Natural synesthetes maintain >90% consistency over a year. Disrupting the mapping during training would undermine induction.
- **Durability**: Associations can decay within ~3 months of stopping practice, suggesting ongoing maintenance practice is necessary for long-term retention.
- **Saturation**: Research indicates moderate color saturation — not maximum — is more effective for conditioning. Extremely saturated stimuli may be visually fatiguing.

### 2.3 Relevance to Pitch-Color Synesthesia

The majority of induction studies have used grapheme-color (letter-color) synesthesia as their model, which is simpler to control experimentally. The evidence for inducing pitch-color (chromesthesia) specifically is less direct, but the mechanistic arguments extend straightforwardly: the core requirement is consistent, repeated co-occurrence of the target stimulus (a pitch) and the conditioned response (a color), with sufficient immersion to engage associative learning.

The key difference with pitch-color induction is that pitch is a continuous, high-dimensional variable (frequency), whereas graphemes are discrete categorical symbols. This makes the mapping richer but also potentially harder to internalize — a single pitch-to-color function must be learned, rather than a finite set of discrete pairs.

---

## 3. Pitch-to-Color Mapping: Design Rationale

### 3.1 Historical Systems

Several historical and contemporary systems for mapping pitch to color have been proposed:

| System | Year | Organization | Notes |
|---|---|---|---|
| Newton | 1704 | Diatonic (Dorian D–D), 7 colors | Proportional intervals; analogical, not physical |
| Castel | 1725 | Chromatic, 12 colors | Extended Newtonian; practical color organ |
| Scriabin (Prometheus) | 1911 | Circle of fifths | Likely intellectual, not genuine synesthesia; harmonically adjacent notes get adjacent colors |
| Rimsky-Korsakov | ~1905 | Major keys | Genuine synesthesia; irregular, no spectral logic |
| Theosophical system | ~1880s | Diatonic ascending | C=red → B=violet; influenced Scriabin |
| Itoh et al. (2017) | 2017 | Solfège (do–si) | Empirical; genuine synesthetes; rainbow hue progression confirmed |

Newton's correspondence between the seven spectral colors and the seven diatonic notes established the foundational analogy (Newton, 1704, *Opticks*). Scriabin's *Prometheus: Poem of Fire* (1911) implemented a circle-of-fifths-based color system where harmonically related notes receive spectrally adjacent colors — making tonal progressions visually coherent (see Section 3.4 for discussion of this tradeoff).

### 3.2 Empirical Evidence: Rainbow Hue Progression

Itoh, Takimoto, & Akatsuka (2017) studied 15 individuals with confirmed pitch-class color synesthesia using solfège naming. They found a **linear rainbow hue progression**: do (C) maps to red (~0 radians), with hue increasing linearly through the solfège scale to si (B) at violet (~2π radians). Saturation decreased gradually across the scale. Crucially, the dominant determinant of color was the **verbal label** of the note (do, re, mi...), not raw acoustic frequency — consistent with the role of learned categorical associations.

This empirical finding from genuine synesthetes is the primary evidence base for the spectral/linear mapping adopted in this project.

### 3.3 The Spectral/Linear Mapping

The design uses a spectral hue progression from red (C) to violet (B), implemented as a continuous function of audio frequency rather than discrete MIDI note numbers. This has several advantages:

**Frequency-based (not MIDI-based):** Color is computed from the actual audio frequency in Hz, making the mapping tuning-agnostic. In 12-tone equal temperament (12-TET), 12-TET and just intonation versions of nominally the same note produce slightly different hues — the color literally encodes the tuning.

**Continuous and microtonal:** The mapping `phase = log₂(f / f_ref) mod 1.0` is a continuous function of frequency. Any pitch — including microtonal pitches, quarter tones, or just-intonation ratios — receives a unique, interpolated color. No discrete bucketing occurs.

**Continuous brightness:** Lightness maps to the raw (non-floored) log-frequency value, making brightness fully continuous across the entire pitch range. Every semitone — and every microtonal interval — produces a distinct lightness level. Whether the brain infers octave equivalence from the repeating hue cycle, or treats each octave as genuinely different, is left as an open empirical question for the practitioner.

**The three mapping dimensions (OKLCH):**

```
H (hue)        = 29° + phase × 271°                          C=red(29°), B=violet(300°)
L (lightness)  = 0.10 + (clamp(octave_float, 0, 8) / 8) × 0.80   C0=dim, C8=bright (continuous)
C (chroma)     = 0.12 + (velocity/127) × 0.15                soft=muted, loud=vivid
```

where `phase = log₂(f / 16.3516 Hz) mod 1.0` and `octave_float = log₂(f / 16.3516 Hz)` (no floor).

### 3.4 The Circle-of-Fifths Alternative (Not Adopted)

Scriabin's approach assigns spectrally adjacent colors to harmonically adjacent notes (arranged by the circle of fifths). This makes tonal progressions visually coherent — a I-IV-V chord in any key would produce a cluster of adjacent hues. However, this approach has two significant drawbacks for the induction goal:

1. **Learnability**: Chromatically adjacent notes are assigned very different colors (e.g., C=red, C#=violet-purple in Scriabin's system), making the mapping harder to internalize through scale-wise practice.
2. **Microtonal inextensibility**: The circle of fifths is specific to 12-TET. In just intonation or other tunings, it has no clean equivalent.

The spectral/linear approach was adopted on grounds of learnability and continuity, accepting the tradeoff that harmonic intervals will not produce adjacent colors.

### 3.5 Perceptual Color Space: OKLCH

Colors are computed in OKLCH (Ottosson, 2020) rather than the intuitive but perceptually non-uniform HSL space.

**Why not HSL?** HSL hue interpolation is perceptually non-uniform: equal semitone steps produce unequal perceived color differences. Yellow-to-green transitions appear rapid; blue transitions appear slow. This would cause the learner to perceive the pitch-color mapping as inconsistent across the register.

**OKLAB** (Ottosson, 2020) is a perceptual color space designed to fix the known failures of CIELAB, specifically:
- The *blue-purple problem*: in CIELAB, reducing chroma on a blue shifts its hue toward purple. In OKLAB, hue is stable under chroma changes.
- The *chroma dip*: interpolating between saturated colors in Cartesian Lab space passes through a desaturated gray midpoint. OKLAB maintains chroma along interpolation paths.

OKLCH is the cylindrical form of OKLAB with explicit Hue, Lightness, and Chroma axes, enabling direct hue-angle assignment. It is now the default interpolation space in CSS Color Level 4, Adobe Photoshop, Unity, and Godot.

The note-off fade is implemented in OKLCH by decaying L and C toward zero while holding H constant — the color drains of light and saturation without any hue shift, providing a clean visual onset/offset boundary for associative conditioning.

---

## 4. Protocol Design

### 4.1 Training Parameters

Based on the induction literature, the following training parameters are recommended:

| Parameter | Value | Basis |
|---|---|---|
| Session duration | 30–60 min/day | Bor et al. (2014); Colizoli et al. (2012) |
| Minimum training period | 6–9 weeks | Bor et al. (2014) |
| Mode | Active (play notes, listen, watch) | Active > passive for induction |
| Environment | Darkened room, fullscreen display | Sensory priming; peripheral immersion |
| Mapping consistency | Never change the mapping | >90% stability in natural synesthesia |
| Audio-visual sync | <150ms | Perceptual processing window for synesthetic color |
| Saturation | Moderate (C ≤ 0.27) | Extreme saturation fatigues; moderate conditions better |

### 4.2 Display

The plugin opens a borderless, fullscreen color window on a configurable display (typically a second monitor while the DAW is operated on the primary). The practice session involves:

1. Playing individual notes on a MIDI keyboard
2. Observing the full-field color response
3. Playing scales, arpeggios, and improvised melodic lines
4. Attempting to mentally anticipate the color before playing each note

The goal of anticipation practice — trying to predict the color before sounding the note — mimics the top-down component of associative learning and may accelerate internalization.

### 4.3 Outcome Assessment

Without laboratory facilities, behavioral assessment of induction success will rely on:

- **Self-report consistency**: After completing daily sessions, occasionally test whether colors appear when merely imagining or hearing pitches without the visual display.
- **Stroop-like self-testing**: With the display off, imagine the color for a played note. Then display the color. Does conflict feel uncomfortable when the displayed color "feels wrong"?
- **Journal documentation**: Keep a dated log of subjective color experiences during and outside practice, noting any unsolicited color percepts.

---

## 5. Hypothesis

**Primary hypothesis:** Consistent daily associative practice, using a fullscreen color display paired with MIDI keyboard performance over 6–9 weeks, can induce automatic or semi-automatic color percepts in response to musical pitch in a non-synesthetic individual.

**Secondary hypothesis:** The induced associations, if formed, will reflect the trained spectral/linear mapping (C=red, ascending through spectrum to B=violet, with brightness covarying with octave).

**Null hypothesis:** No measurable synesthetic-like associations form within the training period, and pitch does not spontaneously evoke color experiences outside the training context.

---

## 6. Limitations and Considerations

- **Single subject**: This is an n=1 self-experiment. Results will not generalize statistically.
- **Demand characteristics**: Self-report measures may be influenced by expectation and motivation.
- **Individual differences**: The capacity for synesthetic induction varies by individual. Some people may be more "induction-prone" than others.
- **Mapping arbitrariness**: The spectral/linear mapping, while evidence-informed, is not the "only correct" mapping. The consistency of the mapping matters more than its specific form.
- **Conflation with imagery**: Voluntary visual imagery of color (deliberately imagining red when hearing C) is not the same as automatic synesthetic experience. Outcome assessment should attempt to distinguish these.

---

## 7. References

Bor, D., Rothen, N., Schwartzman, D. J., Clayton, S., & Seth, A. K. (2014). Adults can be trained to acquire synesthetic experiences. *Scientific Reports*, 4, 7089. https://doi.org/10.1038/srep07089

Colizoli, O., Murre, J. M., & Rouw, R. (2012). Pseudo-synesthesia through reading books with colored letters. *PLOS ONE*, 7(6), e39799. https://doi.org/10.1371/journal.pone.0039799

Cytowic, R. E. (1989). *Synesthesia: A Union of the Senses*. Springer.

Cytowic, R. E., & Eagleman, D. M. (2011). *Wednesday Is Indigo Blue: Discovering the Brain of Synesthesia*. MIT Press.

Day, S. A. (2019). *Synesthetes: A handbook*. CreateSpace.

Grossenbacher, P. G., & Lovelace, C. T. (2001). Mechanisms of synesthesia: Cognitive and physiological constraints. *Trends in Cognitive Sciences*, 5(1), 36–41. https://doi.org/10.1016/S1364-6613(00)01571-0

Hupé, J. M., Bordier, C., & Dojat, M. (2012). The neural bases of grapheme-color synesthesia are not localized in real color-sensitive areas. *Cerebral Cortex*, 22(7), 1619–1629. https://doi.org/10.1093/cercor/bhr236

Itoh, K., Takimoto, Y., & Akatsuka, T. (2017). Musical pitch classes have rainbow hues in pitch class-color synesthesia. *Scientific Reports*, 7, 17781. https://doi.org/10.1038/s41598-017-18150-y

Marks, L. E. (1974). On associations of light and sound: The mediation of brightness, pitch, and loudness. *The American Journal of Psychology*, 87(1/2), 173–188. https://doi.org/10.2307/1422011

Newton, I. (1704). *Opticks: Or, a Treatise of the Reflexions, Refractions, Inflexions and Colours of Light*. Sam. Smith and Benj. Walford.

Ottosson, B. (2020). A perceptual color space for image processing. *Blog post*. https://bottosson.github.io/posts/oklab/

Ramachandran, V. S., & Hubbard, E. M. (2001). Synaesthesia: A window into perception, thought and language. *Journal of Consciousness Studies*, 8(12), 3–34.

Saitis, C., & Wallmark, Z. (2024). Color and tone color: Audiovisual crossmodal correspondences and timbre. *Frontiers in Psychology*, 15. https://doi.org/10.3389/fpsyg.2024.1520131

Nair, A., & Brang, D. (2019). Inducing synesthesia in non-synesthetes: Short-term visual deprivation facilitates auditory-evoked visual percepts. *Consciousness and Cognition*, 70, 70–79. https://doi.org/10.1016/j.concog.2019.02.006

Simner, J., Mulvenna, C., Sagiv, N., Tsakanikos, E., Witherby, S. A., Fraser, C., Scott, K., & Ward, J. (2006). Synaesthesia: The prevalence of atypical cross-modal experiences. *Perception*, 35(8), 1024–1033. https://doi.org/10.1068/p5469

Spence, C., & Di Stefano, N. (2022). Coloured hearing, colour music, colour organs, and the search for perceptually meaningful correspondences between colour and sound. *i-Perception*, 13(3). https://doi.org/10.1177/20416695221092802

Terhune, D. B., Tai, S., Cowey, A., Popescu, T., & Kadosh, R. C. (2011). Enhanced cortical excitability in grapheme-color synesthesia and its modulation. *Current Biology*, 21(23), 2006–2009. https://doi.org/10.1016/j.cub.2011.10.032

Ward, J., Thompson-Lake, D., Ely, R., & Kaminski, F. (2008). Synaesthesia, creativity and art: What is the link? *British Journal of Psychology*, 99(1), 127–141. https://doi.org/10.1348/000712607X204164

Ward, J., et al. (2024). Structural brain differences in synesthetes: Altered myelin content across cortical and subcortical regions. *Cerebral Cortex*, 34(11). https://doi.org/10.1093/cercor/bhae446

---

## Appendix A: Frequency-to-Color Mapping Formula

Given audio frequency `f` in Hz:

```
f_ref        = 16.3516 Hz   (C0)
octave_float = log₂(f / f_ref)          (continuous; no floor)
phase        = octave_float mod 1.0      ∈ [0.0, 1.0)

OKLCH:
  H = 29.0 + phase × 271.0                              (degrees; 29°=red, 300°=violet)
  L = 0.10 + (clamp(octave_float, 0, 8) / 8) × 0.80   (fully continuous brightness)
  C = 0.12 + (velocity / 127) × 0.15
```

**12-TET reference values:**

| Note | Freq (Hz, A4=440) | Phase | OKLCH H | Color |
|---|---|---|---|---|
| C4 | 261.63 | 0.000 | 29.0° | Red |
| D4 | 293.66 | 0.167 | 74.1° | Orange |
| E4 | 329.63 | 0.333 | 119.2° | Yellow-green |
| F4 | 349.23 | 0.417 | 141.9° | Green |
| G4 | 392.00 | 0.583 | 187.1° | Cyan |
| A4 | 440.00 | 0.750 | 232.3° | Blue |
| B4 | 493.88 | 0.917 | 277.5° | Violet |

**Just intonation divergence (from C4):**

| JI interval | Ratio | JI freq | Phase delta | Hue delta |
|---|---|---|---|---|
| Perfect 5th (G) | 3:2 | 392.44 Hz | +0.0019 oct | +0.5° |
| Major 3rd (E) | 5:4 | 327.03 Hz | −0.0136 oct | −3.7° |
| Harmonic 7th (Bb) | 7:4 | 457.14 Hz | −0.031 oct | −8.4° |

## Appendix B: OKLCH to sRGB Conversion

Using Ottosson's exact matrices:

```cpp
// OKLCH → OKLAB
float h_rad = H * (π / 180);
float a = C * cos(h_rad);
float b = C * sin(h_rad);

// OKLAB → LMS (cube-root intermediate)
float l_ = L + 0.3963377774·a + 0.2158037573·b;
float m_ = L − 0.1055613458·a − 0.0638541728·b;
float s_ = L − 0.0894841775·a − 1.2914855480·b;
float l = l_³, m = m_³, s = s_³;

// LMS → linear RGB
r =  4.0767416621·l − 3.3077115913·m + 0.2309699292·s;
g = −1.2684380046·l + 2.6097574011·m − 0.3413193965·s;
b = −0.0041960863·l − 0.7034186147·m + 1.7076147010·s;

// Linear → sRGB gamma (IEC 61966-2-1)
sRGB(x) = x ≤ 0.0031308 ? 12.92·x : 1.055·x^(1/2.4) − 0.055
```
