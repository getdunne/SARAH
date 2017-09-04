#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class GuiFilterTab : public Component, public SliderListener
{
public:
    GuiFilterTab (SynthSound* pSynthSound, int filterIndex);
    ~GuiFilterTab();

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

	void notify();

private:
	SynthSound* pSound;
	int whichFilter;

	ScopedPointer<Label> cutoffLabel;
	ScopedPointer<Slider> cutoffSlider;
	ScopedPointer<Label> slopeLabel;
	ScopedPointer<Slider> slopeSlider;
	ScopedPointer<Label> envAmountLabel;
	ScopedPointer<Slider> envAmountSlider;

	ScopedPointer<Label> attackLabel;
    ScopedPointer<Slider> attackSlider;
    ScopedPointer<Label> decayLabel;
    ScopedPointer<Slider> decaySlider;
    ScopedPointer<Label> sustainLabel;
    ScopedPointer<Slider> sustainSlider;
    ScopedPointer<Label> releaseLabel;
    ScopedPointer<Slider> releaseSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiFilterTab)
};
