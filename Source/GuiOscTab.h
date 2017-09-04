#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class GuiOscTab : public Component,
                  public ComboBoxListener,
                  public SliderListener
{
public:
    GuiOscTab (SynthSound* pSynthSound);
    ~GuiOscTab();

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

	void notify();

private:
	SynthSound* pSound;

    ScopedPointer<Label> wfLabel1;
    ScopedPointer<ComboBox> waveformCB1;
    ScopedPointer<Label> semiLabel1;
    ScopedPointer<Slider> semiSlider1;
    ScopedPointer<Label> detuneLabel1;
    ScopedPointer<Slider> detuneSlider1;

	ScopedPointer<Label> wfLabel2;
	ScopedPointer<ComboBox> waveformCB2;
	ScopedPointer<Label> semiLabel2;
	ScopedPointer<Slider> semiSlider2;
	ScopedPointer<Label> detuneLabel2;
	ScopedPointer<Slider> detuneSlider2;

	ScopedPointer<Label> oscBlendLabel;
	ScopedPointer<Slider> oscBlendSlider;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiOscTab)
};
