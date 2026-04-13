#pragma once
#include <JuceHeader.h>
#include "ColorEngine.h"
#include <atomic>

//==============================================================================
// ChromesthesiaProcessor
//
// Audio thread: receives MIDI note-on/off and pitch bend, converts the current
// held frequency to an OKLCH color, and stores it in atomics for the message
// thread to read without locking.
//
// The plugin outputs silence — it is used purely as a MIDI receiver.
//==============================================================================
class ChromesthesiaProcessor : public juce::AudioProcessor {
public:
    ChromesthesiaProcessor();
    ~ChromesthesiaProcessor() override = default;

    //==========================================================================
    // AudioProcessor interface
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "Chromesthesia"; }
    bool   acceptsMidi()   const override { return true; }
    bool   producesMidi()  const override { return false; }
    bool   isMidiEffect()  const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int  getNumPrograms() override                           { return 1; }
    int  getCurrentProgram() override                        { return 0; }
    void setCurrentProgram (int) override                    {}
    const juce::String getProgramName (int) override         { return {}; }
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock&) override   {}
    void setStateInformation (const void*, int) override     {}

    //==========================================================================
    // State read by message thread (lock-free)

    // Current OKLCH color for the held note (or black if none held).
    OKLCH getCurrentOKLCH() const noexcept {
        return { atomicL.load(), atomicC.load(), atomicH.load() };
    }

    bool  isNoteHeld()          const noexcept { return noteHeld.load(); }
    float getCurrentFrequency() const noexcept { return currentFreq.load(); }
    int   getCurrentMidiNote()  const noexcept { return currentNote.load(); }

private:
    // Note state — written on audio thread, read on message thread.
    std::atomic<int>   currentNote     { -1 };
    std::atomic<int>   currentVelocity { 0 };
    std::atomic<float> currentFreq     { 0.0f };
    std::atomic<bool>  noteHeld        { false };
    std::atomic<float> pitchBendST     { 0.0f }; // pitch bend in semitones

    // Current display color (packed as three floats).
    std::atomic<float> atomicH { ColorEngine::HUE_MIN };
    std::atomic<float> atomicL { 0.0f };
    std::atomic<float> atomicC { 0.0f };

    static constexpr float PITCH_BEND_RANGE_ST = 2.0f; // ±2 semitones

    void updateColor (float freq, int velocity) noexcept;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChromesthesiaProcessor)
};
