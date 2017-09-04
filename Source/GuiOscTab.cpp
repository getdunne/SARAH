#include "GuiOscTab.h"

GuiOscTab::GuiOscTab (SynthSound* pSynthSound)
	: pSound(pSynthSound)
{
    addAndMakeVisible (wfLabel1 = new Label ("waveform label1", TRANS("Osc1 Waveform")));
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

    addAndMakeVisible (semiLabel1 = new Label ("semitone offset label1", TRANS("Pitch (semitones)")));
    semiLabel1->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    semiLabel1->setJustificationType (Justification::centredRight);
    semiLabel1->setEditable (false, false, false);
    semiLabel1->setColour (TextEditor::textColourId, Colours::black);
    semiLabel1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (semiSlider1 = new Slider ("semitone offset slider1"));
    semiSlider1->setRange (-24, 24, 1);
    semiSlider1->setSliderStyle (Slider::LinearHorizontal);
    semiSlider1->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    semiSlider1->addListener (this);

    addAndMakeVisible (detuneLabel1 = new Label ("detune label1", TRANS("Detune (cents)")));
	detuneLabel1->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
	detuneLabel1->setJustificationType (Justification::centredRight);
	detuneLabel1->setEditable (false, false, false);
	detuneLabel1->setColour (TextEditor::textColourId, Colours::black);
	detuneLabel1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (detuneSlider1 = new Slider ("detune slider1"));
    detuneSlider1->setRange (-50, 50, 0);
    detuneSlider1->setSliderStyle (Slider::LinearHorizontal);
    detuneSlider1->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    detuneSlider1->addListener (this);


	addAndMakeVisible(wfLabel2 = new Label("waveform label2", TRANS("Osc2 Waveform")));
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

	addAndMakeVisible(semiLabel2 = new Label("semitone offset label2", TRANS("Pitch (semitones)")));
	semiLabel2->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	semiLabel2->setJustificationType(Justification::centredRight);
	semiLabel2->setEditable(false, false, false);
	semiLabel2->setColour(TextEditor::textColourId, Colours::black);
	semiLabel2->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(semiSlider2 = new Slider("semitone offset slider2"));
	semiSlider2->setRange(-24, 24, 1);
	semiSlider2->setSliderStyle(Slider::LinearHorizontal);
	semiSlider2->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
	semiSlider2->addListener(this);

	addAndMakeVisible(detuneLabel2 = new Label("detune label2", TRANS("Detune (cents)")));
	detuneLabel2->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	detuneLabel2->setJustificationType(Justification::centredRight);
	detuneLabel2->setEditable(false, false, false);
	detuneLabel2->setColour(TextEditor::textColourId, Colours::black);
	detuneLabel2->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(detuneSlider2 = new Slider("detune slider2"));
	detuneSlider2->setRange(-50, 50, 0);
	detuneSlider2->setSliderStyle(Slider::LinearHorizontal);
	detuneSlider2->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
	detuneSlider2->addListener(this);


	addAndMakeVisible(oscBlendLabel = new Label("osc blend label", TRANS("Blend")));
	oscBlendLabel->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	oscBlendLabel->setJustificationType(Justification::centred);
	oscBlendLabel->setEditable(false, false, false);
	oscBlendLabel->setColour(TextEditor::textColourId, Colours::black);
	oscBlendLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(oscBlendSlider = new Slider("Osc1 Percent"));
	oscBlendSlider->setRange(0, 100, 0);
	oscBlendSlider->setSliderStyle(Slider::LinearVertical);
	oscBlendSlider->setTextBoxStyle(Slider::TextBoxAbove, false, 80, 20);
	oscBlendSlider->addListener(this);

	notify();

    setSize (600, 400);
}

GuiOscTab::~GuiOscTab()
{
    wfLabel1 = nullptr;
    waveformCB1 = nullptr;
    semiLabel1 = nullptr;
    semiSlider1 = nullptr;
    detuneLabel1 = nullptr;
    detuneSlider1 = nullptr;

	wfLabel2 = nullptr;
	waveformCB2 = nullptr;
	semiLabel2 = nullptr;
	semiSlider2 = nullptr;
	detuneLabel2 = nullptr;
	detuneSlider2 = nullptr;

	oscBlendLabel = nullptr;
	oscBlendSlider = nullptr;
}

//==============================================================================
void GuiOscTab::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
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
    wfLabel1->setBounds (labelLeft, top, labelWidth, controlHeight);
    waveformCB1->setBounds (controlLeft, top, cboxWidth, controlHeight);
	top += controlHeight + gapHeight;
    semiLabel1->setBounds (labelLeft, top, labelWidth, controlHeight);
    semiSlider1->setBounds (controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	detuneLabel1->setBounds (labelLeft, top, labelWidth, controlHeight);
    detuneSlider1->setBounds (controlLeft, top, sliderWidth, controlHeight);

	top += controlHeight + 5 * gapHeight;
	wfLabel2->setBounds(labelLeft, top, labelWidth, controlHeight);
	waveformCB2->setBounds(controlLeft, top, cboxWidth, controlHeight);
	top += controlHeight + gapHeight;
	semiLabel2->setBounds(labelLeft, top, labelWidth, controlHeight);
	semiSlider2->setBounds(controlLeft, top, sliderWidth, controlHeight);
	top += controlHeight + gapHeight;
	detuneLabel2->setBounds(labelLeft, top, labelWidth, controlHeight);
	detuneSlider2->setBounds(controlLeft, top, sliderWidth, controlHeight);

	top = 20;
	oscBlendSlider->setBounds(blendSliderLeft, top, blendSliderWidth, blendSliderHeight);
	top += blendSliderHeight + gapHeight;
	oscBlendLabel->setBounds(blendSliderLeft+ blendSliderWidth /2-labelWidth/2, top, labelWidth, controlHeight);
}

void GuiOscTab::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
	SynthOscillatorBase::WaveformEnum wf = (SynthOscillatorBase::WaveformEnum)
		(SynthOscillatorBase::kSine + comboBoxThatHasChanged->getSelectedItemIndex());
	SynthParameters* pParams = pSound->pParams;
	if (comboBoxThatHasChanged == waveformCB1)
    {
		pParams->osc1.waveform = wf;
    }
	else if (comboBoxThatHasChanged == waveformCB2)
	{
		pParams->osc2.waveform = wf;
	}
	pSound->parameterChanged();
}

void GuiOscTab::sliderValueChanged (Slider* sliderThatWasMoved)
{
	double value = sliderThatWasMoved->getValue();
	SynthParameters* pParams = pSound->pParams;
	if (sliderThatWasMoved == semiSlider1)
    {
		pParams->osc1.pitchOffsetSemitones = int(value);
    }
	else if (sliderThatWasMoved == semiSlider2)
	{
		pParams->osc2.pitchOffsetSemitones = int(value);
	}
	else if (sliderThatWasMoved == detuneSlider1)
    {
		pParams->osc1.detuneOffsetCents = value;
	}
	else if (sliderThatWasMoved == detuneSlider2)
	{
		pParams->osc2.detuneOffsetCents = value;
	}
	else if (sliderThatWasMoved == oscBlendSlider)
	{
		pParams->main.oscBlend = 0.01 * value;
	}
	pSound->parameterChanged();
}

void GuiOscTab::notify()
{
	SynthParameters* pParams = pSound->pParams;

	waveformCB1->setSelectedItemIndex(int(pParams->osc1.waveform - SynthOscillatorBase::kSine));
	semiSlider1->setValue(pParams->osc1.pitchOffsetSemitones);
	detuneSlider1->setValue(pParams->osc1.detuneOffsetCents);

	waveformCB2->setSelectedItemIndex(int(pParams->osc2.waveform - SynthOscillatorBase::kSine));
	semiSlider2->setValue(pParams->osc2.pitchOffsetSemitones);
	detuneSlider2->setValue(pParams->osc2.detuneOffsetCents);

	oscBlendSlider->setValue(100.0 * pParams->main.oscBlend);
}
