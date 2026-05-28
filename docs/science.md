# Chromesthesia VST: Scientific Basis and Design Rationale

**Project:** Chromesthesia — A pitch-to-color synesthesia induction tool
**Author:** Handsome Labs
**Status:** Experimental / self-research (n=1)
**Subject context:** Tenor vocalist studying Hindustani classical vocal in scale C# (Sa = C#)

---

## Abstract

This document describes the scientific foundations underlying the Chromesthesia VST plugin, an n=1 self-experiment testing whether a non-synesthete can acquire automatic pitch-to-color associations through daily, high-immersion practice combining MIDI-driven full-screen color display with Hindustani classical vocal training. The plugin maps audio frequency to a perceptually calibrated color in the OKLCH color space, with the hue cycle anchored to the practitioner's tonic (Sa = C#). The protocol draws on published evidence for grapheme-color induction and cross-modal correspondence, while deliberately diverging from the published natural-synesthesia phenotype in one specific way: the mapping is continuous in frequency rather than discrete in pitch-class name. This divergence is documented and justified below, and is itself part of what the experiment is testing.

The expected outcome — if induction succeeds — is **an artificial, frequency-mediated color association**, not a replication of natural pitch-class-color synesthesia (which is name-mediated). Both are potentially valuable; only the former is a plausible target for this protocol.

---

## 1. Background: What Is Chromesthesia?

Chromesthesia is a form of synesthesia in which auditory stimuli — typically musical pitch, pitch-class, or timbre — automatically and involuntarily evoke visual color experiences. It is one of many recognized synesthesia variants. Prevalence estimates vary by methodology and inclusion criteria:

- **All synesthesia variants combined: ~4.4%** (Simner et al., 2006, screened a random sample of 500 adults).
- **Grapheme-color (the most-studied form): ~1.0–1.4%** (Simner et al., 2006; Ward & Simner, 2022).
- **Sound-color / chromesthesia specifically: ~0.2%** in the Simner sample. It is a comparatively *uncommon* synesthesia variant, not one of the more prevalent forms.

The widely-cited "1–4%" range applies to synesthesia overall, not chromesthesia specifically. Earlier characterizations describing chromesthesia as "one of the most common forms" appear to predate the population screening of Simner et al. (2006), which placed sound-color well below grapheme-color and sequence-color forms.

Key established properties of chromesthesia include:

- **Automaticity**: Color experiences are involuntary, not deliberate visualizations (Cytowic, 1989).
- **Consistency**: Individual mappings are highly stable over time. The Eagleman Synesthesia Battery scoring uses a consistency threshold (typically >0.7 on the test–retest distance metric) to discriminate genuine synesthetes; consistency >70% over months-to-years is characteristic of natural synesthetes (Eagleman et al., 2007; Simner et al., 2006).
- **Idiosyncrasy**: No universal pitch-to-color mapping exists across individuals. The composers Scriabin and Rimsky-Korsakov — historically the most-cited "synesthete composers" — disagreed on most color assignments (notable agreement: D major as a golden/yellow), despite working in adjacent traditions (Day, 2019). The scholarly consensus is that Scriabin's color system was **intellectually constructed** from Theosophical and circle-of-fifths principles rather than a genuine perceptual phenotype (Galeyev & Vanechkina, 2001; Spence & Di Stefano, 2022). Rimsky-Korsakov's reports are more consistent with genuine experience.
- **Pitch-height–brightness covariance**: The single most consistent cross-individual pattern is that higher pitches are associated with lighter/brighter colors and lower pitches with darker colors. This holds among both synesthetes and non-synesthetes (Marks, 1974; Spence & Di Stefano, 2022; Saitis & Wallmark, 2024).
- **Pitch-hue is the weakest cross-modal axis**. When brightness and saturation are controlled, there is **no robust population-level pitch-to-*hue* correspondence**; emotional/affective mediation provides a more parsimonious account of apparent hue associations (Spence & Di Stefano, 2022). Timbre descriptors (bright/dark/warm) similarly predict lightness and saturation but not specific hue (Saitis & Wallmark, 2024). This means a pitch-to-hue mapping is *not* exploitable as a natural correspondence; it must be **trained** to take hold.
- **Structural brain differences in natural synesthetes**: Synesthetes show altered cortical myelin content (32 regions with more myelin, 38 with less) compared to controls (Ward et al., 2024), along with altered functional connectivity. However, **earlier claims of V4-localized "hyper-connectivity" are not well supported**: Hupé, Bordier & Dojat (2012) found that color-selective cortex was *not* activated by synesthetic colors, and Ward et al. (2024) actually report a *flatter* (less hub-spoke-organized) connectome in synesthetes — not the focal hyperconnectivity earlier accounts proposed.

### 1.1 Neurological Models

Two principal mechanistic accounts of synesthesia are debated:

**Cross-activation model** (Ramachandran & Hubbard, 2001): Synesthesia arises from anomalously dense structural connections between adjacent cortical regions — in the case of grapheme-color synesthesia, between fusiform grapheme-recognition areas and the V4/V8 color region. The model has been weakened by subsequent imaging work (Hupé et al., 2012) showing that color-selective cortex is not the site of synesthetic color experience.

**Disinhibited feedback model** (Grossenbacher & Lovelace, 2001): Synesthetic percepts arise not from structural hyperconnectivity but from disinhibited feedback from higher-order multimodal regions to primary sensory areas. Under this model, the connections exist in all brains but are normally suppressed.

A 2019 study found that approximately 5 minutes of dark adaptation facilitated auditory-evoked visual percepts in ~50% of non-synesthetes (Nair & Brang, 2019). These percepts included vivid colors and Klüver-style geometric form-constants characteristic of sensory deprivation; whether they constitute "synesthesia-like" experiences in the strict phenomenological sense is the authors' framing rather than an established equivalence. The rapid timescale is incompatible with structural change but consistent with altered inhibitory tone, providing support for the disinhibited feedback view and suggesting that some form of cross-modal coupling may be a latent capacity in many human brains.

---

## 2. Can Synesthesia Be Induced?

The induction hypothesis rests on a smaller and more qualified evidence base than is sometimes implied. The strongest evidence is for behavioral acquisition of automatic associations; evidence for full phenomenological color experience is weaker and the effects appear to decay without maintenance.

### 2.1 Key Induction Studies

**Bor, Rothen, Schwartzman, Clayton, & Seth (2014)** — *Scientific Reports*, "Adults can be trained to acquire synesthetic experiences"
- N = 14 (training group), nine weeks of adaptive training (30 min/day), 13 specific grapheme-color pairings.
- Physiological measure: **Skin Conductance Response (SCR)**, not ERPs. The study included **no fMRI and no EEG** — there is no measurement of "early visual cortex activation" in this paper.
- Most participants reported subjective color experiences for achromatic letters, both during and outside training sessions.
- Critically, **effects largely faded by the 3-month retest**: participants had "largely lost the experience of 'seeing' colors when thinking about the letters" (Rothen, 2014). Stroop-like behavioral interference persisted in attenuated form; phenomenological color experience did not.
- The authors explicitly do not claim to have created genuine synesthetes.

**Colizoli, Murre, & Rouw (2012)** — *PLOS ONE*
- Participants read a novel printed with **only four letters colored** (a, e, s, t in red/orange/green/blue), over 2–4 weeks (cumulative reading on the order of hours, not 30 min/day).
- Modified Stroop showed acquired automatic letter–color interference effects.
- Subjective color experience was *weaker* than behavioral effects: the direct survey item "I am experiencing color when I see certain letters" did not correlate with behavioral effects, though a subset of participants did report internal color experiences (r ≈ 0.51 with Stroop in that subset).
- A perceptual-crowding task did not reach significance (p = .097).

**Terhune, Tai, Cowey, Popescu, & Cohen Kadosh (2011)** — *Current Biology* 21(23), 2006–2009
- Genuine grapheme-color synesthetes showed approximately 3-fold lower phosphene thresholds in V1 under TMS than non-synesthete controls.
- **This is a between-group trait comparison, not a training effect.** The lower thresholds reflect pre-existing cortical excitability differences in natural synesthetes, not something the study induced. The paper does not establish that training raises cortical excitability in non-synesthetes.

**Nair & Brang (2019)** — *Consciousness and Cognition*
- After 5 minutes of dark adaptation, ~50% of non-synesthetes reported visual percepts in response to sounds.
- Percepts included "vivid colors and Klüver form-constants" — the latter being geometric hallucination patterns (gratings, lattices, tunnels) characteristic of sensory deprivation, ganzfeld, and similar states. The authors frame these as "synesthesia-like"; a more skeptical reading is that they are sensory-deprivation phosphenes modulated by sound. Treat the framing with appropriate epistemic care.

### 2.2 Training Characteristics

What the literature actually supports:

- **Duration**: Bor et al. (2014) showed effects after nine weeks of daily training; full phenomenological experience faded by three months without maintenance. Shorter protocols (≤10 days) produce behavioral but not phenomenological markers.
- **Daily practice volume**: Bor et al. used 30 min/day specifically. Generalizing to "studies suggest 30 min/day" overstates the converging evidence; one well-controlled study used this volume.
- **Active engagement**: Active training outperforms passive exposure controls — the learner must engage with the association, not merely be exposed to it.
- **Consistency of the mapping**: Once established, natural synesthetic associations are highly stable. Inconsistency in the trained mapping during induction would defeat the protocol.
- **Durability without maintenance is poor**: The Bor 2014 retest data are the clearest evidence here. **Plan for ongoing maintenance practice after the active induction phase.**
- **Saturation**: There is no published evidence specifically establishing that moderate saturation outperforms maximum for synesthesia conditioning. The general conditioning literature, if anything, suggests higher-saliency stimuli condition faster. The "moderate is better" intuition may have ergonomic merit (avoiding visual fatigue across 30+ min sessions) but is not an evidence-based parameter.

### 2.3 Relevance to Pitch-Color Synesthesia (and an honest caveat)

The majority of induction studies have used grapheme-color (letter-color) synesthesia. Direct evidence for inducing chromesthesia is essentially absent in the published literature. The argument by analogy is: if consistent, repeated co-occurrence of a stimulus and a color can produce automatic associations for letters, the same mechanism should in principle support associations for pitches.

The key empirical study of natural pitch-class-color synesthesia — Itoh, Takimoto, & Akatsuka (2017, *Scientific Reports*) — found something important that complicates this:

> In 15 individuals with confirmed pitch-class color synesthesia, **color was determined by the verbal label of the note** (do, re, mi…), **not raw acoustic frequency**. Enharmonic pitches (e.g., C♯ vs. D♭) at identical frequency produced *different* colors depending on the name the synesthete used. The proposed mechanism is two-step: pitch → name → color.

This is significant for the project's design. Natural pitch-class-color synesthesia is name-mediated. A continuous frequency-based mapping does not implement that mechanism. See §4 for how this experiment addresses this — partly by leveraging Hindustani solfège, partly by deliberately and self-consciously departing from Itoh's finding.

---

## 3. Pitch-to-Color Mapping: Design Rationale

### 3.1 Empirical Basis (Itoh 2017)

Itoh, Takimoto, & Akatsuka (2017) reported a **linear rainbow hue progression** in 15 pitch-class-color synesthetes: *do* (C) at red (~0 radians), *si* (B) at violet (~2π), with hue increasing approximately linearly across the solfège scale. Saturation decreased gradually across the scale. Pitch class mapped to the hue–saturation plane; pitch height mapped to brightness.

The spectral/linear arrangement is therefore empirically attested in genuine synesthetes — not as a universal individual mapping (no such universal exists) but as the *aggregate* pattern across this population. The circle-of-fifths arrangement (Scriabin's intellectual construction) was *not* observed empirically.

### 3.2 The Sa-Anchored Spectral Mapping

The design uses a spectral hue cycle, continuous in frequency, anchored to the practitioner's tonic. For this subject (Sa fixed at C#), the reference frequency is set to **C#0 = 17.3239 Hz**, placing Sa at the warmest hue (red, OKLCH 29°) and tracing the rainbow forward through the swaras to Ni at violet (~277°).

**Why anchor to Sa (and not to C as the published literature does):** Itoh's synesthetes were Japanese-trained musicians using solfège (do = C); the published rainbow runs from C = red. For this subject, the perceptually-load-bearing pitch is Sa (C#), not C. Anchoring the spectrum to Sa makes the swara progression align with the rainbow:

- **Sa** (C#) = red (29°)
- **re** komal (D) = red-orange (52°)
- **Re** shuddha (D#) = orange (75°)
- **ga** komal (E) = yellow (97°)
- **Ga** shuddha (F) = yellow-green (119°)
- **Ma** shuddha (F#) = green (142°)
- **Ma** teevra (G) = teal (165°)
- **Pa** (G#) = cyan (187°)
- **dha** komal (A) = light blue (210°)
- **Dha** shuddha (A#) = blue (232°)
- **ni** komal (B) = indigo (255°)
- **Ni** shuddha (C) = violet (277°)
- **Sa** (next octave, C#) = red, wrap

This is still **absolute frequency → color** (every C# in the universe → red, every D → red-orange). Sa-anchoring is a 1-semitone shift of the reference frequency; the mapping is not made tonic-relative or movable. If the subject ever transposed to a different scale, all the colors would shift accordingly — which is acceptable because the subject's practice is fixed at scale C#.

### 3.3 Continuous Frequency, Not Discrete Pitch-Class — Deliberate Departure from Itoh

The mapping is continuous in frequency: `phase = log₂(f / 17.3239 Hz) mod 1.0`. Any pitch — including microtonal pitches between semitones — receives a unique, interpolated color. No discrete bucketing occurs.

This is **a deliberate departure from Itoh's name-mediated finding**, and the central hypothesis the experiment tests. Two reasons motivate this choice for this subject:

1. **Hindustani vocal practice is inherently continuous.** The fundamental ornaments of the tradition — *meend* (slide), *gamaka* (oscillation), *kan* (grace note) — are continuous pitch trajectories, not discrete note sequences. A discrete-quantized color mapping would visually freeze on a single color during a meend; a continuous mapping tracks the slide as a color sweep. This is more faithful to what the practitioner actually does with their voice.
2. **The experiment's interesting question is whether continuous frequency-binding can be acquired at all.** Itoh's data say natural synesthetes have name-mediated discrete bindings. If this protocol succeeds in inducing *continuous* frequency-color binding, it is evidence for a learnable mechanism distinct from the natural pitch-class form. If it fails, that is also informative.

**Practical convergence with name-mediation, for this subject specifically:** Because Sa is permanently fixed at C# in this practitioner's tradition, name and frequency are coupled — every Sa is C#, every Re is D#, etc. Hindustani vocalization during practice (singing "Sa, Re, Ga…" while watching the color) supplies the name-mediated reinforcement that Itoh's mechanism would predict, while the continuous mapping additionally provides reinforcement for the intermediate pitches that occur during meends and gamakas. The protocol therefore covers both possibilities: if the brain prefers a name-mediated representation, it has the names; if it can acquire a frequency-mediated representation, it has the continuous signal.

### 3.4 Pitch-Height to Lightness

The L-mapping is:

```
L = 0.25 + (clamp(octave_float, 1, 7) − 1) / 6 × 0.65
```

where `octave_float = log₂(f / 17.3239 Hz)`.

This produces a monotonic, perceptually-linear-in-OKLCH brightness across the range **C1 (~33 Hz) to C7 (~2093 Hz)**, which covers virtually all pitched musical instruments. Pitches outside this range are clamped at L = 0.25 (below C1) or L = 0.90 (above C7) so they still produce a valid color, but with reduced contrast at the extremes.

Reference points relevant to this subject's vocal range:

| Pitch | Octave_float | L | Context |
|---|---|---|---|
| C1 | 0.917 → clamp 1.0 | 0.25 | contrabass low |
| C2 | 1.917 | 0.350 | bass low |
| C#3 (Sa mandra) | 3.000 | **0.467** | tenor low |
| C4 (middle C) | 3.917 | 0.566 | |
| C#4 (Sa madhya) | 4.000 | **0.575** | tenor middle |
| C5 | 4.917 | 0.674 | |
| C#5 (Sa taar) | 5.000 | **0.683** | tenor top |
| C6 | 5.917 | 0.783 | soprano top |
| C7 | 6.917 | 0.891 | piccolo top |

The practitioner's three saptaks (mandra, madhya, taar) land at L ≈ 0.47, 0.58, 0.68 — evenly spaced and well inside the visible dynamic range. Pitches outside the vocal range still produce monotonic-extrapolable brightness within the trained slope, so the learned rule should generalize to instruments and voices the practitioner does not produce themselves.

**Why not stretch L across 0–1?** Below L ≈ 0.20 and above L ≈ 0.90, the sRGB-displayable chroma for most hues collapses sharply, meaning the hue identity of low and high pitches is lost (every low note looks black-tinted, every high note looks near-white). The chosen range trades a small amount of dynamic-range theater for guaranteed hue legibility across the practical pitch range.

### 3.5 Velocity to Chroma

```
C = 0.12 + (velocity / 127) × 0.06    →    C ∈ [0.12, 0.18]
```

Loud = more saturated; soft = more muted. This is a *forced* design choice rather than an evidence-driven one: the primary loudness cross-modal correspondence in the literature is loudness → brightness (Marks, 1974), but pitch already occupies lightness in this design. Velocity-to-chroma is a documented secondary loudness correlate (Caivano, 1994) and a defensible compromise.

The chroma ceiling (0.18) is chosen to remain inside the sRGB gamut for most hue/lightness combinations in the active range. The OKLCH→sRGB conversion (§3.7) applies proper gamut mapping for the remaining edge cases.

A nuance worth noting: Itoh's synesthetes showed saturation correlating with **pitch class** (lower-numbered solfège notes more saturated than higher-numbered ones), *not* with loudness. The mapping here therefore diverges from natural synesthesia on this dimension as well. This is acknowledged rather than hidden.

### 3.6 Perceptual Color Space: OKLCH

Colors are computed in OKLCH (Ottosson, 2020), the cylindrical form of OKLab. Two failures of older perceptual spaces motivate this choice:

- **Blue-purple problem**: In CIELAB, reducing chroma on a blue shifts its hue toward purple. OKLab is fit to fix this; hue is approximately stable under chroma changes.
- **Chroma dip on interpolation**: In CIELAB Cartesian space, interpolating between saturated complementary colors passes through a desaturated gray midpoint. OKLab interpolation preserves chroma.

OKLab is the **default interpolation space in CSS Color Level 4** and Adobe Photoshop's "Perceptual" gradient mode. OKLab is **supported** (not default) as a perceptual blend mode in Unity and Godot. OKLCH is the cylindrical form, used here for direct hue-angle assignment.

Other perceptual spaces considered:

- **HSLuv/HPLuv** (CIELUV-based): guarantees monotonic perceived lightness, but inherits CIELUV's blue-purple shift and has worse hue uniformity than OKLab.
- **CAM16-UCS**: marginally more accurate perceptually, but numerically heavier and still exhibits some blue-purple residue.
- **JzCzhz, ICtCp**: HDR-targeted; no advantage at sRGB display levels.

For an sRGB-output, single-color full-screen display where hue stability under varying chroma matters (because velocity varies), OKLCH dominates the alternatives.

### 3.7 Gamut Mapping

The OKLCH → sRGB pipeline uses **CSS Color 4 gamut mapping** (chroma reduction at constant L and H): if the requested OKLCH color is out of sRGB gamut, chroma is binary-searched downward until the color enters gamut, preserving the requested hue exactly. A small per-channel clip is then applied to handle floating-point edge cases (well below the ΔE_OK just-noticeable difference threshold of ~0.02).

This replaces naive per-channel RGB clamping. Per-channel clamping silently shifts hue — clipping the dominant channel reduces it more than the others, moving the chromaticity coordinates and rotating the perceived hue. For a tool whose value rests on consistent pitch-to-color identity over weeks of training, per-channel clamping would introduce a velocity-and-pitch-dependent hue drift; gamut mapping eliminates it.

### 3.8 What Was Considered and Rejected

**Circle-of-fifths mapping (Scriabin)**: Empirically not what Itoh's synesthetes show. Theoretically elegant for tonal music — harmonically related notes get adjacent colors — but the empirical case for spectral/linear is stronger.

**Discrete 12-bin hue quantization**: Would more faithfully replicate Itoh's name-mediated discrete bindings, but would mismatch the continuous gamakas of Hindustani vocal practice. The continuous mapping is the more interesting research question for this subject.

**Tonic-relative ("movable Sa") coloring**: Would make colors invariant under transposition. Rejected because (a) the subject's practice is fixed at scale C#, so this would have no practical effect, and (b) the experiment is testing absolute frequency-binding, not relative-pitch-class binding.

---

## 4. Protocol Design

### 4.1 Training Parameters

| Parameter | Value | Basis |
|---|---|---|
| Session duration | 30–60 min/day | Bor et al. (2014); subject's existing riyaaz routine |
| Active induction period | 9 weeks minimum, 12 weeks target | Bor et al. (2014) used 9 weeks |
| Maintenance phase | Indefinite | Bor effects faded by 3-month retest without maintenance |
| Mode | Active vocal + MIDI keyboard | Active > passive in induction literature |
| Vocalization | Hindustani swara naming during practice | Aligns with Itoh's name-mediation mechanism |
| Environment | Dark room, fullscreen display on secondary monitor | Sensory priming; Nair & Brang (2019) effect |
| Mapping consistency | Never change the mapping | Stability is the load-bearing variable |
| Audio-visual sync | Single audio buffer + 60 Hz redraw (~30–50 ms typical) | Comfortably inside the audiovisual binding window (~80–185 ms; Spence & Squire, 2003) |

### 4.2 Practice Structure

The plugin renders a borderless fullscreen color on a secondary display while the DAW is operated on the primary. The practice session uses both a MIDI keyboard (typically driving a tanpura drone and providing reference swara pitches) and the practitioner's voice.

Suggested daily session:

1. **Warm-up (5 min)**: Tanpura on Sa; sing held Sa, Pa, upper Sa while watching the color settle. Build association between the vocalized name + the held pitch + the color.
2. **Aroha–avaroha (10 min)**: Slowly ascend and descend the chosen raga's scale, vocalizing each swara and watching the color step. Try to mentally pre-image the color before playing the next note.
3. **Alankars / paltas (10 min)**: Standard ornamental scale exercises. The point is consistent repetition of swara-color pairings.
4. **Meend / gamaka work (10 min)**: Practice continuous slides between adjacent swaras, watching the color sweep. This is the most informative test of continuous frequency-binding.
5. **Free bandish / vocal phrasing (10–15 min)**: Sing fragments of bandishes or improvise in the raga. By now the practitioner is mostly attending to the music; the color presentation runs as ambient peripheral input.

### 4.3 Pre-Registered Success Criteria

Written before training begins; evaluated at weeks 3, 6, 9 (active phase) and at 3 and 6 months (maintenance). The point of pre-registration is to defend against confirmation bias and demand characteristics in self-report.

**Behavioral markers (replicating Bor/Colizoli paradigm in self-test form):**

- **B1 — Stroop-like incongruence**: Display a color while playing a randomly-selected pitch. Self-rate "how 'right' does this pairing feel" on a 1–7 scale. Track mean rating gap between congruent (pitch-matched-to-color) and incongruent trials. **Success criterion: gap of ≥2 scale points consistently by week 9.**
- **B2 — Anticipation accuracy**: With fullscreen window black, name a swara aloud, then mentally produce the expected color. Reveal the actual color. Score by hue-angle error in degrees. **Success criterion: median hue error <30° (~1 semitone) by week 9.**

**Phenomenological markers (harder; subject to demand-characteristic caveat):**

- **P1 — Spontaneous percept journal**: Dated log of any unsolicited color experiences during music listening *outside* practice. Distinguish "I deliberately imagined" from "color appeared without effort." **Success indicator: ≥1 spontaneous percept per week by week 9.**
- **P2 — Imagery vs. automaticity rating**: Weekly 1–7 rating of "when I hear/play a note, does the color feel automatic vs. deliberately conjured?" **Success indicator: monotonic increase across weeks; ≥5/7 by week 9.**

**Decay markers (3-month, 6-month retest):**

- Re-run B1, B2, P1, P2. The Bor 2014 result predicts P-markers will decay more than B-markers. Quantify the decay; relate to maintenance practice frequency during the post-active period.

### 4.4 Threats to Validity

- **Demand characteristics**: Self-report measures are vulnerable to motivated reporting. The B1/B2 quantitative markers are less vulnerable than P1/P2.
- **Imagery vs. automaticity conflation**: Deliberately imagining red when hearing Sa is not the same as automatic synesthetic color experience. P2 is designed to track this; honest weekly rating matters more than the trend looking favorable.
- **Single-subject n=1**: Results do not generalize statistically. The experiment is meaningful for the practitioner, not for the field.

---

## 5. Hypotheses

**Primary hypothesis (induction):** Daily 30–60 min sessions over 9–12 weeks, combining MIDI-driven full-screen color display with active Hindustani vocal practice and swara vocalization, will produce measurable acquired pitch-to-color associations as defined by markers B1 and B2.

**Secondary hypothesis (mapping fidelity):** If induced, the associations will reflect the trained Sa-anchored spectral mapping rather than an arbitrary or idiosyncratic alternative.

**Tertiary hypothesis (mechanism):** Phenomenological color experience (P1, P2) will lag behavioral markers and will require ongoing maintenance practice past the active induction phase to persist (predicted from Bor 2014 decay data).

**What this experiment does NOT predict:** That the induced associations will match those of natural pitch-class-color synesthetes. Natural synesthetes show name-mediated discrete bindings; this protocol trains a frequency-mediated continuous mapping. Even if all markers succeed, the induced phenotype will differ from Itoh's subjects on at least three dimensions (frequency vs. name binding; continuous vs. discrete; chroma tied to velocity rather than pitch class). This is by design.

**Null hypothesis:** No measurable acquired associations form within the training period; behavioral markers remain at chance, no spontaneous percepts occur.

---

## 6. Limitations and Considerations

- **n=1 self-experiment**: No statistical generalization possible.
- **Pitch-hue is the weakest cross-modal axis**: Spence & Di Stefano (2022) and Saitis & Wallmark (2024) find no robust population pitch-to-*hue* correspondence. This protocol relies on **trained association**, not exploitation of a natural correspondence — pitch-brightness has natural support; pitch-hue does not.
- **Deliberate departure from natural synesthesia**: The continuous frequency-binding goal is explicitly distinct from the discrete name-binding natural synesthetes show (Itoh, 2017). If successful, the induced association is a novel artificial phenotype, not a replication.
- **Demand characteristics**: Self-report dominates the assessment. Pre-registration of B1/B2 quantitative markers (§4.3) is the principal defense.
- **Mapping arbitrariness**: The Sa-anchored spectral mapping is *one* defensible mapping, not the only one. Consistency of the chosen mapping matters more than its specific form, but the choice of mapping does shape what gets induced.
- **Decay without maintenance**: Bor 2014's 3-month retest is the cautionary data. Plan for indefinite low-frequency maintenance practice past the active induction phase.
- **MIDI-driven, not audio-driven**: The plugin reads MIDI; meends and gamakas in the *voice itself* do not drive the colors. Only the reference MIDI keyboard pitches do. Audio pitch detection (driving colors directly from voice) is a possible future extension; the present protocol uses keyboard reference for the visual signal alongside vocal name reinforcement.

---

## 7. References

Bor, D., Rothen, N., Schwartzman, D. J., Clayton, S., & Seth, A. K. (2014). Adults can be trained to acquire synesthetic experiences. *Scientific Reports*, 4, 7089. https://doi.org/10.1038/srep07089

Caivano, J. L. (1994). Color and sound: Physical and psychophysical relations. *Color Research & Application*, 19(2), 126–133.

Colizoli, O., Murre, J. M., & Rouw, R. (2012). Pseudo-synesthesia through reading books with colored letters. *PLOS ONE*, 7(6), e39799. https://doi.org/10.1371/journal.pone.0039799

Cytowic, R. E. (1989). *Synesthesia: A Union of the Senses*. Springer.

Cytowic, R. E., & Eagleman, D. M. (2011). *Wednesday Is Indigo Blue: Discovering the Brain of Synesthesia*. MIT Press.

Day, S. A. (2019). *Synesthetes: A handbook*. CreateSpace.

Eagleman, D. M., Kagan, A. D., Nelson, S. S., Sagaram, D., & Sarma, A. K. (2007). A standardized test battery for the study of synesthesia. *Journal of Neuroscience Methods*, 159(1), 139–145.

Galeyev, B. M., & Vanechkina, I. L. (2001). Was Scriabin a synesthete? *Leonardo*, 34(4), 357–361.

Grossenbacher, P. G., & Lovelace, C. T. (2001). Mechanisms of synesthesia: Cognitive and physiological constraints. *Trends in Cognitive Sciences*, 5(1), 36–41. https://doi.org/10.1016/S1364-6613(00)01571-0

Hupé, J. M., Bordier, C., & Dojat, M. (2012). The neural bases of grapheme-color synesthesia are not localized in real color-sensitive areas. *Cerebral Cortex*, 22(7), 1619–1629. https://doi.org/10.1093/cercor/bhr236

Itoh, K., Takimoto, Y., & Akatsuka, T. (2017). Musical pitch classes have rainbow hues in pitch class-color synesthesia. *Scientific Reports*, 7, 17781. https://doi.org/10.1038/s41598-017-18150-y

Marks, L. E. (1974). On associations of light and sound: The mediation of brightness, pitch, and loudness. *The American Journal of Psychology*, 87(1/2), 173–188. https://doi.org/10.2307/1422011

Nair, A., & Brang, D. (2019). Inducing synesthesia in non-synesthetes: Short-term visual deprivation facilitates auditory-evoked visual percepts. *Consciousness and Cognition*, 70, 70–79. https://doi.org/10.1016/j.concog.2019.02.006

Ottosson, B. (2020). A perceptual color space for image processing. *Blog post*. https://bottosson.github.io/posts/oklab/

Ottosson, B. (2021). sRGB gamut clipping. *Blog post*. https://bottosson.github.io/posts/gamutclipping/

Ramachandran, V. S., & Hubbard, E. M. (2001). Synaesthesia: A window into perception, thought and language. *Journal of Consciousness Studies*, 8(12), 3–34.

Rothen, N. (2014). Quoted in EurekAlert press release on Bor et al. (2014). https://www.eurekalert.org/news-releases/713545

Saitis, C., & Wallmark, Z. (2024). Color and tone color: Audiovisual crossmodal correspondences and timbre. *Frontiers in Psychology*, 15, 1520131. https://doi.org/10.3389/fpsyg.2024.1520131

Simner, J., Mulvenna, C., Sagiv, N., Tsakanikos, E., Witherby, S. A., Fraser, C., Scott, K., & Ward, J. (2006). Synaesthesia: The prevalence of atypical cross-modal experiences. *Perception*, 35(8), 1024–1033. https://doi.org/10.1068/p5469

Spence, C., & Di Stefano, N. (2022). Coloured hearing, colour music, colour organs, and the search for perceptually meaningful correspondences between colour and sound. *i-Perception*, 13(3). https://doi.org/10.1177/20416695221092802

Spence, C., & Squire, S. (2003). Multisensory integration: Maintaining the perception of synchrony. *Current Biology*, 13(13), R519–R521.

Terhune, D. B., Tai, S., Cowey, A., Popescu, T., & Cohen Kadosh, R. (2011). Enhanced cortical excitability in grapheme-color synesthesia and its modulation. *Current Biology*, 21(23), 2006–2009. https://doi.org/10.1016/j.cub.2011.10.032

Ward, J., & Simner, J. (2022). Synesthesia: The current state of the field. In K. Sathian & V. S. Ramachandran (Eds.), *Multisensory Perception: From Laboratory to Clinic* (pp. 295–319). Academic Press.

Ward, J., Caulton, D., Frankland, M., et al. (2024). Synesthesia is linked to large and extensive differences in brain structure and function as determined by whole-brain biomarkers derived from the HCP (Human Connectome Project) cortical parcellation. *Cerebral Cortex*, 34(11), bhae446. https://doi.org/10.1093/cercor/bhae446

---

## Appendix A: Frequency-to-Color Mapping

Given audio frequency `f` in Hz:

```
f_ref        = 17.3239 Hz                       (C#0, Sa for scale C#)
octave_float = log₂(f / f_ref)                  (continuous; no floor)
phase        = octave_float mod 1.0             ∈ [0.0, 1.0)

OKLCH:
  H = 29.0 + phase × 271.0                                   (degrees; Sa=29°, Ni=277°)
  L = 0.25 + (clamp(octave_float, 1.0, 7.0) − 1.0) / 6.0 × 0.65
  C = 0.12 + (velocity / 127) × 0.06                          (∈ [0.12, 0.18])
```

### 12-TET swara reference values (madhya saptak)

| Swara | Western | Freq (Hz, A4=440) | Phase | OKLCH H | Approx. color |
|---|---|---|---|---|---|
| Sa | C#4 | 277.18 | 0.000 | 29.0° | Red |
| re (komal) | D4 | 293.66 | 0.083 | 51.6° | Red-orange |
| Re | D#4 | 311.13 | 0.167 | 74.2° | Orange |
| ga (komal) | E4 | 329.63 | 0.250 | 96.8° | Yellow |
| Ga | F4 | 349.23 | 0.333 | 119.3° | Yellow-green |
| Ma | F#4 | 369.99 | 0.417 | 141.9° | Green |
| MA (teevra) | G4 | 392.00 | 0.500 | 164.5° | Teal |
| Pa | G#4 | 415.30 | 0.583 | 187.1° | Cyan |
| dha (komal) | A4 | 440.00 | 0.667 | 209.7° | Light blue |
| Dha | A#4 | 466.16 | 0.750 | 232.2° | Blue |
| ni (komal) | B4 | 493.88 | 0.833 | 254.8° | Indigo |
| Ni | C5 | 523.25 | 0.917 | 277.4° | Violet |
| Sa (taar) | C#5 | 554.37 | 0.000 | 29.0° | Red |

Lightness for the same notes is determined by `octave_float`, so each saptak is a constant-hue cycle that brightens monotonically. For the practitioner's three saptaks:

- **Sa mandra** (C#3, octave_float=3.000): L = 0.467
- **Sa madhya** (C#4, octave_float=4.000): L = 0.575
- **Sa taar** (C#5, octave_float=5.000): L = 0.683

### Just intonation divergence (from Sa = C#4 = 277.18 Hz)

These divergences only manifest if the source supplies fractional pitch (via MIDI pitch bend or microtonal MIDI). With vanilla 12-TET MIDI input, the color is locked to 12-TET. The plugin accepts pitch bend; the figures below assume the user supplies it.

| JI interval (from Sa) | Ratio | JI freq (Hz) | Phase delta (oct) | Hue delta |
|---|---|---|---|---|
| Pa (Pythagorean 5th) | 3:2 | 415.77 | +0.00163 | +0.44° |
| Ga shuddha (just major 3rd) | 5:4 | 346.48 | −0.01140 | −3.09° |
| ni komal (harmonic 7th) | 7:4 | 485.07 | −0.02598 | −7.04° |

Whether these differences are *perceivable* depends on hue and viewing conditions. Conservative JND estimates for OKLCH hue in normal viewing are roughly 5–10°, so the Pa difference is below threshold, the Ga shuddha difference is marginal, and the harmonic-7th difference is reliably visible. The mapping is technically continuous regardless of whether the user can perceive small deltas.

---

## Appendix B: OKLCH to sRGB Conversion (with Gamut Mapping)

```
// 1. OKLCH → OKLab
h_rad = H × (π / 180)
a = C × cos(h_rad)
b = C × sin(h_rad)

// 2. OKLab → LMS (cube-root intermediate, Ottosson coefficients)
l_ = L + 0.3963377774·a + 0.2158037573·b
m_ = L − 0.1055613458·a − 0.0638541728·b
s_ = L − 0.0894841775·a − 1.2914855480·b
l = l_³,  m = m_³,  s = s_³

// 3. LMS → linear RGB
r =  4.0767416621·l − 3.3077115913·m + 0.2309699292·s
g = −1.2684380046·l + 2.6097574011·m − 0.3413193965·s
b = −0.0041960863·l − 0.7034186147·m + 1.7076147010·s

// 4. Gamut mapping (CSS Color 4): if (r,g,b) outside [0,1]³,
//    binary-search C downward at constant L and H until in gamut,
//    then re-run steps 1–3 with the reduced C.

// 5. Linear → sRGB gamma (IEC 61966-2-1)
sRGB(x) = x ≤ 0.0031308 ? 12.92·x : 1.055·x^(1/2.4) − 0.055
```

Reference: Ottosson (2020) for the matrices; Ottosson (2021) for the gamut-clipping discussion; W3C CSS Color Module Level 4 for the gamut mapping algorithm.
