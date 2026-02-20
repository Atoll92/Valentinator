#pragma once
#include <juce_dsp/juce_dsp.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "PitchWobble.h"

class UnderwaterChain
{
public:
    UnderwaterChain() = default;

    void prepare (const juce::dsp::ProcessSpec& spec);
    void process (juce::AudioBuffer<float>& buffer);
    void reset();

    void updateParameters (juce::AudioProcessorValueTreeState& apvts);

private:
    PitchWobble                      pitchWobble;
    juce::dsp::LadderFilter<float>   ladderFilter;
    juce::dsp::Chorus<float>         chorus;
    juce::dsp::Reverb                reverb;
    juce::dsp::DryWetMixer<float>    dryWetMixer;
};
