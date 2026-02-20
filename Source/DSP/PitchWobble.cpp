#include "PitchWobble.h"

void PitchWobble::prepare (const juce::dsp::ProcessSpec& spec)
{
    sampleRate = static_cast<float> (spec.sampleRate);
    delayLine.prepare (spec);
    delayLine.setMaximumDelayInSamples (static_cast<int> ((baseDelayMs + maxDelayModulationMs) * sampleRate / 1000.0f) + 1);
    reset();
}

void PitchWobble::process (const juce::dsp::ProcessContextReplacing<float>& context)
{
    auto& block = context.getOutputBlock();
    auto numChannels = block.getNumChannels();
    auto numSamples  = block.getNumSamples();

    float baseDelaySamples = baseDelayMs * sampleRate / 1000.0f;
    float maxModSamples    = maxDelayModulationMs * sampleRate / 1000.0f;

    for (size_t sample = 0; sample < numSamples; ++sample)
    {
        float mod = std::sin (lfoPhase) * depth * maxModSamples;
        float totalDelay = baseDelaySamples + mod;

        lfoPhase += lfoIncrement;
        if (lfoPhase >= juce::MathConstants<float>::twoPi)
            lfoPhase -= juce::MathConstants<float>::twoPi;

        for (size_t ch = 0; ch < numChannels; ++ch)
        {
            float inputSample = block.getSample (static_cast<int> (ch), static_cast<int> (sample));
            delayLine.pushSample (static_cast<int> (ch), inputSample);
            float outputSample = delayLine.popSample (static_cast<int> (ch), totalDelay);
            block.setSample (static_cast<int> (ch), static_cast<int> (sample), outputSample);
        }
    }
}

void PitchWobble::reset()
{
    delayLine.reset();
    lfoPhase = 0.0f;
}

void PitchWobble::setDepth (float newDepth)
{
    depth = juce::jlimit (0.0f, 1.0f, newDepth);
}

void PitchWobble::setRate (float newRateHz)
{
    lfoIncrement = juce::MathConstants<float>::twoPi * newRateHz / sampleRate;
}
