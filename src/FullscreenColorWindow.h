#pragma once
#include <JuceHeader.h>
#include "ColorEngine.h"
#include <functional>

class ChromesthesiaProcessor;

//==============================================================================
// FullscreenColorWindow
//
// A borderless top-level window that fills a chosen display with a solid
// OKLCH-derived color. Lives on the message thread.
//
// Keyboard:
//   - Escape : invokes onEscapeRequested (the editor uses this to exit
//              fullscreen and restore its UI)
//   - C      : toggle calibration palette (12 swara reference stripes with
//              labels) — useful for verifying Night Shift / True Tone /
//              third-party warmth is disabled before training
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
    bool keyPressed (const juce::KeyPress& key) override;

    // Called by the timer or externally to force an immediate repaint.
    void refresh();

    // Set by the editor; invoked when the user presses Escape on the
    // fullscreen window.
    std::function<void()> onEscapeRequested;

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

    // Calibration palette mode (toggled by 'C')
    bool calibrationMode { false };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FullscreenColorWindow)
};
