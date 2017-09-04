#include "GuiMainTab.h"

//==============================================================================
GuiMainTab::GuiMainTab (SynthSound* pSynthSound)
	: pSound(pSynthSound)
{
    addAndMakeVisible (masterLevelLabel = new Label ("master level label", TRANS("Master Volume")));
	masterLevelLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
	masterLevelLabel->setJustificationType (Justification::centredRight);
	masterLevelLabel->setEditable (false, false, false);
	masterLevelLabel->setColour (TextEditor::textColourId, Colours::black);
	masterLevelLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (masterLevelSlider = new Slider ("Master Volume"));
	masterLevelSlider->setRange (0, 10, 0);
	masterLevelSlider->setSliderStyle (Slider::LinearHorizontal);
	masterLevelSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
	masterLevelSlider->addListener (this);

	addAndMakeVisible(pbUpLabel = new Label("PB up semis", TRANS("P.Bend up (semi)")));
	pbUpLabel->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	pbUpLabel->setJustificationType(Justification::centredRight);
	pbUpLabel->setEditable(false, false, false);
	pbUpLabel->setColour(TextEditor::textColourId, Colours::black);
	pbUpLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(pbUpSlider = new Slider("PB up semis"));
	pbUpSlider->setRange(0, 12, 1);
	pbUpSlider->setSliderStyle(Slider::LinearHorizontal);
	pbUpSlider->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
	pbUpSlider->addListener(this);

	addAndMakeVisible(pbDownLabel = new Label("PB down semis", TRANS("P.Bend down (semi)")));
	pbDownLabel->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	pbDownLabel->setJustificationType(Justification::centredRight);
	pbDownLabel->setEditable(false, false, false);
	pbDownLabel->setColour(TextEditor::textColourId, Colours::black);
	pbDownLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(pbDownSlider = new Slider("PB down semis"));
	pbDownSlider->setRange(0, 12, 1);
	pbDownSlider->setSliderStyle(Slider::LinearHorizontal);
	pbDownSlider->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
	pbDownSlider->addListener(this);

	notify();

    setSize (600, 400);
}

GuiMainTab::~GuiMainTab()
{
	masterLevelLabel = nullptr;
	masterLevelSlider = nullptr;
	pbUpLabel = nullptr;
	pbUpSlider = nullptr;
	pbDownLabel = nullptr;
	pbDownSlider = nullptr;
}

//==============================================================================
void GuiMainTab::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
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
	masterLevelLabel->setBounds (labelLeft, top, labelWidth, controlHeight);
	masterLevelSlider->setBounds (controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + 5 * gapHeight;
	pbUpLabel->setBounds(labelLeft, top, labelWidth, controlHeight);
	pbUpSlider->setBounds(controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	pbDownLabel->setBounds(labelLeft, top, labelWidth, controlHeight);
	pbDownSlider->setBounds(controlLeft, top, sliderWidth, controlHeight);
}

void GuiMainTab::sliderValueChanged (Slider* sliderThatWasMoved)
{
	double value = sliderThatWasMoved->getValue();
	SynthParameters::MainParams* pParams = &pSound->pParams->main;
	if (sliderThatWasMoved == masterLevelSlider)
    {
		pParams->masterLevel = 0.1 * value;
    }
	else if (sliderThatWasMoved == pbUpSlider)
	{
		pParams->pitchBendUpSemitones = int(value);
	}
	else if (sliderThatWasMoved == pbDownSlider)
	{
		pParams->pitchBendDownSemitones = int(value);
	}
	pSound->parameterChanged();
}

void GuiMainTab::notify()
{
	SynthParameters::MainParams* pParams = &pSound->pParams->main;
	masterLevelSlider->setValue(10.0 * pParams->masterLevel);
	pbUpSlider->setValue(pParams->pitchBendUpSemitones);
	pbDownSlider->setValue(pParams->pitchBendDownSemitones);
}
