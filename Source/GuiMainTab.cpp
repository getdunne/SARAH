#include "GuiMainTab.h"

//==============================================================================
GuiMainTab::GuiMainTab(SynthSound* pSynthSound)
    : pSound(pSynthSound)
    , masterLevelLabel("master level", TRANS("Master Volume"))
    , pbUpLabel("PB up", TRANS("P.Bend up (semi)"))
    , pbDownLabel("PB down", TRANS("P.Bend down (semi)"))
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

    initLabel(masterLevelLabel);
    initLabel(pbUpLabel);
    initLabel(pbDownLabel);

    auto initSlider = [this](Slider& slider)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::LinearHorizontal);
        slider.setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
        slider.addListener(this);
    };

    initSlider(masterLevelSlider); masterLevelSlider.setRange(0, 10, 0);
    initSlider(pbUpSlider); pbUpSlider.setRange(0, 12, 1);
    initSlider(pbDownSlider); pbDownSlider.setRange(0, 12, 1);

    notify();
}

//==============================================================================
void GuiMainTab::paint(Graphics& g)
{
    g.fillAll(Colour(0xff323e44));
}

void GuiMainTab::resized()
{
    const int labelLeft = 16;
    const int controlLeft = 144;
    const int labelWidth = 120;
    const int sliderWidth = 420;
    const int controlHeight = 24;
    const int gapHeight = 8;

    int top = 20;
    masterLevelLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    masterLevelSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + 5 * gapHeight;
    pbUpLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    pbUpSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    pbDownLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    pbDownSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
}

void GuiMainTab::sliderValueChanged(Slider* sliderThatWasMoved)
{
    double value = sliderThatWasMoved->getValue();
    SynthParameters::MainParams* pParams = &pSound->pParams->main;
    if (sliderThatWasMoved == &masterLevelSlider)
    {
        pParams->masterLevel = 0.1 * value;
    }
    else if (sliderThatWasMoved == &pbUpSlider)
    {
        pParams->pitchBendUpSemitones = int(value);
    }
    else if (sliderThatWasMoved == &pbDownSlider)
    {
        pParams->pitchBendDownSemitones = int(value);
    }
    pSound->parameterChanged();
}

void GuiMainTab::notify()
{
    SynthParameters::MainParams* pParams = &pSound->pParams->main;
    masterLevelSlider.setValue(10.0 * pParams->masterLevel);
    pbUpSlider.setValue(pParams->pitchBendUpSemitones);
    pbDownSlider.setValue(pParams->pitchBendDownSemitones);
}
