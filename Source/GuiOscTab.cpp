#include "GuiOscTab.h"

GuiOscTab::GuiOscTab(SynthSound* pSynthSound)
    : pSound(pSynthSound)
    , wfLabel1("waveform label1", TRANS("Osc1 Waveform"))
    , semiLabel1("semitone offset label1", TRANS("Pitch (semitones)"))
    , detuneLabel1("detune label1", TRANS("Detune (cents)"))
    , wfLabel2("waveform label2", TRANS("Osc2 Waveform"))
    , semiLabel2("semitone offset label1", TRANS("Pitch (semitones)"))
    , detuneLabel2("detune label1", TRANS("Detune (cents)"))
    , oscBlendLabel("osc blend label", TRANS("Blend"))
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

    initLabel(wfLabel1);
    initLabel(semiLabel1);
    initLabel(detuneLabel1);
    initLabel(wfLabel2);
    initLabel(semiLabel2);
    initLabel(detuneLabel2);
    initLabel(oscBlendLabel);
    oscBlendLabel.setJustificationType(Justification::centred);

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
    waveformCB1.addItem(TRANS("Sine"), 1);
    waveformCB1.addItem(TRANS("Triangle"), 2);
    waveformCB1.addItem(TRANS("Square"), 3);
    waveformCB1.addItem(TRANS("Sawtooth"), 4);
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

    initSlider(semiSlider1); semiSlider1.setRange(-24, 24, 1);
    initSlider(detuneSlider1); detuneSlider1.setRange(-50, 50, 0);
    initSlider(semiSlider2); semiSlider2.setRange(-24, 24, 1);
    initSlider(detuneSlider2); detuneSlider2.setRange(-50, 50, 0);

    addAndMakeVisible(oscBlendSlider);
    oscBlendSlider.setRange(0, 100, 0);
    oscBlendSlider.setSliderStyle(Slider::LinearVertical);
    oscBlendSlider.setTextBoxStyle(Slider::TextBoxAbove, false, 80, 20);
    oscBlendSlider.addListener(this);

    notify();
}

//==============================================================================
void GuiOscTab::paint(Graphics& g)
{
    g.fillAll(Colour(0xff323e44));
}

void GuiOscTab::resized()
{
    const int labelLeft = 16;
    const int controlLeft = 144;
    const int labelWidth = 120;
    const int cboxWidth = 150;
    const int sliderWidth = 344;
    const int controlHeight = 24;
    const int gapHeight = 8;
    const int blendSliderLeft = 510;
    const int blendSliderWidth = 60;
    const int blendSliderHeight = 240;

    int top = 20;
    wfLabel1.setBounds(labelLeft, top, labelWidth, controlHeight);
    waveformCB1.setBounds(controlLeft, top, cboxWidth, controlHeight);
    top += controlHeight + gapHeight;
    semiLabel1.setBounds(labelLeft, top, labelWidth, controlHeight);
    semiSlider1.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    detuneLabel1.setBounds(labelLeft, top, labelWidth, controlHeight);
    detuneSlider1.setBounds(controlLeft, top, sliderWidth, controlHeight);

    top += controlHeight + 5 * gapHeight;
    wfLabel2.setBounds(labelLeft, top, labelWidth, controlHeight);
    waveformCB2.setBounds(controlLeft, top, cboxWidth, controlHeight);
    top += controlHeight + gapHeight;
    semiLabel2.setBounds(labelLeft, top, labelWidth, controlHeight);
    semiSlider2.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    detuneLabel2.setBounds(labelLeft, top, labelWidth, controlHeight);
    detuneSlider2.setBounds(controlLeft, top, sliderWidth, controlHeight);

    top = 20;
    oscBlendSlider.setBounds(blendSliderLeft, top, blendSliderWidth, blendSliderHeight);
    top += blendSliderHeight + gapHeight;
    oscBlendLabel.setBounds(blendSliderLeft + blendSliderWidth / 2 - labelWidth / 2, top, labelWidth, controlHeight);
}

void GuiOscTab::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    SynthOscillatorBase::WaveformEnum wf = (SynthOscillatorBase::WaveformEnum)
        (SynthOscillatorBase::kSine + comboBoxThatHasChanged->getSelectedItemIndex());
    SynthParameters* pParams = pSound->pParams;
    if (comboBoxThatHasChanged == &waveformCB1)
    {
        pParams->osc1.waveform = wf;
    }
    else if (comboBoxThatHasChanged == &waveformCB2)
    {
        pParams->osc2.waveform = wf;
    }
    pSound->parameterChanged();
}

void GuiOscTab::sliderValueChanged(Slider* sliderThatWasMoved)
{
    double value = sliderThatWasMoved->getValue();
    SynthParameters* pParams = pSound->pParams;
    if (sliderThatWasMoved == &semiSlider1)
    {
        pParams->osc1.pitchOffsetSemitones = int(value);
    }
    else if (sliderThatWasMoved == &semiSlider2)
    {
        pParams->osc2.pitchOffsetSemitones = int(value);
    }
    else if (sliderThatWasMoved == &detuneSlider1)
    {
        pParams->osc1.detuneOffsetCents = value;
    }
    else if (sliderThatWasMoved == &detuneSlider2)
    {
        pParams->osc2.detuneOffsetCents = value;
    }
    else if (sliderThatWasMoved == &oscBlendSlider)
    {
        pParams->main.oscBlend = 0.01 * value;
    }
    pSound->parameterChanged();
}

void GuiOscTab::notify()
{
    SynthParameters* pParams = pSound->pParams;

    waveformCB1.setSelectedItemIndex(int(pParams->pitchLFO.waveform - SynthOscillatorBase::kSine));
    semiSlider1.setValue(pParams->osc1.pitchOffsetSemitones);
    detuneSlider1.setValue(pParams->osc1.detuneOffsetCents);

    waveformCB2.setSelectedItemIndex(int(pParams->filterLFO.waveform - SynthOscillatorBase::kSine));
    semiSlider2.setValue(pParams->osc2.pitchOffsetSemitones);
    detuneSlider2.setValue(pParams->osc2.detuneOffsetCents);

    oscBlendSlider.setValue(100.0 * pParams->main.oscBlend);
}
