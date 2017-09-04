#include "GuiLFOTab.h"

GuiLFOTab::GuiLFOTab (SynthSound* pSynthSound)
	: pSound(pSynthSound)
{
    addAndMakeVisible (wfLabel1 = new Label ("waveform label1", TRANS("Pitch LFO")));
    wfLabel1->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    wfLabel1->setJustificationType (Justification::centredRight);
    wfLabel1->setEditable (false, false, false);
    wfLabel1->setColour (TextEditor::textColourId, Colours::black);
    wfLabel1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (waveformCB1 = new ComboBox ("waveform combo1"));
    waveformCB1->setEditableText (false);
    waveformCB1->setJustificationType (Justification::centredLeft);
    waveformCB1->setTextWhenNothingSelected (String());
    waveformCB1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    waveformCB1->addItem (TRANS("Sine"), 1);
    waveformCB1->addItem (TRANS("Triangle"), 2);
    waveformCB1->addItem (TRANS("Square"), 3);
    waveformCB1->addItem (TRANS("Sawtooth"), 4);
    waveformCB1->addListener (this);

    addAndMakeVisible (freqLabel1 = new Label ("freq label1", TRANS("Frequency (Hz)")));
    freqLabel1->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    freqLabel1->setJustificationType (Justification::centredRight);
    freqLabel1->setEditable (false, false, false);
    freqLabel1->setColour (TextEditor::textColourId, Colours::black);
    freqLabel1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (freqSlider1 = new Slider ("freq slider1"));
    freqSlider1->setRange (0.1, 10.0, 0);
    freqSlider1->setSliderStyle (Slider::LinearHorizontal);
    freqSlider1->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    freqSlider1->addListener (this);

    addAndMakeVisible (amountLabel1 = new Label ("amount label1", TRANS("Amount (cents)")));
	amountLabel1->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
	amountLabel1->setJustificationType (Justification::centredRight);
	amountLabel1->setEditable (false, false, false);
	amountLabel1->setColour (TextEditor::textColourId, Colours::black);
	amountLabel1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (amountSlider1 = new Slider ("amount slider1"));
    amountSlider1->setRange (0, 100, 0);
    amountSlider1->setSliderStyle (Slider::LinearHorizontal);
    amountSlider1->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    amountSlider1->addListener (this);


	addAndMakeVisible(wfLabel2 = new Label("waveform label2", TRANS("Filter LFO")));
	wfLabel2->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	wfLabel2->setJustificationType(Justification::centredRight);
	wfLabel2->setEditable(false, false, false);
	wfLabel2->setColour(TextEditor::textColourId, Colours::black);
	wfLabel2->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(waveformCB2 = new ComboBox("waveform combo2"));
	waveformCB2->setEditableText(false);
	waveformCB2->setJustificationType(Justification::centredLeft);
	waveformCB2->setTextWhenNothingSelected(String());
	waveformCB2->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
	waveformCB2->addItem(TRANS("Sine"), 1);
	waveformCB2->addItem(TRANS("Triangle"), 2);
	waveformCB2->addItem(TRANS("Square"), 3);
	waveformCB2->addItem(TRANS("Sawtooth"), 4);
	waveformCB2->addListener(this);

	addAndMakeVisible(freqLabel2 = new Label("freq label2", TRANS("Frequency (Hz)")));
	freqLabel2->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	freqLabel2->setJustificationType(Justification::centredRight);
	freqLabel2->setEditable(false, false, false);
	freqLabel2->setColour(TextEditor::textColourId, Colours::black);
	freqLabel2->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(freqSlider2 = new Slider("freq slider2"));
	freqSlider2->setRange(0.1, 10.0, 0);
	freqSlider2->setSliderStyle(Slider::LinearHorizontal);
	freqSlider2->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
	freqSlider2->addListener(this);

	addAndMakeVisible(amountLabel2 = new Label("amount label2", TRANS("Amount (%)")));
	amountLabel2->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	amountLabel2->setJustificationType(Justification::centredRight);
	amountLabel2->setEditable(false, false, false);
	amountLabel2->setColour(TextEditor::textColourId, Colours::black);
	amountLabel2->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(amountSlider2 = new Slider("amount slider2"));
	amountSlider2->setRange(0, 100, 0);
	amountSlider2->setSliderStyle(Slider::LinearHorizontal);
	amountSlider2->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
	amountSlider2->addListener(this);

	notify();

    setSize (600, 400);
}

GuiLFOTab::~GuiLFOTab()
{
    wfLabel1 = nullptr;
    waveformCB1 = nullptr;
    freqLabel1 = nullptr;
    freqSlider1 = nullptr;
    amountLabel1 = nullptr;
    amountSlider1 = nullptr;

	wfLabel2 = nullptr;
	waveformCB2 = nullptr;
	freqLabel2 = nullptr;
	freqSlider2 = nullptr;
	amountLabel2 = nullptr;
	amountSlider2 = nullptr;
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
    wfLabel1->setBounds (labelLeft, top, labelWidth, controlHeight);
    waveformCB1->setBounds (controlLeft, top, cboxWidth, controlHeight);
	top += controlHeight + gapHeight;
    freqLabel1->setBounds (labelLeft, top, labelWidth, controlHeight);
    freqSlider1->setBounds (controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	amountLabel1->setBounds (labelLeft, top, labelWidth, controlHeight);
    amountSlider1->setBounds (controlLeft, top, sliderWidth, controlHeight);

	top += controlHeight + 5 * gapHeight;
	wfLabel2->setBounds(labelLeft, top, labelWidth, controlHeight);
	waveformCB2->setBounds(controlLeft, top, cboxWidth, controlHeight);
	top += controlHeight + gapHeight;
	freqLabel2->setBounds(labelLeft, top, labelWidth, controlHeight);
	freqSlider2->setBounds(controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	amountLabel2->setBounds(labelLeft, top, labelWidth, controlHeight);
	amountSlider2->setBounds(controlLeft, top, sliderWidth, controlHeight);
}

void GuiLFOTab::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
	SynthOscillatorBase::WaveformEnum wf = (SynthOscillatorBase::WaveformEnum)
		(SynthOscillatorBase::kSine + comboBoxThatHasChanged->getSelectedItemIndex());
	SynthParameters* pParams = pSound->pParams;
	if (comboBoxThatHasChanged == waveformCB1)
    {
		pParams->pitchLFO.waveform = wf;
    }
	else if (comboBoxThatHasChanged == waveformCB2)
	{
		pParams->filterLFO.waveform = wf;
	}
	pSound->parameterChanged();
}

void GuiLFOTab::sliderValueChanged (Slider* sliderThatWasMoved)
{
	double value = sliderThatWasMoved->getValue();
	SynthParameters* pParams = pSound->pParams;
	if (sliderThatWasMoved == freqSlider1)
    {
		pParams->pitchLFO.freqHz = value;
    }
	else if (sliderThatWasMoved == freqSlider2)
	{
		pParams->filterLFO.freqHz = value;
	}
	else if (sliderThatWasMoved == amountSlider1)
    {
		pParams->pitchLFO.amount = value;	// cents
	}
	else if (sliderThatWasMoved == amountSlider2)
	{
		pParams->filterLFO.amount = 0.01 * value;	// percent -> fraction
	}
	pSound->parameterChanged();
}

void GuiLFOTab::notify()
{
	SynthParameters* pParams = pSound->pParams;

	waveformCB1->setSelectedItemIndex(int(pParams->pitchLFO.waveform - SynthOscillatorBase::kSine));
	freqSlider1->setValue(pParams->pitchLFO.freqHz);
	amountSlider1->setValue(pParams->pitchLFO.amount);

	waveformCB2->setSelectedItemIndex(int(pParams->filterLFO.waveform - SynthOscillatorBase::kSine));
	freqSlider2->setValue(pParams->filterLFO.freqHz);
	amountSlider2->setValue(100.0 * pParams->filterLFO.amount);	// fraction -> percent
}
