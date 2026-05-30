#pragma once
#include <JuceHeader.h>
#include "ColorEngine.h"

class ChromesthesiaProcessor;

//==============================================================================
// FullscreenColorWindow
//
// A borderless top-level window that fills a chosen display with a solid
// OKLCH-derived color. Lives on the message thread.
//
// It deliberately does NOT take keyboard focus: the practitioner may use the
// computer keyboard as a MIDI input in the host, and a focus-grabbing window
// would intercept those keystrokes (MIDI stops working). All controls —
// exit fullscreen, calibration palette, hue arc — live as buttons in the
// plugin editor instead.
//
// Lifecycle:
//   - Constructed with a reference to the processor (for polling color state).
//   - Call showOnDisplay(index) to open/move to a screen.
//   - Call hide() to dismiss without destroying.
//   - A 60Hz timer drives both note-held display and note-off fade.
//==============================================================================
class FullscreenColorWindow : public juce::Component,
                               private juce::Timer
{
public:
    explicit FullscreenColorWindow (ChromesthesiaProcessor& p);
    ~FullscreenColorWindow() override;

    void showOnDisplay (int displayIndex);
    void hide();

    void paint (juce::Graphics& g) override;

    // Calibration palette (12 swara reference stripes) — driven by an editor
    // button so the window needs no keyboard focus.
    void setCalibration (bool on);
    bool isCalibration() const noexcept { return calibrationMode; }

    // Called by the timer or externally to force an immediate repaint.
    void refresh();

private:
    void timerCallback() override;

    juce::Colour toJuceColour (OKLCH c) const;
    void paintLiveColor (juce::Graphics& g);
    void paintCalibration (juce::Graphics& g);

    ChromesthesiaProcessor& processor;

    // Fade state
    OKLCH  fadeFromColor {};
    bool   isFading      { false };
    double fadeStartSecs { 0.0 };
    static constexpr double FADE_DURATION_SECS = 0.5;

    // Last known note-held state, to detect transitions.
    bool wasHeld { false };

    // Calibration palette mode (toggled via the editor's Calibration button).
    bool calibrationMode { false };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FullscreenColorWindow)
};
