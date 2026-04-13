#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FullscreenColorWindow.h"

//==============================================================================
// ChromesthesiaEditor
//
// Compact in-DAW UI:
//   - Display selector (ComboBox listing all connected monitors)
//   - "Go Fullscreen" / "Exit Fullscreen" toggle button
//   - Live color swatch showing the current pitch color
//   - Current note label (e.g. "C4  261.6 Hz")
//
// The FullscreenColorWindow is owned here and lives as long as the editor.
// The editor polls the processor at ~30Hz for the swatch and note label.
//==============================================================================
class ChromesthesiaEditor : public juce::AudioProcessorEditor,
                             private juce::Timer
{
public:
    explicit ChromesthesiaEditor (ChromesthesiaProcessor&);
    ~ChromesthesiaEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void timerCallback() override;
    void populateDisplayList();
    void toggleFullscreen();
    juce::String noteLabel() const;

    ChromesthesiaProcessor& proc;

    juce::Label      titleLabel;
    juce::Label      displayLabel;
    juce::ComboBox   displayCombo;
    juce::TextButton fullscreenButton;

    // Swatch: just a painted rectangle, updated via repaint().
    juce::Rectangle<int> swatchBounds;
    juce::Label          noteInfoLabel;

    std::unique_ptr<FullscreenColorWindow> colorWindow;
    bool isFullscreen { false };

    static constexpr int W = 380;
    static constexpr int H = 180;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChromesthesiaEditor)
};
