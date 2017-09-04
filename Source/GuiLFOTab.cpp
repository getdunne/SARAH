#include "GuiLFOTab.h"

GuiLFOTab::GuiLFOTab (SynthSound* pSynthSound)
    : pSound(pSynthSound)
    , wfLabel1("waveform label1", TRANS("Pitch LFO"))
    , freqLabel1("freq label1", TRANS("Frequency (Hz)"))
    , amountLabel1("amount label1", TRANS("Amount (cents)"))
    , wfLabel2("waveform label2", TRANS("Filter LFO"))
    , freqLabel2("freq label2", TRANS("Frequency (Hz)"))
    , amountLabel2("amount label2", TRANS("Amount (cents)"))
{
    auto initLabel = [this](Label& label)
    {
        addAndMakeVisible(label);
        label.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
        label.setJustificationType(Justification::centredRight);
        label.setEditable(false, false, false);
        label.setColour(TextEditor::textColourId, Colours::black);
        label.setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    };

    initLabel(wfLabel1); initLabel(wfLabel2);
    initLabel(freqLabel1); initLabel(freqLabel2);
    initLabel(amountLabel1); initLabel(amountLabel2);

    auto initCombo = [this](ComboBox& combo)
    {
        addAndMakeVisible(combo);
        combo.setEditableText(false);
        combo.setJustificationType(Justification::centredLeft);
        combo.setTextWhenNothingSelected("");
        combo.setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
        combo.addListener(this);
    };

    initCombo(waveformCB1);
    waveformCB1.addItem (TRANS("Sine"), 1);
    waveformCB1.addItem (TRANS("Triangle"), 2);
    waveformCB1.addItem (TRANS("Square"), 3);
    waveformCB1.addItem (TRANS("Sawtooth"), 4);
    initCombo(waveformCB2);
    waveformCB2.addItem(TRANS("Sine"), 1);
    waveformCB2.addItem(TRANS("Triangle"), 2);
    waveformCB2.addItem(TRANS("Square"), 3);
    waveformCB2.addItem(TRANS("Sawtooth"), 4);

    auto initSlider = [this](Slider& slider)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::LinearHorizontal);
        slider.setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
        slider.addListener(this);
    };

    initSlider(freqSlider1); freqSlider1.setRange(0.1, 10.0, 0);
    initSlider(amountSlider1); amountSlider1.setRange(0, 100, 0);
    initSlider(freqSlider2); freqSlider2.setRange(0.1, 10.0, 0);
    initSlider(amountSlider2); amountSlider2.setRange(0, 100, 0);

    notify();
}

//==============================================================================
void GuiLFOTab::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiLFOTab::resized()
{
    const int labelLeft = 16;
    const int controlLeft = 144;
    const int labelWidth = 120;
    const int cboxWidth = 150;
    const int sliderWidth = 344;
    const int controlHeight = 24;
    const int gapHeight = 8;

    int top = 20;
    wfLabel1.setBounds (labelLeft, top, labelWidth, controlHeight);
    waveformCB1.setBounds (controlLeft, top, cboxWidth, controlHeight);
    top += controlHeight + gapHeight;
    freqLabel1.setBounds (labelLeft, top, labelWidth, controlHeight);
    freqSlider1.setBounds (controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    amountLabel1.setBounds (labelLeft, top, labelWidth, controlHeight);
    amountSlider1.setBounds (controlLeft, top, sliderWidth, controlHeight);

    top += controlHeight + 5 * gapHeight;
    wfLabel2.setBounds(labelLeft, top, labelWidth, controlHeight);
    waveformCB2.setBounds(controlLeft, top, cboxWidth, controlHeight);
    top += controlHeight + gapHeight;
    freqLabel2.setBounds(labelLeft, top, labelWidth, controlHeight);
    freqSlider2.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    amountLabel2.setBounds(labelLeft, top, labelWidth, controlHeight);
    amountSlider2.setBounds(controlLeft, top, sliderWidth, controlHeight);
}

void GuiLFOTab::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    SynthOscillatorBase::WaveformEnum wf = (SynthOscillatorBase::WaveformEnum)
        (SynthOscillatorBase::kSine + comboBoxThatHasChanged->getSelectedItemIndex());
    SynthParameters* pParams = pSound->pParams;
    if (comboBoxThatHasChanged == &waveformCB1)
    {
        pParams->pitchLFO.waveform = wf;
    }
    else if (comboBoxThatHasChanged == &waveformCB2)
    {
        pParams->filterLFO.waveform = wf;
    }
    pSound->parameterChanged();
}

void GuiLFOTab::sliderValueChanged (Slider* sliderThatWasMoved)
{
    double value = sliderThatWasMoved->getValue();
    SynthParameters* pParams = pSound->pParams;
    if (sliderThatWasMoved == &freqSlider1)
    {
        pParams->pitchLFO.freqHz = value;
    }
    else if (sliderThatWasMoved == &freqSlider2)
    {
        pParams->filterLFO.freqHz = value;
    }
    else if (sliderThatWasMoved == &amountSlider1)
    {
        pParams->pitchLFO.amount = value;    // cents
    }
    else if (sliderThatWasMoved == &amountSlider2)
    {
        pParams->filterLFO.amount = 0.01 * value;    // percent -> fraction
    }
    pSound->parameterChanged();
}

void GuiLFOTab::notify()
{
    SynthParameters* pParams = pSound->pParams;

    waveformCB1.setSelectedItemIndex(int(pParams->pitchLFO.waveform - SynthOscillatorBase::kSine));
    freqSlider1.setValue(pParams->pitchLFO.freqHz);
    amountSlider1.setValue(pParams->pitchLFO.amount);

    waveformCB2.setSelectedItemIndex(int(pParams->filterLFO.waveform - SynthOscillatorBase::kSine));
    freqSlider2.setValue(pParams->filterLFO.freqHz);
    amountSlider2.setValue(100.0 * pParams->filterLFO.amount);    // fraction -> percent
}
