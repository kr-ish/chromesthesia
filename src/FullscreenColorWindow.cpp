#include "FullscreenColorWindow.h"
#include "PluginProcessor.h"

namespace {

// 12 swara reference colors for the calibration palette, all at madhya saptak
// lightness (L≈0.58) and a mid-range chroma (C=0.15). If any of these look
// off-spectrum on screen, Night Shift / True Tone / or a third-party warmth
// app is likely active — see README "Display setup" section.
struct SwaraRef {
    const char* name;
    float       hue_deg;
};

constexpr SwaraRef kCalibrationSwaras[12] = {
    { "Sa",  29.0f  },
    { "re",  51.6f  },
    { "Re",  74.2f  },
    { "ga",  96.8f  },
    { "Ga",  119.3f },
    { "Ma",  141.9f },
    { "MA",  164.5f },
    { "Pa",  187.1f },
    { "dha", 209.7f },
    { "Dha", 232.2f },
    { "ni",  254.8f },
    { "Ni",  277.4f }
};

constexpr float kCalibrationL = 0.58f;  // madhya saptak
constexpr float kCalibrationC = 0.15f;  // mid velocity

} // namespace

FullscreenColorWindow::FullscreenColorWindow (ChromesthesiaProcessor& p)
    : processor (p)
{
    setOpaque (true);
    setWantsKeyboardFocus (true);  // required for keyPressed to fire

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

    // Ask the peer to go truly fullscreen on this display.
    if (auto* peer = getPeer())
        peer->setFullScreen (true);

    // Take keyboard focus so Escape and C are received.
    grabKeyboardFocus();
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

bool FullscreenColorWindow::keyPressed (const juce::KeyPress& key)
{
    if (key == juce::KeyPress::escapeKey)
    {
        calibrationMode = false;
        if (onEscapeRequested) onEscapeRequested();
        return true;
    }

    const juce::juce_wchar ch = key.getTextCharacter();
    if (ch == 'c' || ch == 'C')
    {
        calibrationMode = ! calibrationMode;
        repaint();
        return true;
    }

    return false;
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

    // 12 vertical stripes across the full width.
    const float stripeW = static_cast<float> (w) / 12.0f;

    for (int i = 0; i < 12; ++i)
    {
        const auto& s = kCalibrationSwaras[i];
        const OKLCH c { kCalibrationL, kCalibrationC, s.hue_deg };
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
        const auto& s = kCalibrationSwaras[i];
        const juce::Rectangle<int> box (static_cast<int> (i * stripeW), h / 2 - 30,
                                         static_cast<int> (stripeW), 60);
        drawLabel (juce::String (s.name), box);
    }

    // Header and footer hints.
    const juce::Font hintFont (juce::Font::getDefaultMonospacedFontName(), 18.0f, juce::Font::plain);
    g.setFont (hintFont);

    drawLabel ("Calibration palette  |  press C to return  |  Esc to exit fullscreen",
               juce::Rectangle<int> (0, h - 50, w, 30));
    drawLabel ("Verify: Sa = pure red,  Pa = cyan,  Dha = blue,  Ni = violet "
               "(if these look warm/off, disable Night Shift, True Tone, and f.lux)",
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
