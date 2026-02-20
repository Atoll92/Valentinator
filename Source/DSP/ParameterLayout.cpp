#include "ParameterLayout.h"

namespace ValentinatorParams
{

juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    // Master
    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ID::depth, 1 },
        "Depth",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f),
        0.5f));

    // Filter
    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ID::tide, 1 },
        "Tide",
        juce::NormalisableRange<float> (20.0f, 2000.0f, 1.0f, 0.3f),
        800.0f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ID::current, 1 },
        "Current",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f),
        0.4f));

    // Modulation (Chorus)
    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ID::drift, 1 },
        "Drift",
        juce::NormalisableRange<float> (0.1f, 5.0f, 0.01f),
        1.2f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ID::ripple, 1 },
        "Ripple",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f),
        0.4f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ID::undertow, 1 },
        "Undertow",
        juce::NormalisableRange<float> (1.0f, 30.0f, 0.1f),
        8.0f));

    // Reverb
    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ID::abyss, 1 },
        "Abyss",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f),
        0.6f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ID::murk, 1 },
        "Murk",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f),
        0.7f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ID::expanse, 1 },
        "Expanse",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f),
        0.8f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ID::submersion, 1 },
        "Submersion",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f),
        0.5f));

    // Pitch Wobble
    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ID::wobble, 1 },
        "Wobble",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f),
        0.3f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ID::sway, 1 },
        "Sway",
        juce::NormalisableRange<float> (0.05f, 2.0f, 0.01f),
        0.4f));

    return layout;
}

} // namespace ValentinatorParams
