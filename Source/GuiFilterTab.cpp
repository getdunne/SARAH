#include "GuiFilterTab.h"

GuiFilterTab::GuiFilterTab (SynthSound* pSynthSound, int filterIndex)
	: pSound(pSynthSound)
	, whichFilter(filterIndex)
{
	addAndMakeVisible(cutoffLabel = new Label("cutoff label", TRANS("Cutoff (%)")));
	cutoffLabel->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	cutoffLabel->setJustificationType(Justification::centredRight);
	cutoffLabel->setEditable(false, false, false);
	cutoffLabel->setColour(TextEditor::textColourId, Colours::black);
	cutoffLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(cutoffSlider = new Slider("cutoff slider"));
	cutoffSlider->setRange(0, 100, 0);
	cutoffSlider->setSliderStyle(Slider::LinearHorizontal);
	cutoffSlider->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
	cutoffSlider->addListener(this);

	addAndMakeVisible(slopeLabel = new Label("slope label", TRANS("Slope (dB/oct)")));
	slopeLabel->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	slopeLabel->setJustificationType(Justification::centredRight);
	slopeLabel->setEditable(false, false, false);
	slopeLabel->setColour(TextEditor::textColourId, Colours::black);
	slopeLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(slopeSlider = new Slider("slope slider"));
	slopeSlider->setRange(6, 48, 6);
	slopeSlider->setSliderStyle(Slider::LinearHorizontal);
	slopeSlider->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
	slopeSlider->addListener(this);

	addAndMakeVisible(envAmountLabel = new Label("env amount label", TRANS("Env Amount (%)")));
	envAmountLabel->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	envAmountLabel->setJustificationType(Justification::centredRight);
	envAmountLabel->setEditable(false, false, false);
	envAmountLabel->setColour(TextEditor::textColourId, Colours::black);
	envAmountLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(envAmountSlider = new Slider("env amount slider"));
	envAmountSlider->setRange(0, 100, 0);
	envAmountSlider->setSliderStyle(Slider::LinearHorizontal);
	envAmountSlider->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
	envAmountSlider->addListener(this);

	addAndMakeVisible (attackLabel = new Label ("attack label", TRANS("Attack Time (sec)")));
    attackLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    attackLabel->setJustificationType (Justification::centredRight);
    attackLabel->setEditable (false, false, false);
    attackLabel->setColour (TextEditor::textColourId, Colours::black);
    attackLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (attackSlider = new Slider ("attack time slider"));
    attackSlider->setRange (0, 10, 0);
    attackSlider->setSliderStyle (Slider::LinearHorizontal);
    attackSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    attackSlider->addListener (this);

    addAndMakeVisible (decayLabel = new Label ("decay time label", TRANS("Decay Time (sec)")));
    decayLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    decayLabel->setJustificationType (Justification::centredRight);
    decayLabel->setEditable (false, false, false);
    decayLabel->setColour (TextEditor::textColourId, Colours::black);
    decayLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (decaySlider = new Slider ("decay time slider"));
    decaySlider->setRange (0, 10, 0);
    decaySlider->setSliderStyle (Slider::LinearHorizontal);
    decaySlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    decaySlider->addListener (this);

    addAndMakeVisible (sustainLabel = new Label ("sustain level label", TRANS("Sustain Level (%)")));
	sustainLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
	sustainLabel->setJustificationType (Justification::centredRight);
	sustainLabel->setEditable (false, false, false);
	sustainLabel->setColour (TextEditor::textColourId, Colours::black);
	sustainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sustainSlider = new Slider ("sustain level slider"));
    sustainSlider->setRange (0, 100, 1);
    sustainSlider->setSliderStyle (Slider::LinearHorizontal);
    sustainSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    sustainSlider->addListener (this);

    addAndMakeVisible (releaseLabel = new Label ("release time label", TRANS("Release Time (sec)")));
	releaseLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
	releaseLabel->setJustificationType (Justification::centredRight);
	releaseLabel->setEditable (false, false, false);
	releaseLabel->setColour (TextEditor::textColourId, Colours::black);
	releaseLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (releaseSlider = new Slider ("release time slider"));
	releaseSlider->setRange (0, 10, 0);
	releaseSlider->setSliderStyle (Slider::LinearHorizontal);
	releaseSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
	releaseSlider->addListener (this);

	notify();

    setSize (600, 400);
}

GuiFilterTab::~GuiFilterTab()
{
	cutoffLabel = nullptr;
	cutoffSlider = nullptr;
	slopeLabel = nullptr;
	slopeSlider = nullptr;
	envAmountLabel = nullptr;
	envAmountSlider = nullptr;
	attackLabel = nullptr;
    attackSlider = nullptr;
    decayLabel = nullptr;
    decaySlider = nullptr;
    sustainLabel = nullptr;
    sustainSlider = nullptr;
    releaseLabel = nullptr;
    releaseSlider = nullptr;
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
	cutoffLabel->setBounds(labelLeft, top, labelWidth, controlHeight);
	cutoffSlider->setBounds(controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	slopeLabel->setBounds(labelLeft, top, labelWidth, controlHeight);
	slopeSlider->setBounds(controlLeft, top, sliderWidth, controlHeight);

	top += controlHeight + 5 * gapHeight;
	envAmountLabel->setBounds(labelLeft, top, labelWidth, controlHeight);
	envAmountSlider->setBounds(controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + 5 * gapHeight;

	attackLabel->setBounds(labelLeft, top, labelWidth, controlHeight);
	attackSlider->setBounds(controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	decayLabel->setBounds(labelLeft, top, labelWidth, controlHeight);
	decaySlider->setBounds(controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	sustainLabel->setBounds(labelLeft, top, labelWidth, controlHeight);
	sustainSlider->setBounds(controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	releaseLabel->setBounds(labelLeft, top, labelWidth, controlHeight);
	releaseSlider->setBounds(controlLeft, top, sliderWidth, controlHeight);
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

	if (sliderThatWasMoved == cutoffSlider)
	{
		pFilterParams->cutoff = 0.01 * value;
	}
	else if (sliderThatWasMoved == slopeSlider)
	{
		pFilterParams->dBperOctave = value;
	}
	else if (sliderThatWasMoved == envAmountSlider)
	{
		pFilterParams->envAmount = 0.01 * value;
	}
	else if (sliderThatWasMoved == attackSlider)
	{
		pEnvelopeParams->attackTimeSeconds = value;
    }
    else if (sliderThatWasMoved == decaySlider)
    {
		pEnvelopeParams->decayTimeSeconds = value;
    }
    else if (sliderThatWasMoved == sustainSlider)
    {
		pEnvelopeParams->sustainLevel = 0.01 * value;
    }
    else if (sliderThatWasMoved == releaseSlider)
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

	cutoffSlider->setValue(100.0 * pFilterParams->cutoff);
	slopeSlider->setValue(pFilterParams->dBperOctave);
	envAmountSlider->setValue(100.0 * pFilterParams->envAmount);
	attackSlider->setValue(pEnvelopeParams->attackTimeSeconds);
	decaySlider->setValue(pEnvelopeParams->decayTimeSeconds);
	sustainSlider->setValue(100.0 * pEnvelopeParams->sustainLevel);
	releaseSlider->setValue(pEnvelopeParams->releaseTimeSeconds);
}
