#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class GuiMainTab : public Component, public SliderListener
{
public:
    GuiMainTab (SynthSound* pSynthSound);
    ~GuiMainTab();

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

	void notify();

private:
	SynthSound* pSound;

    ScopedPointer<Label> masterLevelLabel;
    ScopedPointer<Slider> masterLevelSlider;
	ScopedPointer<Label> pbUpLabel;
	ScopedPointer<Slider> pbUpSlider;
	ScopedPointer<Label> pbDownLabel;
	ScopedPointer<Slider> pbDownSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiMainTab)
};
