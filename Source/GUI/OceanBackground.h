#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class OceanBackground : public juce::Component
{
public:
    OceanBackground();
    void paint (juce::Graphics& g) override;

private:
    juce::Image backgroundImage;
};
