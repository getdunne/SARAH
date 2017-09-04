#include "GuiFilterTab.h"

GuiFilterTab::GuiFilterTab (SynthSound* pSynthSound, int filterIndex)
	: pSound(pSynthSound)
	, whichFilter(filterIndex)
    , cutoffLabel("cutoff", TRANS("Cutoff (%)"))
    , slopeLabel("slope", TRANS("Slope (dB/oct)"))
    , envAmountLabel("env amount", TRANS("Env Amount (%)"))
    , attackLabel("attack", TRANS("Attack Time (sec)"))
    , decayLabel("decay", TRANS("Decay Time (sec)"))
    , sustainLabel("sustain", TRANS("Sustain Level (%)"))
    , releaseLabel("release", TRANS("Release Time (sec)"))
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

    initLabel(cutoffLabel);
    initLabel(slopeLabel);
    initLabel(envAmountLabel);
    initLabel(attackLabel);
    initLabel(decayLabel);
    initLabel(sustainLabel);
    initLabel(releaseLabel);

    auto initSlider = [this](Slider& slider)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::LinearHorizontal);
        slider.setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
        slider.addListener(this);
    };

    initSlider(cutoffSlider); cutoffSlider.setRange(0, 100, 0);
    initSlider(slopeSlider); slopeSlider.setRange(6, 48, 6);
    initSlider(envAmountSlider); envAmountSlider.setRange(0, 100, 0);
    initSlider(attackSlider); attackSlider.setRange(0, 10, 0);
    initSlider(decaySlider); decaySlider.setRange(0, 10, 0);
    initSlider(sustainSlider); sustainSlider.setRange(0, 100, 1);
    initSlider(releaseSlider); releaseSlider.setRange(0, 10, 0);

    notify();
}

//==============================================================================
void GuiFilterTab::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiFilterTab::resized()
{
	const int labelLeft = 16;
	const int controlLeft = 144;
	const int labelWidth = 120;
	const int sliderWidth = 420;
	const int controlHeight = 24;
	const int gapHeight = 8;

	int top = 20;
	cutoffLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
	cutoffSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	slopeLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
	slopeSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);

	top += controlHeight + 5 * gapHeight;
	envAmountLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
	envAmountSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + 5 * gapHeight;

	attackLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
	attackSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	decayLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
	decaySlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	sustainLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
	sustainSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	releaseLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
	releaseSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
}

void GuiFilterTab::sliderValueChanged (Slider* sliderThatWasMoved)
{
	double value = sliderThatWasMoved->getValue();
	SynthParameters::FilterParams* pFilterParams = (whichFilter == 0)
		? &pSound->pParams->filter1
		: &pSound->pParams->filter2;
	SynthParameters::EnvelopeParams* pEnvelopeParams = (whichFilter == 0)
		? &pSound->pParams->filter1EG
		: &pSound->pParams->filter2EG;

	if (sliderThatWasMoved == &cutoffSlider)
	{
		pFilterParams->cutoff = 0.01 * value;
	}
	else if (sliderThatWasMoved == &slopeSlider)
	{
		pFilterParams->dBperOctave = value;
	}
	else if (sliderThatWasMoved == &envAmountSlider)
	{
		pFilterParams->envAmount = 0.01 * value;
	}
	else if (sliderThatWasMoved == &attackSlider)
	{
		pEnvelopeParams->attackTimeSeconds = value;
    }
    else if (sliderThatWasMoved == &decaySlider)
    {
		pEnvelopeParams->decayTimeSeconds = value;
    }
    else if (sliderThatWasMoved == &sustainSlider)
    {
		pEnvelopeParams->sustainLevel = 0.01 * value;
    }
    else if (sliderThatWasMoved == &releaseSlider)
    {
		pEnvelopeParams->releaseTimeSeconds = value;
    }
	pSound->parameterChanged();
}

void GuiFilterTab::notify()
{
	SynthParameters::FilterParams* pFilterParams = (whichFilter == 0)
		? &pSound->pParams->filter1
		: &pSound->pParams->filter2;
	SynthParameters::EnvelopeParams* pEnvelopeParams = (whichFilter == 0)
		? &pSound->pParams->filter1EG
		: &pSound->pParams->filter2EG;

	cutoffSlider.setValue(100.0 * pFilterParams->cutoff);
	slopeSlider.setValue(pFilterParams->dBperOctave);
	envAmountSlider.setValue(100.0 * pFilterParams->envAmount);
	attackSlider.setValue(pEnvelopeParams->attackTimeSeconds);
	decaySlider.setValue(pEnvelopeParams->decayTimeSeconds);
	sustainSlider.setValue(100.0 * pEnvelopeParams->sustainLevel);
	releaseSlider.setValue(pEnvelopeParams->releaseTimeSeconds);
}
