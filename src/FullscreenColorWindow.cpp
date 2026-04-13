#include "FullscreenColorWindow.h"
#include "PluginProcessor.h"

FullscreenColorWindow::FullscreenColorWindow (ChromesthesiaProcessor& p)
    : processor (p)
{
    setOpaque (true);

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
}

void FullscreenColorWindow::hide()
{
    if (auto* peer = getPeer())
        peer->setFullScreen (false);

    setVisible (false);
    isFading = false;
}

//==============================================================================
void FullscreenColorWindow::timerCallback()
{
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

void FullscreenColorWindow::paint (juce::Graphics& g)
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

juce::Colour FullscreenColorWindow::toJuceColour (OKLCH c) const
{
    const sRGB rgb = ColorEngine::oklchToSRGB (c);
    return juce::Colour::fromFloatRGBA (rgb.r, rgb.g, rgb.b, 1.0f);
}

void FullscreenColorWindow::refresh()
{
    repaint();
}
