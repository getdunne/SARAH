#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class GuiMainTab : public Component, public SliderListener
{
public:
    GuiMainTab (SynthSound* pSynthSound);

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

	void notify();

private:
	SynthSound* pSound;

    Label masterLevelLabel, pbUpLabel, pbDownLabel;
    Slider masterLevelSlider, pbUpSlider, pbDownSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiMainTab)
};
