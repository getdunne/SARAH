#include "GuiAmpEgTab.h"

GuiAmpEgTab::GuiAmpEgTab (SynthSound* pSynthSound)
	: pSound(pSynthSound)
{
    addAndMakeVisible (attackLabel = new Label ("attack label",
                                                TRANS("Attack Time (sec)")));
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

    addAndMakeVisible (decayLabel = new Label ("decay time label",
                                               TRANS("Decay Time (sec)")));
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

    addAndMakeVisible (sustainLabel = new Label ("sustain level label",
                                                 TRANS("Sustain Level (%)")));
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

    addAndMakeVisible (releaseLabel = new Label ("release time label",
                                              TRANS("Release Time (sec)")));
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

GuiAmpEgTab::~GuiAmpEgTab()
{
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
void GuiAmpEgTab::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiAmpEgTab::resized()
{
	const int labelLeft = 16;
	const int controlLeft = 144;
	const int labelWidth = 120;
	const int sliderWidth = 420;
	const int controlHeight = 24;
	const int gapHeight = 8;

	int top = 20;
	attackLabel->setBounds (labelLeft, top, labelWidth, controlHeight);
    attackSlider->setBounds (controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	decayLabel->setBounds (labelLeft, top, labelWidth, controlHeight);
    decaySlider->setBounds (controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	sustainLabel->setBounds (labelLeft, top, labelWidth, controlHeight);
    sustainSlider->setBounds (controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	releaseLabel->setBounds (labelLeft, top, labelWidth, controlHeight);
    releaseSlider->setBounds (controlLeft, top, sliderWidth, controlHeight);
}

void GuiAmpEgTab::sliderValueChanged (Slider* sliderThatWasMoved)
{
	double value = sliderThatWasMoved->getValue();
	SynthParameters::EnvelopeParams* pParams = &pSound->pParams->ampEG;
	if (sliderThatWasMoved == attackSlider)
    {
		pParams->attackTimeSeconds = value;
    }
    else if (sliderThatWasMoved == decaySlider)
    {
		pParams->decayTimeSeconds = value;
    }
    else if (sliderThatWasMoved == sustainSlider)
    {
		pParams->sustainLevel = 0.01 * value;
    }
    else if (sliderThatWasMoved == releaseSlider)
    {
		pParams->releaseTimeSeconds = value;
    }
	pSound->parameterChanged();
}

void GuiAmpEgTab::notify()
{
	SynthParameters::EnvelopeParams* pParams = &pSound->pParams->ampEG;
	attackSlider->setValue(pParams->attackTimeSeconds);
	decaySlider->setValue(pParams->decayTimeSeconds);
	sustainSlider->setValue(100.0 * pParams->sustainLevel);
	releaseSlider->setValue(pParams->releaseTimeSeconds);
}
