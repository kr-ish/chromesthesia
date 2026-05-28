#pragma once
#include <cmath>
#include <cstdint>

struct OKLCH {
    float L = 0.0f;  // lightness: 0.0–1.0
    float C = 0.0f;  // chroma:    0.0–~0.37
    float H = 29.0f; // hue:       degrees (29°=red, 300°=violet)
};

struct sRGB {
    float r = 0.0f, g = 0.0f, b = 0.0f;  // 0.0–1.0, gamma-corrected

    uint8_t r8() const { return static_cast<uint8_t>(r * 255.0f + 0.5f); }
    uint8_t g8() const { return static_cast<uint8_t>(g * 255.0f + 0.5f); }
    uint8_t b8() const { return static_cast<uint8_t>(b * 255.0f + 0.5f); }
};

//==============================================================================
// ColorEngine: pure math, no JUCE dependency.
//
// Mapping design (Sa-anchored at C#0 for Hindustani vocal practice):
//   H = 29 + phase × 271          spectral red (Sa = C#) → violet (Ni = C)
//   L = 0.25 + (clamp(octave_float, 1, 7) − 1) / 6 × 0.65
//                                 monotonic pitch-height → brightness across
//                                 C1–C7 (covers all musical instruments;
//                                 vocal range C3–C5 lands at L=0.47–0.69).
//   C = 0.12 + (velocity/127) × 0.06   soft = muted, loud = vivid; ceiling
//                                       chosen to stay in sRGB gamut for most
//                                       hue/L combos. Out-of-gamut requests are
//                                       handled by chroma-reduction gamut
//                                       mapping in oklchToSRGB().
//
// where phase  = log2(f / F_REF) mod 1.0   (tuning-agnostic, continuous)
//       F_REF  = C#0 = 17.3239 Hz          (so Sa = C# → hue 29° = red)
//==============================================================================
class ColorEngine {
public:
    static constexpr float F_REF      = 17.3239f;  // C#0 (Sa, Hindustani scale C#)
    static constexpr float HUE_MIN    = 29.0f;     // OKLCH hue for red (Sa)
    static constexpr float HUE_RANGE  = 271.0f;    // red → violet span
    static constexpr float CHROMA_MIN = 0.12f;
    static constexpr float CHROMA_MAX = 0.18f;     // safely in sRGB gamut for
                                                    // most hue/L combinations

    // Compute display color from audio frequency and MIDI velocity (0–127).
    // Returns black (L=0, C=0) if freq <= 0.
    static OKLCH frequencyToOKLCH(float freq_hz, int velocity_0_127) noexcept;

    // Convert OKLCH to sRGB using Ottosson's exact matrices, with CSS Color 4
    // gamut mapping (chroma reduction at constant L and H) for out-of-gamut
    // requests. Hue is preserved exactly; per-channel clipping after gamut
    // mapping is below JND.
    static sRGB oklchToSRGB(OKLCH c) noexcept;

    // Interpolate L and C linearly, hold H constant.
    // Used for fade-to-black: blend(held, black, t) where t 0→1 over 500ms.
    static OKLCH fadeToBlack(OKLCH from, float t) noexcept;

    // Frequency from MIDI note number + pitch bend in semitones.
    // pitch_bend_semitones: typically in [-2, +2] for standard ±2 st range.
    static float midiToFrequency(int midi_note, float pitch_bend_semitones = 0.0f) noexcept;

private:
    static float linearToSRGB(float x) noexcept;
};
