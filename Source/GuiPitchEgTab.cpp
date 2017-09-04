#include "GuiPitchEgTab.h"

GuiPitchEgTab::GuiPitchEgTab (SynthSound* pSynthSound)
	: pSound(pSynthSound)
{
    addAndMakeVisible (attackLabel1 = new Label ("attack label1", TRANS("Attack Time (sec)")));
    attackLabel1->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    attackLabel1->setJustificationType (Justification::centredRight);
    attackLabel1->setEditable (false, false, false);
    attackLabel1->setColour (TextEditor::textColourId, Colours::black);
    attackLabel1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (attackSlider1 = new Slider ("attack time slider1"));
    attackSlider1->setRange (0, 10, 0);
    attackSlider1->setSliderStyle (Slider::LinearHorizontal);
    attackSlider1->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    attackSlider1->addListener (this);

    //addAndMakeVisible (decayLabel1 = new Label ("decay time label1", TRANS("Decay Time (sec)")));
    //decayLabel1->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    //decayLabel1->setJustificationType (Justification::centredRight);
    //decayLabel1->setEditable (false, false, false);
    //decayLabel1->setColour (TextEditor::textColourId, Colours::black);
    //decayLabel1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    //addAndMakeVisible (decaySlider1 = new Slider ("decay time slider1"));
    //decaySlider1->setRange (0, 10, 0);
    //decaySlider1->setSliderStyle (Slider::LinearHorizontal);
    //decaySlider1->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    //decaySlider1->addListener (this);

    addAndMakeVisible (sustainLabel1 = new Label ("sustain level label1", TRANS("Sustain (semitones)")));
	sustainLabel1->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
	sustainLabel1->setJustificationType (Justification::centredRight);
	sustainLabel1->setEditable (false, false, false);
	sustainLabel1->setColour (TextEditor::textColourId, Colours::black);
	sustainLabel1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sustainSlider1 = new Slider ("sustain level slider1"));
    sustainSlider1->setRange (-12, 12, 0);
    sustainSlider1->setSliderStyle (Slider::LinearHorizontal);
    sustainSlider1->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    sustainSlider1->addListener (this);

    addAndMakeVisible (releaseLabel1 = new Label ("release time label1", TRANS("Release Time (sec)")));
	releaseLabel1->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
	releaseLabel1->setJustificationType (Justification::centredRight);
	releaseLabel1->setEditable (false, false, false);
	releaseLabel1->setColour (TextEditor::textColourId, Colours::black);
	releaseLabel1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (releaseSlider1 = new Slider ("release time slider1"));
	releaseSlider1->setRange (0, 10, 0);
	releaseSlider1->setSliderStyle (Slider::LinearHorizontal);
	releaseSlider1->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
	releaseSlider1->addListener (this);

	addAndMakeVisible(attackLabel2 = new Label("attack label2", TRANS("Attack Time (sec)")));
	attackLabel2->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	attackLabel2->setJustificationType(Justification::centredRight);
	attackLabel2->setEditable(false, false, false);
	attackLabel2->setColour(TextEditor::textColourId, Colours::black);
	attackLabel2->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(attackSlider2 = new Slider("attack time slider2"));
	attackSlider2->setRange(0, 10, 0);
	attackSlider2->setSliderStyle(Slider::LinearHorizontal);
	attackSlider2->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
	attackSlider2->addListener(this);

	//addAndMakeVisible(decayLabel2 = new Label("decay time label2", TRANS("Decay Time (sec)")));
	//decayLabel2->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	//decayLabel2->setJustificationType(Justification::centredRight);
	//decayLabel2->setEditable(false, false, false);
	//decayLabel2->setColour(TextEditor::textColourId, Colours::black);
	//decayLabel2->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	//addAndMakeVisible(decaySlider2 = new Slider("decay time slider2"));
	//decaySlider2->setRange(0, 10, 0);
	//decaySlider2->setSliderStyle(Slider::LinearHorizontal);
	//decaySlider2->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
	//decaySlider2->addListener(this);

	addAndMakeVisible(sustainLabel2 = new Label("sustain level label2", TRANS("Sustain (semitones)")));
	sustainLabel2->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	sustainLabel2->setJustificationType(Justification::centredRight);
	sustainLabel2->setEditable(false, false, false);
	sustainLabel2->setColour(TextEditor::textColourId, Colours::black);
	sustainLabel2->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(sustainSlider2 = new Slider("sustain level slider2"));
	sustainSlider2->setRange(-12, 12, 0);
	sustainSlider2->setSliderStyle(Slider::LinearHorizontal);
	sustainSlider2->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
	sustainSlider2->addListener(this);

	addAndMakeVisible(releaseLabel2 = new Label("release time label2", TRANS("Release Time (sec)")));
	releaseLabel2->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	releaseLabel2->setJustificationType(Justification::centredRight);
	releaseLabel2->setEditable(false, false, false);
	releaseLabel2->setColour(TextEditor::textColourId, Colours::black);
	releaseLabel2->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(releaseSlider2 = new Slider("release time slider2"));
	releaseSlider2->setRange(0, 10, 0);
	releaseSlider2->setSliderStyle(Slider::LinearHorizontal);
	releaseSlider2->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
	releaseSlider2->addListener(this);

	notify();

    setSize (600, 400);
}

GuiPitchEgTab::~GuiPitchEgTab()
{
    attackLabel1 = nullptr;
    attackSlider1 = nullptr;
    //decayLabel1 = nullptr;
    //decaySlider1 = nullptr;
    sustainLabel1 = nullptr;
    sustainSlider1 = nullptr;
    releaseLabel1 = nullptr;
    releaseSlider1 = nullptr;

	attackLabel2 = nullptr;
	attackSlider2 = nullptr;
	//decayLabel2 = nullptr;
	//decaySlider2 = nullptr;
	sustainLabel2 = nullptr;
	sustainSlider2 = nullptr;
	releaseLabel2 = nullptr;
	releaseSlider2 = nullptr;
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
	attackLabel1->setBounds (labelLeft, top, labelWidth, controlHeight);
    attackSlider1->setBounds (controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	//decayLabel1->setBounds (labelLeft, top, labelWidth, controlHeight);
 //   decaySlider1->setBounds (controlLeft, top, sliderWidth, controlHeight);
	//top += controlHeight + gapHeight;
	sustainLabel1->setBounds (labelLeft, top, labelWidth, controlHeight);
    sustainSlider1->setBounds (controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	releaseLabel1->setBounds (labelLeft, top, labelWidth, controlHeight);
    releaseSlider1->setBounds (controlLeft, top, sliderWidth, controlHeight);

	top += controlHeight + 5 * gapHeight;
	attackLabel2->setBounds(labelLeft, top, labelWidth, controlHeight);
	attackSlider2->setBounds(controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	//decayLabel2->setBounds(labelLeft, top, labelWidth, controlHeight);
	//decaySlider2->setBounds(controlLeft, top, sliderWidth, controlHeight);
	//top += controlHeight + gapHeight;
	sustainLabel2->setBounds(labelLeft, top, labelWidth, controlHeight);
	sustainSlider2->setBounds(controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	releaseLabel2->setBounds(labelLeft, top, labelWidth, controlHeight);
	releaseSlider2->setBounds(controlLeft, top, sliderWidth, controlHeight);
}

void GuiPitchEgTab::sliderValueChanged (Slider* sliderThatWasMoved)
{
	double value = sliderThatWasMoved->getValue();
	SynthParameters::EnvelopeParams* peg1Params = &pSound->pParams->pitch1EG;
	SynthParameters::EnvelopeParams* peg2Params = &pSound->pParams->pitch2EG;
	if (sliderThatWasMoved == attackSlider1)
    {
		peg1Params->attackTimeSeconds = value;
    }
  //  else if (sliderThatWasMoved == decaySlider1)
  //  {
		//peg1Params->decayTimeSeconds = value;
  //  }
    else if (sliderThatWasMoved == sustainSlider1)
    {
		peg1Params->sustainLevel = value;
    }
    else if (sliderThatWasMoved == releaseSlider1)
    {
		peg1Params->releaseTimeSeconds = value;
    }
	else if (sliderThatWasMoved == attackSlider2)
	{
		peg2Params->attackTimeSeconds = value;
	}
	//else if (sliderThatWasMoved == decaySlider2)
	//{
	//	peg2Params->decayTimeSeconds = value;
	//}
	else if (sliderThatWasMoved == sustainSlider2)
	{
		peg2Params->sustainLevel = value;
	}
	else if (sliderThatWasMoved == releaseSlider2)
	{
		peg2Params->releaseTimeSeconds = value;
	}
	pSound->parameterChanged();
}

void GuiPitchEgTab::notify()
{
	SynthParameters::EnvelopeParams* peg1Params = &pSound->pParams->pitch1EG;
	attackSlider1->setValue(peg1Params->attackTimeSeconds);
	//decaySlider1->setValue(peg1Params->decayTimeSeconds);
	sustainSlider1->setValue(peg1Params->sustainLevel);
	releaseSlider1->setValue(peg1Params->releaseTimeSeconds);

	SynthParameters::EnvelopeParams* peg2Params = &pSound->pParams->pitch2EG;
	attackSlider2->setValue(peg2Params->attackTimeSeconds);
	//decaySlider2->setValue(peg2Params->decayTimeSeconds);
	sustainSlider2->setValue(peg2Params->sustainLevel);
	releaseSlider2->setValue(peg2Params->releaseTimeSeconds);
}
