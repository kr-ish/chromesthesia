#include "FullscreenColorWindow.h"
#include "PluginProcessor.h"

namespace {

// Swara names for the calibration palette (Sa-anchored, Bhatkhande shorthand:
// lowercase = komal, uppercase = shuddha, MA = teevra Ma). Hue is computed at
// paint time from the processor's current hue range, so the palette tracks the
// 271° arc vs 360° wrap TEST TOGGLE. If Sa does not read as pure red, Night
// Shift / True Tone / a third-party warmth app is likely active — see README
// "Display Setup".
const char* const kSwaraNames[12] = {
    "Sa", "re", "Re", "ga", "Ga", "Ma",
    "MA", "Pa", "dha", "Dha", "ni", "Ni"
};

constexpr float kCalibrationL = 0.58f;  // madhya saptak
constexpr float kCalibrationC = 0.15f;  // mid velocity

} // namespace

FullscreenColorWindow::FullscreenColorWindow (ChromesthesiaProcessor& p)
    : processor (p)
{
    setOpaque (true);
    // Intentionally NOT keyboard-focusable: a focus-grabbing window would
    // intercept computer-keyboard MIDI typed into the host. Controls live in
    // the plugin editor instead.
    setWantsKeyboardFocus (false);

    // Create a native borderless window.
    addToDesktop (juce::ComponentPeer::windowAppearsOnTaskbar);
    setVisible (false);

    startTimerHz (60);
}

FullscreenColorWindow::~FullscreenColorWindow()
{
    stopTimer();
}

void FullscreenColorWindow::showOnDisplay (int displayIndex)
{
    const auto& displays = juce::Desktop::getInstance().getDisplays();
    const int   n        = displays.displays.size();

    if (n == 0) return;
    displayIndex = juce::jlimit (0, n - 1, displayIndex);

    const auto& d = displays.displays[displayIndex];

    // Size to the full physical area of the display (includes taskbar/menu bar).
    setBounds (d.totalArea);
    setVisible (true);
    toFront (false);

    // Ask the peer to go truly fullscreen on this display. toFront(false) shows
    // it without stealing keyboard focus from the host (so computer-keyboard
    // MIDI keeps working).
    if (auto* peer = getPeer())
        peer->setFullScreen (true);
}

void FullscreenColorWindow::hide()
{
    if (auto* peer = getPeer())
        peer->setFullScreen (false);

    setVisible (false);
    isFading        = false;
    calibrationMode = false;
}

//==============================================================================
void FullscreenColorWindow::timerCallback()
{
    if (calibrationMode)
        return;  // calibration palette is static; no need to repaint

    const bool held = processor.isNoteHeld();

    // Detect note-off edge: transition from held → released.
    if (wasHeld && !held)
    {
        fadeFromColor  = processor.getCurrentOKLCH();
        isFading       = true;
        fadeStartSecs  = juce::Time::getMillisecondCounterHiRes() / 1000.0;
    }
    wasHeld = held;

    repaint();
}

void FullscreenColorWindow::setCalibration (bool on)
{
    calibrationMode = on;
    repaint();
}

void FullscreenColorWindow::paint (juce::Graphics& g)
{
    if (calibrationMode)
        paintCalibration (g);
    else
        paintLiveColor (g);
}

void FullscreenColorWindow::paintLiveColor (juce::Graphics& g)
{
    OKLCH display;

    if (processor.isNoteHeld())
    {
        isFading = false;
        display  = processor.getCurrentOKLCH();
    }
    else if (isFading)
    {
        const double elapsed = juce::Time::getMillisecondCounterHiRes() / 1000.0 - fadeStartSecs;
        const float  t       = static_cast<float> (juce::jlimit (0.0, 1.0, elapsed / FADE_DURATION_SECS));
        display = ColorEngine::fadeToBlack (fadeFromColor, t);

        if (t >= 1.0f)
            isFading = false;
    }
    else
    {
        display = { 0.0f, 0.0f, ColorEngine::HUE_MIN }; // black
    }

    g.fillAll (toJuceColour (display));
}

void FullscreenColorWindow::paintCalibration (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);

    const auto bounds = getLocalBounds();
    const int  w      = bounds.getWidth();
    const int  h      = bounds.getHeight();

    // Hue arc currently selected (271° spectral arc or 360° wrap — TEST TOGGLE),
    // so the palette matches whatever the live display is using.
    const float hueRange = processor.getHueRange();
    const bool  wrap     = processor.isHueWrap();

    // 12 vertical stripes across the full width.
    const float stripeW = static_cast<float> (w) / 12.0f;

    for (int i = 0; i < 12; ++i)
    {
        const float phase = static_cast<float> (i) / 12.0f;
        const float hue   = std::fmod (ColorEngine::HUE_MIN + phase * hueRange, 360.0f);
        const OKLCH c { kCalibrationL, kCalibrationC, hue };
        g.setColour (toJuceColour (c));
        g.fillRect (juce::Rectangle<float> (i * stripeW, 0.0f, stripeW, static_cast<float> (h)));
    }

    // Overlay: swara names + expected color description, white text with
    // black drop shadow for legibility against any background hue.
    const juce::Font labelFont (juce::Font::getDefaultMonospacedFontName(),
                                 juce::jmin (28.0f, stripeW / 4.0f),
                                 juce::Font::bold);
    g.setFont (labelFont);

    auto drawLabel = [&] (const juce::String& text, juce::Rectangle<int> box)
    {
        g.setColour (juce::Colours::black.withAlpha (0.7f));
        for (int dx = -1; dx <= 1; ++dx)
            for (int dy = -1; dy <= 1; ++dy)
                g.drawText (text, box.translated (dx, dy), juce::Justification::centred, false);
        g.setColour (juce::Colours::white);
        g.drawText (text, box, juce::Justification::centred, false);
    };

    for (int i = 0; i < 12; ++i)
    {
        const juce::Rectangle<int> box (static_cast<int> (i * stripeW), h / 2 - 30,
                                         static_cast<int> (stripeW), 60);
        drawLabel (juce::String (kSwaraNames[i]), box);
    }

    // Header and footer hints.
    const juce::Font hintFont (juce::Font::getDefaultMonospacedFontName(), 18.0f, juce::Font::plain);
    g.setFont (hintFont);

    drawLabel (juce::String ("Calibration palette  ·  hue arc: ") + (wrap ? "360 wrap" : "271 spectral")
                   + "   ·   use the plugin window to exit / switch arc / return to live color",
               juce::Rectangle<int> (0, h - 50, w, 30));

    // Expected anchors differ by mode (TEST TOGGLE). Sa = pure red in both.
    const juce::String verify = wrap
        ? "Verify: Sa = red,  Ma = cyan,  Pa = blue,  Dha = purple,  Ni = pink-red"
        : "Verify: Sa = red,  Pa = cyan,  Dha = blue,  Ni = violet";
    drawLabel (verify + "   (warm/off? disable Night Shift, True Tone, f.lux)",
               juce::Rectangle<int> (0, 20, w, 30));
}

juce::Colour FullscreenColorWindow::toJuceColour (OKLCH c) const
{
    const sRGB rgb = ColorEngine::oklchToSRGB (c);
    return juce::Colour::fromFloatRGBA (rgb.r, rgb.g, rgb.b, 1.0f);
}

void FullscreenColorWindow::refresh()
{
    repaint();
}
