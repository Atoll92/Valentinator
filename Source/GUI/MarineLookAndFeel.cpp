#include "MarineLookAndFeel.h"

MarineLookAndFeel::MarineLookAndFeel()
{
    setColour (juce::Slider::textBoxTextColourId,    textColour);
    setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    setColour (juce::Label::textColourId,            labelColour);
    setColour (juce::GroupComponent::outlineColourId, accent.withAlpha (0.3f));
    setColour (juce::GroupComponent::textColourId,   accent);
    setColour (juce::ResizableWindow::backgroundColourId, bgTop);
}

void MarineLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                                           float sliderPos, float rotaryStartAngle,
                                           float rotaryEndAngle, juce::Slider&)
{
    auto bounds = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (4.0f);
    auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto centreX = bounds.getCentreX();
    auto centreY = bounds.getCentreY();
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto diameter = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // Knob body — dark circle with subtle gradient
    juce::ColourGradient bodyGrad (knobTrack.brighter (0.15f), centreX, ry,
                                   knobTrack.darker (0.2f), centreX, ry + diameter, false);
    g.setGradientFill (bodyGrad);
    g.fillEllipse (rx, ry, diameter, diameter);

    // Track arc (background)
    juce::Path trackArc;
    auto arcRadius = radius - 4.0f;
    trackArc.addCentredArc (centreX, centreY, arcRadius, arcRadius, 0.0f,
                            rotaryStartAngle, rotaryEndAngle, true);
    g.setColour (knobTrack.darker (0.3f));
    g.strokePath (trackArc, juce::PathStrokeType (3.0f, juce::PathStrokeType::curved,
                                                   juce::PathStrokeType::rounded));

    // Value arc (filled portion)
    juce::Path valueArc;
    valueArc.addCentredArc (centreX, centreY, arcRadius, arcRadius, 0.0f,
                            rotaryStartAngle, angle, true);
    juce::ColourGradient arcGrad (accent, centreX - radius, centreY,
                                  seafoam, centreX + radius, centreY, false);
    g.setGradientFill (arcGrad);
    g.strokePath (valueArc, juce::PathStrokeType (3.0f, juce::PathStrokeType::curved,
                                                   juce::PathStrokeType::rounded));

    // Pointer dot
    auto pointerLength = radius - 8.0f;
    auto pointerX = centreX + pointerLength * std::cos (angle - juce::MathConstants<float>::halfPi);
    auto pointerY = centreY + pointerLength * std::sin (angle - juce::MathConstants<float>::halfPi);
    g.setColour (accent);
    g.fillEllipse (pointerX - 3.0f, pointerY - 3.0f, 6.0f, 6.0f);

    // Glow around pointer
    g.setColour (accent.withAlpha (0.3f));
    g.fillEllipse (pointerX - 5.0f, pointerY - 5.0f, 10.0f, 10.0f);
}

void MarineLookAndFeel::drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                                           float sliderPos, float /*minSliderPos*/, float /*maxSliderPos*/,
                                           const juce::Slider::SliderStyle style, juce::Slider&)
{
    if (style != juce::Slider::LinearHorizontal)
    {
        LookAndFeel_V4::drawLinearSlider (g, x, y, width, height, sliderPos, 0, 0, style, *static_cast<juce::Slider*>(nullptr));
        return;
    }

    auto trackY = static_cast<float> (y) + static_cast<float> (height) * 0.5f;
    auto trackHeight = 6.0f;
    auto trackRect = juce::Rectangle<float> (static_cast<float> (x), trackY - trackHeight * 0.5f,
                                              static_cast<float> (width), trackHeight);

    // Track background
    g.setColour (knobTrack);
    g.fillRoundedRectangle (trackRect, trackHeight * 0.5f);

    // Filled portion
    auto fillWidth = sliderPos - static_cast<float> (x);
    auto fillRect = trackRect.withWidth (fillWidth);
    juce::ColourGradient fillGrad (accent, trackRect.getX(), 0,
                                   seafoam, trackRect.getRight(), 0, false);
    g.setGradientFill (fillGrad);
    g.fillRoundedRectangle (fillRect, trackHeight * 0.5f);

    // Thumb — glowing circle
    auto thumbRadius = 8.0f;
    g.setColour (accent.withAlpha (0.3f));
    g.fillEllipse (sliderPos - thumbRadius - 2.0f, trackY - thumbRadius - 2.0f,
                   (thumbRadius + 2.0f) * 2.0f, (thumbRadius + 2.0f) * 2.0f);
    g.setColour (accent);
    g.fillEllipse (sliderPos - thumbRadius, trackY - thumbRadius,
                   thumbRadius * 2.0f, thumbRadius * 2.0f);
    g.setColour (juce::Colours::white.withAlpha (0.6f));
    g.fillEllipse (sliderPos - 3.0f, trackY - 3.0f, 6.0f, 6.0f);
}

void MarineLookAndFeel::drawGroupComponentOutline (juce::Graphics& g, int width, int height,
                                                    const juce::String& text,
                                                    const juce::Justification&,
                                                    juce::GroupComponent&)
{
    auto cornerSize = 6.0f;
    auto textH = 14.0f;
    auto indent = 3.0f;

    auto bounds = juce::Rectangle<float> (indent, textH, static_cast<float> (width) - indent * 2.0f,
                                           static_cast<float> (height) - textH - indent);

    // Semi-transparent background
    g.setColour (knobTrack.withAlpha (0.2f));
    g.fillRoundedRectangle (bounds, cornerSize);

    // Border
    g.setColour (accent.withAlpha (0.25f));
    g.drawRoundedRectangle (bounds, cornerSize, 1.0f);

    // Group label
    g.setColour (accent.withAlpha (0.8f));
    g.setFont (juce::Font (12.0f));
    g.drawText (text, static_cast<int> (indent + 8.0f), 0, width, static_cast<int> (textH + 4.0f),
                juce::Justification::centredLeft);
}
