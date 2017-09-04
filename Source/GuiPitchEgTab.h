#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class GuiPitchEgTab : public Component, public SliderListener
{
public:
    GuiPitchEgTab (SynthSound* pSynthSound);
    ~GuiPitchEgTab();

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

	void notify();

private:
	SynthSound* pSound;

    ScopedPointer<Label> attackLabel1;
    ScopedPointer<Slider> attackSlider1;
    //ScopedPointer<Label> decayLabel1;
    //ScopedPointer<Slider> decaySlider1;
    ScopedPointer<Label> sustainLabel1;
    ScopedPointer<Slider> sustainSlider1;
    ScopedPointer<Label> releaseLabel1;
    ScopedPointer<Slider> releaseSlider1;

	ScopedPointer<Label> attackLabel2;
	ScopedPointer<Slider> attackSlider2;
	//ScopedPointer<Label> decayLabel2;
	//ScopedPointer<Slider> decaySlider2;
	ScopedPointer<Label> sustainLabel2;
	ScopedPointer<Slider> sustainSlider2;
	ScopedPointer<Label> releaseLabel2;
	ScopedPointer<Slider> releaseSlider2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiPitchEgTab)
};
