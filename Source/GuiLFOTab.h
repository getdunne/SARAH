#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class GuiLFOTab : public Component,
                  public ComboBoxListener,
                  public SliderListener
{
public:
    GuiLFOTab (SynthSound* pSynthSound);

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

    void notify();

private:
    SynthSound* pSound;

    Label wfLabel1, freqLabel1, amountLabel1;
    ComboBox waveformCB1;
    Slider freqSlider1, amountSlider1;
    Label wfLabel2, freqLabel2, amountLabel2;
    ComboBox waveformCB2;
    Slider freqSlider2, amountSlider2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiLFOTab)
};
