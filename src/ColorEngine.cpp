#include "ColorEngine.h"
#include <algorithm>

namespace {

struct LinearRGB { float r, g, b; };

LinearRGB oklchToLinearRGB(OKLCH lch) noexcept {
    const float h = lch.H * (3.14159265358979323846f / 180.0f);
    const float a = lch.C * std::cos(h);
    const float b = lch.C * std::sin(h);
    const float L = lch.L;

    const float l_ = L + 0.3963377774f * a + 0.2158037573f * b;
    const float m_ = L - 0.1055613458f * a - 0.0638541728f * b;
    const float s_ = L - 0.0894841775f * a - 1.2914855480f * b;

    const float l = l_ * l_ * l_;
    const float m = m_ * m_ * m_;
    const float s = s_ * s_ * s_;

    return {
         4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
        -1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
        -0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s
    };
}

bool inSRGBGamut(LinearRGB rgb) noexcept {
    constexpr float eps = 1.0e-4f;
    return rgb.r >= -eps && rgb.r <= 1.0f + eps &&
           rgb.g >= -eps && rgb.g <= 1.0f + eps &&
           rgb.b >= -eps && rgb.b <= 1.0f + eps;
}

} // namespace

OKLCH ColorEngine::frequencyToOKLCH(float freq_hz, int velocity, float hue_range) noexcept {
    if (freq_hz <= 0.0f)
        return { 0.0f, 0.0f, HUE_MIN };

    const float octave_float = std::log2(freq_hz / F_REF);
    const float phase        = octave_float - std::floor(octave_float); // 0.0–1.0
    const float vel          = std::clamp(velocity / 127.0f, 0.0f, 1.0f);

    // Lightness: monotonic across C1–C7 (covers virtually all musical
    // instruments). Vocal range C3–C5 lands at L≈0.47–0.69, centered on the
    // visible dynamic range for maximum perceptual contrast where most
    // training occurs while preserving extrapolation outside vocal range.
    const float L = 0.25f + (std::clamp(octave_float, 1.0f, 7.0f) - 1.0f) / 6.0f * 0.65f;

    // Hue wrapped into [0,360): a no-op for the 271° arc (max 300°), required
    // for the 360° wrap test mode where HUE_MIN + phase*360 can reach 389°.
    const float H = std::fmod(HUE_MIN + phase * hue_range, 360.0f);

    return {
        L,
        CHROMA_MIN + vel * (CHROMA_MAX - CHROMA_MIN),
        H
    };
}

sRGB ColorEngine::oklchToSRGB(OKLCH lch) noexcept {
    // CSS Color 4 gamut mapping: hold L and H, binary-search C downward until
    // the color enters sRGB. Without this, per-channel clamping after the
    // matrix transform shifts hue away from the OKLCH H we specified —
    // breaking the pitch-color consistency the conditioning protocol depends
    // on across velocity and lightness.
    LinearRGB linear = oklchToLinearRGB(lch);

    if (!inSRGBGamut(linear)) {
        OKLCH probe = lch;
        float lo = 0.0f, hi = lch.C;
        for (int i = 0; i < 16; ++i) {           // ~1e-5 chroma precision
            const float mid = 0.5f * (lo + hi);
            probe.C = mid;
            if (inSRGBGamut(oklchToLinearRGB(probe))) lo = mid;
            else                                      hi = mid;
        }
        probe.C = lo;
        linear  = oklchToLinearRGB(probe);
    }

    return {
        linearToSRGB(std::clamp(linear.r, 0.0f, 1.0f)),
        linearToSRGB(std::clamp(linear.g, 0.0f, 1.0f)),
        linearToSRGB(std::clamp(linear.b, 0.0f, 1.0f))
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
