#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class GuiAmpEgTab : public Component, public SliderListener
{
public:
    GuiAmpEgTab (SynthSound* pSynthSound);
    ~GuiAmpEgTab();

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

	void notify();

private:
	SynthSound* pSound;

    ScopedPointer<Label> attackLabel;
    ScopedPointer<Slider> attackSlider;
    ScopedPointer<Label> decayLabel;
    ScopedPointer<Slider> decaySlider;
    ScopedPointer<Label> sustainLabel;
    ScopedPointer<Slider> sustainSlider;
    ScopedPointer<Label> releaseLabel;
    ScopedPointer<Slider> releaseSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiAmpEgTab)
};
