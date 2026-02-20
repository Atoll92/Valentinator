#include "UnderwaterChain.h"
#include "ParameterLayout.h"

void UnderwaterChain::prepare (const juce::dsp::ProcessSpec& spec)
{
    pitchWobble.prepare (spec);

    ladderFilter.prepare (spec);
    ladderFilter.setMode (juce::dsp::LadderFilterMode::LPF24);

    chorus.prepare (spec);

    reverb.prepare (spec);

    dryWetMixer.prepare (spec);
    dryWetMixer.setWetMixProportion (0.5f);
}

void UnderwaterChain::process (juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block (buffer);

    // Capture dry signal before processing
    dryWetMixer.pushDrySamples (block);

    // Process through the underwater chain
    juce::dsp::ProcessContextReplacing<float> context (block);

    pitchWobble.process (context);
    ladderFilter.process (context);
    chorus.process (context);
    reverb.process (context);

    // Blend dry/wet
    dryWetMixer.mixWetSamples (block);
}

void UnderwaterChain::reset()
{
    pitchWobble.reset();
    ladderFilter.reset();
    chorus.reset();
    reverb.reset();
    dryWetMixer.reset();
}

void UnderwaterChain::updateParameters (juce::AudioProcessorValueTreeState& apvts)
{
    using namespace ValentinatorParams::ID;

    // Master mix
    dryWetMixer.setWetMixProportion (apvts.getRawParameterValue (depth)->load());

    // Low-pass filter
    ladderFilter.setCutoffFrequencyHz (apvts.getRawParameterValue (tide)->load());
    ladderFilter.setResonance (apvts.getRawParameterValue (current)->load());

    // Chorus
    chorus.setRate (apvts.getRawParameterValue (drift)->load());
    chorus.setDepth (apvts.getRawParameterValue (ripple)->load());
    chorus.setCentreDelay (apvts.getRawParameterValue (undertow)->load());
    chorus.setFeedback (0.3f);
    chorus.setMix (1.0f);

    // Reverb
    juce::Reverb::Parameters reverbParams;
    reverbParams.roomSize   = apvts.getRawParameterValue (abyss)->load();
    reverbParams.damping    = apvts.getRawParameterValue (murk)->load();
    reverbParams.width      = apvts.getRawParameterValue (expanse)->load();
    reverbParams.wetLevel   = apvts.getRawParameterValue (submersion)->load();
    reverbParams.dryLevel   = 1.0f - reverbParams.wetLevel;
    reverbParams.freezeMode = 0.0f;
    reverb.setParameters (reverbParams);

    // Pitch wobble
    pitchWobble.setDepth (apvts.getRawParameterValue (wobble)->load());
    pitchWobble.setRate (apvts.getRawParameterValue (sway)->load());
}
