#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class MarineLookAndFeel : public juce::LookAndFeel_V4
{
public:
    MarineLookAndFeel();

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, juce::Slider& slider) override;

    void drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const juce::Slider::SliderStyle style, juce::Slider& slider) override;

    void drawGroupComponentOutline (juce::Graphics& g, int width, int height,
                                    const juce::String& text, const juce::Justification& position,
                                    juce::GroupComponent& group) override;

    // Color palette
    static inline const juce::Colour bgTop       { 0xff0a1628 };
    static inline const juce::Colour bgBottom     { 0xff0d2b3e };
    static inline const juce::Colour accent       { 0xff00e5ff };
    static inline const juce::Colour accentDim    { 0xff007a8a };
    static inline const juce::Colour seafoam      { 0xff69f0ae };
    static inline const juce::Colour knobTrack    { 0xff1a3a50 };
    static inline const juce::Colour textColour   { 0xffb0e0ff };
    static inline const juce::Colour labelColour  { 0xffc0ecff };
};
