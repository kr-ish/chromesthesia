#include "ColorEngine.h"
#include <algorithm>

OKLCH ColorEngine::frequencyToOKLCH(float freq_hz, int velocity) noexcept {
    if (freq_hz <= 0.0f)
        return { 0.0f, 0.0f, HUE_MIN };

    const float octave_float = std::log2(freq_hz / F_REF);
    const float phase        = octave_float - std::floor(octave_float); // 0.0–1.0
    const float vel          = std::clamp(velocity / 127.0f, 0.0f, 1.0f);

    return {
        0.10f + (std::clamp(octave_float, 0.0f, 8.0f) / 8.0f) * 0.80f, // L: continuous pitch height → brightness
        CHROMA_MIN + vel * (CHROMA_MAX - CHROMA_MIN), // C: soft=muted, loud=vivid
        HUE_MIN + phase * HUE_RANGE                  // H: C=red(29°)…B=violet(300°)
    };
}

sRGB ColorEngine::oklchToSRGB(OKLCH lch) noexcept {
    // OKLCH → OKLAB
    const float h = lch.H * (3.14159265358979323846f / 180.0f);
    const float a = lch.C * std::cos(h);
    const float b = lch.C * std::sin(h);
    const float L = lch.L;

    // OKLAB → LMS (via cube-root intermediate)
    const float l_ = L + 0.3963377774f * a + 0.2158037573f * b;
    const float m_ = L - 0.1055613458f * a - 0.0638541728f * b;
    const float s_ = L - 0.0894841775f * a - 1.2914855480f * b;

    const float l = l_ * l_ * l_;
    const float m = m_ * m_ * m_;
    const float s = s_ * s_ * s_;

    // LMS → linear RGB (Ottosson)
    const float r  =  4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s;
    const float g  = -1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s;
    const float bv = -0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s;

    // Gamut clamp then sRGB gamma
    return {
        linearToSRGB(std::clamp(r,  0.0f, 1.0f)),
        linearToSRGB(std::clamp(g,  0.0f, 1.0f)),
        linearToSRGB(std::clamp(bv, 0.0f, 1.0f))
    };
}

OKLCH ColorEngine::fadeToBlack(OKLCH from, float t) noexcept {
    const float s = std::clamp(1.0f - t, 0.0f, 1.0f);
    return { from.L * s, from.C * s, from.H };
}

float ColorEngine::midiToFrequency(int midi_note, float pitch_bend_semitones) noexcept {
    return 440.0f * std::pow(2.0f, (static_cast<float>(midi_note) + pitch_bend_semitones - 69.0f) / 12.0f);
}

float ColorEngine::linearToSRGB(float x) noexcept {
    if (x <= 0.0031308f) return 12.92f * x;
    return 1.055f * std::pow(x, 1.0f / 2.4f) - 0.055f;
}
