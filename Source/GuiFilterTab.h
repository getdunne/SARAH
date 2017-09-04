#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class GuiFilterTab : public Component, public SliderListener
{
public:
    GuiFilterTab (SynthSound* pSynthSound, int filterIndex);

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

	void notify();

private:
	SynthSound* pSound;
	int whichFilter;

    Label cutoffLabel, slopeLabel, envAmountLabel,
        attackLabel, decayLabel, sustainLabel, releaseLabel;
    Slider cutoffSlider, slopeSlider, envAmountSlider,
        attackSlider, decaySlider, sustainSlider, releaseSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiFilterTab)
};
