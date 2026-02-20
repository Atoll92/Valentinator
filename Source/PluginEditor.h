#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"
#include "GUI/MarineLookAndFeel.h"
#include "GUI/OceanBackground.h"

class ValentinatorEditor : public juce::AudioProcessorEditor
{
public:
    explicit ValentinatorEditor (ValentinatorProcessor&);
    ~ValentinatorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ValentinatorProcessor& processor;
    MarineLookAndFeel marineLnf;
    OceanBackground background;

    // Knobs
    juce::Slider tideKnob, currentKnob;
    juce::Slider driftKnob, rippleKnob, undertowKnob;
    juce::Slider abyssKnob, murkKnob, expanseKnob, submersionKnob;
    juce::Slider wobbleKnob, swayKnob;
    juce::Slider depthSlider;

    // Labels
    juce::Label tideLabel, currentLabel;
    juce::Label driftLabel, rippleLabel, undertowLabel;
    juce::Label abyssLabel, murkLabel, expanseLabel, submersionLabel;
    juce::Label wobbleLabel, swayLabel;
    juce::Label depthLabel;

    // Section groups
    juce::GroupComponent filterGroup, modulationGroup, spaceGroup, wobbleGroup, masterGroup;

    // Title label
    juce::Label titleLabel;

    // APVTS attachments (must be declared AFTER sliders)
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> tideAttach, currentAttach;
    std::unique_ptr<SliderAttachment> driftAttach, rippleAttach, undertowAttach;
    std::unique_ptr<SliderAttachment> abyssAttach, murkAttach, expanseAttach, submersionAttach;
    std::unique_ptr<SliderAttachment> wobbleAttach, swayAttach;
    std::unique_ptr<SliderAttachment> depthAttach;

    void setupKnob (juce::Slider& knob, juce::Label& label,
                    const juce::String& text, const juce::String& paramId,
                    std::unique_ptr<SliderAttachment>& attachment);

    void setupHorizontalSlider (juce::Slider& slider, juce::Label& label,
                                const juce::String& text, const juce::String& paramId,
                                std::unique_ptr<SliderAttachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ValentinatorEditor)
};
