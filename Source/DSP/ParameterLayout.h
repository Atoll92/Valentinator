#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

namespace ValentinatorParams
{
    namespace ID
    {
        inline constexpr const char* depth      = "depth";
        inline constexpr const char* tide       = "tide";
        inline constexpr const char* current    = "current";
        inline constexpr const char* drift      = "drift";
        inline constexpr const char* ripple     = "ripple";
        inline constexpr const char* undertow   = "undertow";
        inline constexpr const char* abyss      = "abyss";
        inline constexpr const char* murk       = "murk";
        inline constexpr const char* expanse    = "expanse";
        inline constexpr const char* submersion = "submersion";
        inline constexpr const char* wobble     = "wobble";
        inline constexpr const char* sway       = "sway";
    }

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
}
