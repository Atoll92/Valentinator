#include "OceanBackground.h"
#include "MarineLookAndFeel.h"
#include "BinaryData.h"

OceanBackground::OceanBackground()
{
    setInterceptsMouseClicks (false, false);

    // Load the background image from binary data
    backgroundImage = juce::ImageCache::getFromMemory (BinaryData::background_png,
                                                        BinaryData::background_pngSize);
}

void OceanBackground::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    if (backgroundImage.isValid())
    {
        // Draw image scaled to fill the entire background, maintaining aspect ratio
        // Use RectanglePlacement::fillDestination to cover the whole area (like CSS "cover")
        g.drawImage (backgroundImage, bounds,
                     juce::RectanglePlacement::centred | juce::RectanglePlacement::fillDestination);

        // Dark overlay so knobs/labels remain readable
        g.setColour (juce::Colour (0x00, 0x0a, 0x14).withAlpha (0.55f));
        g.fillRect (bounds);

        // Subtle gradient vignette at edges for depth
        juce::ColourGradient vignetteTop (juce::Colour (0xaa000a14), bounds.getCentreX(), 0,
                                           juce::Colours::transparentBlack, bounds.getCentreX(), bounds.getHeight() * 0.15f, false);
        g.setGradientFill (vignetteTop);
        g.fillRect (bounds);

        juce::ColourGradient vignetteBottom (juce::Colours::transparentBlack, bounds.getCentreX(), bounds.getHeight() * 0.85f,
                                              juce::Colour (0xaa000a14), bounds.getCentreX(), bounds.getHeight(), false);
        g.setGradientFill (vignetteBottom);
        g.fillRect (bounds);
    }
    else
    {
        // Fallback: deep ocean gradient if image fails to load
        juce::ColourGradient bgGrad (MarineLookAndFeel::bgTop, 0, 0,
                                      MarineLookAndFeel::bgBottom, 0, bounds.getHeight(), false);
        g.setGradientFill (bgGrad);
        g.fillRect (bounds);
    }
}
