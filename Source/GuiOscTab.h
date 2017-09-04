#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class GuiOscTab : public Component,
                  public ComboBoxListener,
                  public SliderListener
{
public:
    GuiOscTab (SynthSound* pSynthSound);

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

    void notify();

private:
    SynthSound* pSound;

    Label wfLabel1, semiLabel1, detuneLabel1;
    ComboBox waveformCB1;
    Slider semiSlider1, detuneSlider1;
    Label wfLabel2, semiLabel2, detuneLabel2;
    ComboBox waveformCB2;
    Slider semiSlider2, detuneSlider2;
    Label oscBlendLabel;
    Slider oscBlendSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiOscTab)
};
