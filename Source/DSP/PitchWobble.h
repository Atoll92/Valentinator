#pragma once
#include <juce_dsp/juce_dsp.h>

class PitchWobble
{
public:
    PitchWobble() = default;

    void prepare (const juce::dsp::ProcessSpec& spec);
    void process (const juce::dsp::ProcessContextReplacing<float>& context);
    void reset();

    void setDepth (float newDepth);
    void setRate (float newRateHz);

private:
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Lagrange3rd> delayLine { 4410 };

    float lfoPhase = 0.0f;
    float lfoIncrement = 0.0f;
    float depth = 0.0f;
    float sampleRate = 44100.0f;

    static constexpr float maxDelayModulationMs = 3.0f;
    static constexpr float baseDelayMs = 5.0f;
};
