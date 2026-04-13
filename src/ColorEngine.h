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
// Mapping design:
//   H = 29 + phase × 271          spectral red (C) → violet (B)
//   L = 0.10 + (octave/8) × 0.80  low=dark, high=bright
//   C = 0.12 + (velocity/127)×0.15 soft=muted, loud=vivid
//
// where phase = log2(f / F_REF) mod 1.0  (tuning-agnostic, continuous)
//       octave = floor(log2(f / F_REF))
//       F_REF  = C0 = 16.3516 Hz
//==============================================================================
class ColorEngine {
public:
    static constexpr float F_REF      = 16.3516f;  // C0
    static constexpr float HUE_MIN    = 29.0f;     // OKLCH hue for red (C)
    static constexpr float HUE_RANGE  = 271.0f;    // red → violet span
    static constexpr float CHROMA_MIN = 0.12f;
    static constexpr float CHROMA_MAX = 0.27f;

    // Compute display color from audio frequency and MIDI velocity (0–127).
    // Returns black (L=0, C=0) if freq <= 0.
    static OKLCH frequencyToOKLCH(float freq_hz, int velocity_0_127) noexcept;

    // Convert OKLCH to sRGB using Ottosson's exact matrices.
    // Simple gamut clamp (per-channel) — safe for our controlled palette.
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
