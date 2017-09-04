#include "GuiPitchEgTab.h"

GuiPitchEgTab::GuiPitchEgTab (SynthSound* pSynthSound)
    : pSound(pSynthSound)
    , attackLabel1("attack1", TRANS("Attack Time (sec)"))
    , sustainLabel1("sustain1", TRANS("Sustain (semitones)"))
    , releaseLabel1("release1", TRANS("Release Time (sec)"))
    , attackLabel2("attack2", TRANS("Attack Time (sec)"))
    , sustainLabel2("sustain2", TRANS("Sustain (semitones)"))
    , releaseLabel2("release2", TRANS("Release Time (sec)"))
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

    initLabel(attackLabel1); initLabel(sustainLabel1); initLabel(releaseLabel1);
    initLabel(attackLabel2); initLabel(sustainLabel2); initLabel(releaseLabel2);

    auto initSlider = [this](Slider& slider)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::LinearHorizontal);
        slider.setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
        slider.addListener(this);
    };

    initSlider(attackSlider1); attackSlider1.setRange(0, 10, 0);
    initSlider(sustainSlider1); sustainSlider1.setRange(-12, 12, 0);
    initSlider(releaseSlider1); releaseSlider1.setRange(0, 10, 0);
    initSlider(attackSlider2); attackSlider2.setRange(0, 10, 0);
    initSlider(sustainSlider2); sustainSlider2.setRange(-12, 12, 0);
    initSlider(releaseSlider2); releaseSlider2.setRange(0, 10, 0);

    notify();
}

//==============================================================================
void GuiPitchEgTab::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiPitchEgTab::resized()
{
    const int labelLeft = 16;
    const int controlLeft = 144;
    const int labelWidth = 120;
    const int sliderWidth = 420;
    const int controlHeight = 24;
    const int gapHeight = 8;

    int top = 20;
    attackLabel1.setBounds (labelLeft, top, labelWidth, controlHeight);
    attackSlider1.setBounds (controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    sustainLabel1.setBounds (labelLeft, top, labelWidth, controlHeight);
    sustainSlider1.setBounds (controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    releaseLabel1.setBounds (labelLeft, top, labelWidth, controlHeight);
    releaseSlider1.setBounds (controlLeft, top, sliderWidth, controlHeight);

    top += controlHeight + 5 * gapHeight;
    attackLabel2.setBounds(labelLeft, top, labelWidth, controlHeight);
    attackSlider2.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    sustainLabel2.setBounds(labelLeft, top, labelWidth, controlHeight);
    sustainSlider2.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    releaseLabel2.setBounds(labelLeft, top, labelWidth, controlHeight);
    releaseSlider2.setBounds(controlLeft, top, sliderWidth, controlHeight);
}

void GuiPitchEgTab::sliderValueChanged (Slider* sliderThatWasMoved)
{
    double value = sliderThatWasMoved->getValue();
    SynthParameters::EnvelopeParams* peg1Params = &pSound->pParams->pitch1EG;
    SynthParameters::EnvelopeParams* peg2Params = &pSound->pParams->pitch2EG;
    if (sliderThatWasMoved == &attackSlider1)
    {
        peg1Params->attackTimeSeconds = value;
    }
    else if (sliderThatWasMoved == &sustainSlider1)
    {
        peg1Params->sustainLevel = value;
    }
    else if (sliderThatWasMoved == &releaseSlider1)
    {
        peg1Params->releaseTimeSeconds = value;
    }
    else if (sliderThatWasMoved == &attackSlider2)
    {
        peg2Params->attackTimeSeconds = value;
    }
    else if (sliderThatWasMoved == &sustainSlider2)
    {
        peg2Params->sustainLevel = value;
    }
    else if (sliderThatWasMoved == &releaseSlider2)
    {
        peg2Params->releaseTimeSeconds = value;
    }
    pSound->parameterChanged();
}

void GuiPitchEgTab::notify()
{
    SynthParameters::EnvelopeParams* peg1Params = &pSound->pParams->pitch1EG;
    attackSlider1.setValue(peg1Params->attackTimeSeconds);
    sustainSlider1.setValue(peg1Params->sustainLevel);
    releaseSlider1.setValue(peg1Params->releaseTimeSeconds);

    SynthParameters::EnvelopeParams* peg2Params = &pSound->pParams->pitch2EG;
    attackSlider2.setValue(peg2Params->attackTimeSeconds);
    sustainSlider2.setValue(peg2Params->sustainLevel);
    releaseSlider2.setValue(peg2Params->releaseTimeSeconds);
}
