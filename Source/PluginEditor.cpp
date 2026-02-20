#include "PluginEditor.h"
#include "DSP/ParameterLayout.h"

ValentinatorEditor::ValentinatorEditor (ValentinatorProcessor& p)
    : AudioProcessorEditor (p), processor (p)
{
    setLookAndFeel (&marineLnf);

    // Background
    addAndMakeVisible (background);

    // Title
    titleLabel.setText ("V A L E N T I N A T O R", juce::dontSendNotification);
    titleLabel.setFont (juce::Font (20.0f).boldened());
    titleLabel.setColour (juce::Label::textColourId, MarineLookAndFeel::accent);
    titleLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (titleLabel);

    // Groups
    filterGroup.setText ("FILTER");
    modulationGroup.setText ("MODULATION");
    spaceGroup.setText ("SPACE");
    wobbleGroup.setText ("WOBBLE");
    masterGroup.setText ("MASTER");

    addAndMakeVisible (filterGroup);
    addAndMakeVisible (modulationGroup);
    addAndMakeVisible (spaceGroup);
    addAndMakeVisible (wobbleGroup);
    addAndMakeVisible (masterGroup);

    // Filter knobs
    using namespace ValentinatorParams;
    setupKnob (tideKnob,    tideLabel,    "Tide",    ID::tide,    tideAttach);
    setupKnob (currentKnob, currentLabel, "Current", ID::current, currentAttach);

    // Modulation knobs
    setupKnob (driftKnob,    driftLabel,    "Drift",    ID::drift,    driftAttach);
    setupKnob (rippleKnob,   rippleLabel,   "Ripple",   ID::ripple,   rippleAttach);
    setupKnob (undertowKnob, undertowLabel, "Undertow", ID::undertow, undertowAttach);

    // Space knobs
    setupKnob (abyssKnob,      abyssLabel,      "Abyss",      ID::abyss,      abyssAttach);
    setupKnob (murkKnob,       murkLabel,       "Murk",       ID::murk,       murkAttach);
    setupKnob (expanseKnob,    expanseLabel,    "Expanse",    ID::expanse,    expanseAttach);
    setupKnob (submersionKnob, submersionLabel, "Submersion", ID::submersion, submersionAttach);

    // Wobble knobs
    setupKnob (wobbleKnob, wobbleLabel, "Wobble", ID::wobble, wobbleAttach);
    setupKnob (swayKnob,   swayLabel,   "Sway",   ID::sway,   swayAttach);

    // Master depth slider
    setupHorizontalSlider (depthSlider, depthLabel, "Depth", ID::depth, depthAttach);

    setSize (660, 420);
}

ValentinatorEditor::~ValentinatorEditor()
{
    setLookAndFeel (nullptr);
}

void ValentinatorEditor::setupKnob (juce::Slider& knob, juce::Label& label,
                                     const juce::String& text, const juce::String& paramId,
                                     std::unique_ptr<SliderAttachment>& attachment)
{
    knob.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    knob.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 16);
    knob.setTextValueSuffix ("");
    addAndMakeVisible (knob);

    label.setText (text, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    label.setFont (juce::Font (11.0f));
    addAndMakeVisible (label);

    attachment = std::make_unique<SliderAttachment> (processor.apvts, paramId, knob);
}

void ValentinatorEditor::setupHorizontalSlider (juce::Slider& slider, juce::Label& label,
                                                 const juce::String& text, const juce::String& paramId,
                                                 std::unique_ptr<SliderAttachment>& attachment)
{
    slider.setSliderStyle (juce::Slider::LinearHorizontal);
    slider.setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    addAndMakeVisible (slider);

    label.setText (text, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centredLeft);
    label.setFont (juce::Font (12.0f).boldened());
    label.setColour (juce::Label::textColourId, MarineLookAndFeel::accent);
    addAndMakeVisible (label);

    attachment = std::make_unique<SliderAttachment> (processor.apvts, paramId, slider);
}

void ValentinatorEditor::paint (juce::Graphics&)
{
    // Background component handles all painting
}

void ValentinatorEditor::resized()
{
    auto area = getLocalBounds();

    // Background fills everything
    background.setBounds (area);

    // Title bar
    auto titleArea = area.removeFromTop (36);
    titleLabel.setBounds (titleArea);

    // Main content area with padding
    area.reduce (12, 4);

    // Top row: three groups side by side (Filter | Modulation | Space)
    auto topRow = area.removeFromTop (200);
    auto topThird = topRow.getWidth() / 3;

    // Filter group
    auto filterArea = topRow.removeFromLeft (topThird).reduced (4);
    filterGroup.setBounds (filterArea);
    {
        auto inner = filterArea.reduced (10, 20).withTrimmedTop (4);
        auto knobSize = inner.getWidth() / 2;
        auto row = inner;

        auto tideArea = row.removeFromLeft (knobSize);
        tideLabel.setBounds (tideArea.removeFromTop (16));
        tideKnob.setBounds (tideArea.reduced (4));

        auto currentArea = row;
        currentLabel.setBounds (currentArea.removeFromTop (16));
        currentKnob.setBounds (currentArea.reduced (4));
    }

    // Modulation group
    auto modArea = topRow.removeFromLeft (topThird).reduced (4);
    modulationGroup.setBounds (modArea);
    {
        auto inner = modArea.reduced (10, 20).withTrimmedTop (4);
        auto knobSize = inner.getWidth() / 3;

        auto driftArea = inner.removeFromLeft (knobSize);
        driftLabel.setBounds (driftArea.removeFromTop (16));
        driftKnob.setBounds (driftArea.reduced (2));

        auto rippleArea = inner.removeFromLeft (knobSize);
        rippleLabel.setBounds (rippleArea.removeFromTop (16));
        rippleKnob.setBounds (rippleArea.reduced (2));

        auto undertowArea = inner;
        undertowLabel.setBounds (undertowArea.removeFromTop (16));
        undertowKnob.setBounds (undertowArea.reduced (2));
    }

    // Space group
    auto spaceArea = topRow.reduced (4);
    spaceGroup.setBounds (spaceArea);
    {
        auto inner = spaceArea.reduced (10, 20).withTrimmedTop (4);
        auto half = inner.getHeight() / 2;
        auto topHalf = inner.removeFromTop (half);
        auto botHalf = inner;

        auto knobW = topHalf.getWidth() / 2;

        auto abyssArea = topHalf.removeFromLeft (knobW);
        abyssLabel.setBounds (abyssArea.removeFromTop (16));
        abyssKnob.setBounds (abyssArea.reduced (2));

        auto murkArea = topHalf;
        murkLabel.setBounds (murkArea.removeFromTop (16));
        murkKnob.setBounds (murkArea.reduced (2));

        auto expanseArea = botHalf.removeFromLeft (knobW);
        expanseLabel.setBounds (expanseArea.removeFromTop (16));
        expanseKnob.setBounds (expanseArea.reduced (2));

        auto submersionArea = botHalf;
        submersionLabel.setBounds (submersionArea.removeFromTop (16));
        submersionKnob.setBounds (submersionArea.reduced (2));
    }

    // Bottom row: Wobble group + Master group
    area.removeFromTop (8);
    auto bottomRow = area;

    // Wobble group (left ~35%)
    auto wobbleArea = bottomRow.removeFromLeft (static_cast<int> (bottomRow.getWidth() * 0.35f)).reduced (4);
    wobbleGroup.setBounds (wobbleArea);
    {
        auto inner = wobbleArea.reduced (10, 20).withTrimmedTop (4);
        auto knobSize = inner.getWidth() / 2;

        auto wobArea = inner.removeFromLeft (knobSize);
        wobbleLabel.setBounds (wobArea.removeFromTop (16));
        wobbleKnob.setBounds (wobArea.reduced (4));

        auto swArea = inner;
        swayLabel.setBounds (swArea.removeFromTop (16));
        swayKnob.setBounds (swArea.reduced (4));
    }

    // Master group (right ~65%)
    auto masterArea = bottomRow.reduced (4);
    masterGroup.setBounds (masterArea);
    {
        auto inner = masterArea.reduced (14, 24).withTrimmedTop (4);
        depthLabel.setBounds (inner.removeFromLeft (50));
        depthSlider.setBounds (inner.reduced (4));
    }
}
