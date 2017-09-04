#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class GuiLFOTab : public Component,
                  public ComboBoxListener,
                  public SliderListener
{
public:
    GuiLFOTab (SynthSound* pSynthSound);
    ~GuiLFOTab();

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

	void notify();

private:
	SynthSound* pSound;

    ScopedPointer<Label> wfLabel1;
    ScopedPointer<ComboBox> waveformCB1;
    ScopedPointer<Label> freqLabel1;
    ScopedPointer<Slider> freqSlider1;
    ScopedPointer<Label> amountLabel1;
    ScopedPointer<Slider> amountSlider1;

	ScopedPointer<Label> wfLabel2;
	ScopedPointer<ComboBox> waveformCB2;
	ScopedPointer<Label> freqLabel2;
	ScopedPointer<Slider> freqSlider2;
	ScopedPointer<Label> amountLabel2;
	ScopedPointer<Slider> amountSlider2;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiLFOTab)
};
