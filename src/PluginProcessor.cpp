#include "PluginProcessor.h"
#include "PluginEditor.h"

ChromesthesiaProcessor::ChromesthesiaProcessor()
    : AudioProcessor (BusesProperties()
          .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
          .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
}

void ChromesthesiaProcessor::prepareToPlay (double, int) {}
void ChromesthesiaProcessor::releaseResources() {}

void ChromesthesiaProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                           juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (buffer); // audio passes through unchanged

    // Inspect MIDI for color updates — do NOT clear the buffer so all
    // messages pass through unchanged to the instrument downstream.
    for (const auto metadata : midiMessages)
    {
        const auto msg = metadata.getMessage();

        if (msg.isNoteOn())
        {
            const int   note = msg.getNoteNumber();
            const int   vel  = msg.getVelocity();
            const float freq = ColorEngine::midiToFrequency (note, pitchBendST.load());

            currentNote    .store (note);
            currentVelocity.store (vel);
            currentFreq    .store (freq);
            noteHeld       .store (true);
            updateColor (freq, vel);
        }
        else if (msg.isNoteOff())
        {
            if (msg.getNoteNumber() == currentNote.load())
            {
                noteHeld.store (false);
                // Keep color values so the editor can fade from them.
            }
        }
        else if (msg.isPitchWheel())
        {
            // Pitch wheel: 0–16383, centre 8192 → [-1, +1] × range
            const float normalised = (msg.getPitchWheelValue() - 8192.0f) / 8192.0f;
            const float bendST     = normalised * PITCH_BEND_RANGE_ST;
            pitchBendST.store (bendST);

            if (noteHeld.load())
            {
                const float freq = ColorEngine::midiToFrequency (currentNote.load(), bendST);
                currentFreq.store (freq);
                updateColor (freq, currentVelocity.load());
            }
        }
    }
}

void ChromesthesiaProcessor::updateColor (float freq, int velocity) noexcept
{
    const OKLCH c = ColorEngine::frequencyToOKLCH (freq, velocity);
    atomicH.store (c.H);
    atomicL.store (c.L);
    atomicC.store (c.C);
}

juce::AudioProcessorEditor* ChromesthesiaProcessor::createEditor()
{
    return new ChromesthesiaEditor (*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChromesthesiaProcessor();
}
