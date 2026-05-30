#include "PluginEditor.h"
#include "ColorEngine.h"

using namespace juce;

ChromesthesiaEditor::ChromesthesiaEditor (ChromesthesiaProcessor& p)
    : AudioProcessorEditor (&p), proc (p)
{
    setSize (W, H);

    // Title
    titleLabel.setText ("Chromesthesia", dontSendNotification);
    titleLabel.setFont (Font (18.0f, Font::bold));
    titleLabel.setJustificationType (Justification::centredLeft);
    addAndMakeVisible (titleLabel);

    // Display selector
    displayLabel.setText ("Display:", dontSendNotification);
    displayLabel.setJustificationType (Justification::centredRight);
    addAndMakeVisible (displayLabel);

    populateDisplayList();
    displayCombo.setSelectedId (1, dontSendNotification);
    addAndMakeVisible (displayCombo);

    // Fullscreen button
    fullscreenButton.setButtonText ("Go Fullscreen");
    fullscreenButton.onClick = [this] { toggleFullscreen(); };
    addAndMakeVisible (fullscreenButton);

    // TEST TOGGLE (temporary): 271° spectral arc vs 360° octave wrap. Switch is
    // button-only. Remove once the hue arc is chosen — see docs/science.md
    // Appendix C.
    hueModeButton.onClick = [this]
    {
        proc.setHueWrap (! proc.isHueWrap());
        updateHueModeButton();
        if (colorWindow) colorWindow->refresh(); // repaint palette if it is up
    };
    addAndMakeVisible (hueModeButton);
    updateHueModeButton();

    // Calibration palette toggle. Driven here (not by a fullscreen key) so the
    // color window never needs keyboard focus. Shown only while fullscreen.
    calibrationButton.setButtonText ("Calibration");
    calibrationButton.onClick = [this]
    {
        const bool on = ! colorWindow->isCalibration();
        colorWindow->setCalibration (on);
        calibrationButton.setButtonText (on ? "Live color" : "Calibration");
    };
    addChildComponent (calibrationButton); // hidden until fullscreen

    // Note label
    noteInfoLabel.setJustificationType (Justification::centredLeft);
    noteInfoLabel.setFont (Font (Font::getDefaultMonospacedFontName(), 13.0f, Font::plain));
    addAndMakeVisible (noteInfoLabel);

    // Create window now (hidden); it will be shown on demand. It takes no
    // keyboard focus — all controls are the buttons above.
    colorWindow = std::make_unique<FullscreenColorWindow> (proc);

    startTimerHz (30);
}

ChromesthesiaEditor::~ChromesthesiaEditor()
{
    stopTimer();
    if (colorWindow) colorWindow->hide();
}

//==============================================================================
void ChromesthesiaEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // Draw the live color swatch.
    const OKLCH oklch = proc.getCurrentOKLCH();
    const sRGB  rgb   = ColorEngine::oklchToSRGB (oklch);
    const Colour swatchColor = Colour::fromFloatRGBA (rgb.r, rgb.g, rgb.b, 1.0f);

    g.setColour (swatchColor);
    g.fillRect (swatchBounds);

    g.setColour (Colours::white.withAlpha (0.3f));
    g.drawRect (swatchBounds, 1);
}

void ChromesthesiaEditor::resized()
{
    auto area = getLocalBounds().reduced (12);

    // Title row
    titleLabel.setBounds (area.removeFromTop (28));
    area.removeFromTop (6);

    if (isFullscreen)
    {
        // Compact control bar — everything reachable without the keyboard.
        auto row = area.removeFromTop (26);
        fullscreenButton .setBounds (row.removeFromLeft (116));
        row.removeFromLeft (6);
        calibrationButton.setBounds (row.removeFromLeft (100));
        row.removeFromLeft (6);
        hueModeButton    .setBounds (row.removeFromLeft (124));
        swatchBounds = {};
        return;
    }

    // Windowed layout.
    auto controlRow = area.removeFromTop (26);
    displayLabel    .setBounds (controlRow.removeFromLeft (60));
    controlRow.removeFromLeft (6);
    displayCombo    .setBounds (controlRow.removeFromLeft (180));
    controlRow.removeFromLeft (8);
    fullscreenButton.setBounds (controlRow.removeFromLeft (140));

    area.removeFromTop (8);
    auto hueRow = area.removeFromTop (26);          // TEST TOGGLE row
    hueModeButton.setBounds (hueRow.removeFromLeft (200));

    area.removeFromTop (10);
    auto bottomRow = area.removeFromTop (70);
    swatchBounds = bottomRow.removeFromLeft (70);
    bottomRow.removeFromLeft (12);
    noteInfoLabel.setBounds (bottomRow);
}

//==============================================================================
void ChromesthesiaEditor::timerCallback()
{
    // Refresh swatch and note label.
    noteInfoLabel.setText (noteLabel(), dontSendNotification);
    repaint (swatchBounds);
}

void ChromesthesiaEditor::populateDisplayList()
{
    displayCombo.clear (dontSendNotification);
    const auto& displays = Desktop::getInstance().getDisplays();

    for (int i = 0; i < displays.displays.size(); ++i)
    {
        const auto& d = displays.displays[i];
        String name = "Display " + String (i + 1);
        if (d.isMain) name += " (primary)";
        displayCombo.addItem (name, i + 1); // item ID = index + 1
    }
}

void ChromesthesiaEditor::toggleFullscreen()
{
    if (! isFullscreen)
        enterFullscreen();
    else
        exitFullscreen();
}

void ChromesthesiaEditor::enterFullscreen()
{
    if (isFullscreen) return;

    const int selectedIndex = displayCombo.getSelectedId() - 1; // ID is index+1
    colorWindow->showOnDisplay (selectedIndex);

    fullscreenButton.setButtonText ("Exit Fullscreen");
    titleLabel.setText ("Chromesthesia — fullscreen", juce::dontSendNotification);

    // Hide windowed-only widgets; keep the control buttons reachable.
    displayLabel  .setVisible (false);
    displayCombo  .setVisible (false);
    noteInfoLabel .setVisible (false);
    calibrationButton.setButtonText ("Calibration");
    calibrationButton.setVisible (true);   // shown only while fullscreen

    isFullscreen = true;
    setSize (W, H_MINIMIZED);  // triggers resized()
}

void ChromesthesiaEditor::exitFullscreen()
{
    if (! isFullscreen) return;

    colorWindow->hide();   // also clears calibration mode

    fullscreenButton.setButtonText ("Go Fullscreen");
    titleLabel.setText ("Chromesthesia", juce::dontSendNotification);

    displayLabel  .setVisible (true);
    displayCombo  .setVisible (true);
    noteInfoLabel .setVisible (true);
    calibrationButton.setVisible (false);  // only relevant in fullscreen

    isFullscreen = false;
    setSize (W, H);  // triggers resized()
}

void ChromesthesiaEditor::updateHueModeButton()
{
    // TEST TOGGLE (temporary) — remove with the toggle once the arc is chosen.
    hueModeButton.setButtonText (proc.isHueWrap() ? "Hue arc: 360 wrap"
                                                  : "Hue arc: 271 spectral");
}

juce::String ChromesthesiaEditor::noteLabel() const
{
    if (!proc.isNoteHeld())
        return String();

    const int   note = proc.getCurrentMidiNote();
    const float freq = proc.getCurrentFrequency();

    static const char* names[] = {
        "C", "C#", "D", "D#", "E", "F",
        "F#", "G", "G#", "A", "A#", "B"
    };
    // Hindustani swara names (Sa-anchored at C#, Bhatkhande shorthand:
    // lowercase = komal, uppercase = shuddha, MA = teevra Ma).
    // Indexed by chromatic offset from Sa: (midi_note - 1) mod 12.
    static const char* swaras[] = {
        "Sa", "re", "Re", "ga", "Ga", "Ma",
        "MA", "Pa", "dha", "Dha", "ni", "Ni"
    };

    const int octave = (note / 12) - 1;
    const int swaraIdx = ((note - 1) % 12 + 12) % 12; // safe mod for negatives

    String label = String (names[note % 12]) + String (octave);
    label += " (" + String (swaras[swaraIdx]) + ")";
    label += "   " + String (freq, 1) + " Hz";

    const OKLCH c = proc.getCurrentOKLCH();
    label += "\nH " + String (c.H, 1) + "°  L " + String (c.L, 2) + "  C " + String (c.C, 3);

    return label;
}
