#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class GuiPitchEgTab : public Component, public SliderListener
{
public:
    GuiPitchEgTab (SynthSound* pSynthSound);

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

    void notify();

private:
    SynthSound* pSound;

    Label attackLabel1, sustainLabel1, releaseLabel1;
    Slider attackSlider1, sustainSlider1, releaseSlider1;
    Label attackLabel2, sustainLabel2, releaseLabel2;
    Slider attackSlider2, sustainSlider2, releaseSlider2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiPitchEgTab)
};
