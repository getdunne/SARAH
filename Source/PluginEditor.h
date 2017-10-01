#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class FloatParamSlider : public Slider
{
private:
    float *pParameter;
    float scaleFactor;

public:
    FloatParamSlider(float sf = 1.0f) : Slider(), pParameter(0), scaleFactor(sf) {}

    // initial setup
    void setPointer(float* pf) { pParameter = pf; notify(); }
    void setScale(float sf) { scaleFactor = sf; }

    // gets called whenever slider value is changed by user
    virtual void valueChanged() { if (pParameter) *pParameter = (float)getValue() / scaleFactor; }

    // call this when parameter value changes, to update slider
    void notify() { if (pParameter) setValue(*pParameter * scaleFactor); }
};

class IntParamSlider : public Slider
{
private:
    int* pParameter;

public:
    IntParamSlider() : Slider(), pParameter(0) {}

    void setPointer(int* pi) { pParameter = pi; notify(); }

    virtual void valueChanged() { if (pParameter) *pParameter = (int)getValue(); }

    void notify() { if (pParameter) setValue(*pParameter); }
};

class WaveformComboBox : public ComboBox
{
private:
    SynthWaveform *pWaveform;

public:
    WaveformComboBox() : ComboBox(), pWaveform(0) {}

    void setPointer(SynthWaveform* pWf) { pWaveform = pWf; notify(); }

    virtual void valueChanged(Value&) { if (pWaveform) pWaveform->fromComboBox(*this); }

    void notify() { if (pWaveform) pWaveform->toComboBox(*this); }
};

class MyLookAndFeel : public LookAndFeel_V4
{
public:
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle,
        Slider& slider) override;
};


class SARAHAudioProcessorEditor
    : public AudioProcessorEditor
    , public ChangeListener
    , public ComboBoxListener
    , public SliderListener
{
public:
    SARAHAudioProcessorEditor (SARAHAudioProcessor&);
    ~SARAHAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

    virtual void changeListenerCallback(ChangeBroadcaster*);
    void comboBoxChanged(ComboBox*) override;
    void sliderValueChanged(Slider*) override;

private:
    // some empirical constants used in layout
    static const int windowWidth = 870;
    static const int windowHeight = 450;

    void PaintSarahLogo(Graphics& g);

    Image backgroundImage;
    MyLookAndFeel myLookAndFeel;
    SARAHAudioProcessor& processor;

    Colour backgroundColour;
    bool useBackgroundImage, showGroupBoxes, showLabels, showLogo, showControls;

    GroupComponent gOsc1, gPeg1, gOsc2, gPeg2, gFlt1, gFeg1, gFlt2, gFeg2, gPlfo, gHlfo, gAeg, gMaster;
    WaveformComboBox cbOsc1, cbOsc2, cbPlfo, cbHlfo;
    Label lblOsc1Pitch, lblOsc1Detune, lblOsc1PitchEgAttack, lblOsc1PitchEgSustain, lblOsc1PitchEgRelease;
    Label lblOsc2Pitch, lblOsc2Detune, lblOsc2PitchEgAttack, lblOsc2PitchEgSustain, lblOsc2PitchEgRelease;
    IntParamSlider slOsc1Pitch, slOsc2Pitch;
    FloatParamSlider slOsc1Detune, slOsc1PitchEgAttack, slOsc1PitchEgSustain, slOsc1PitchEgRelease;
    FloatParamSlider slOsc2Detune, slOsc2PitchEgAttack, slOsc2PitchEgSustain, slOsc2PitchEgRelease;
    Label lblFlt1Cutoff, lblFlt1Slope, lblFlt1EnvAmt;
    Label lblFlt1EgAttack, lblFlt1EgDecay, lblFlt1EgSustain, lblFlt1EgRelease;
    Label lblFlt2Cutoff, lblFlt2Slope, lblFlt2EnvAmt;
    Label lblFlt2EgAttack, lblFlt2EgDecay, lblFlt2EgSustain, lblFlt2EgRelease;
    FloatParamSlider slFlt1Cutoff, slFlt1Slope, slFlt1EnvAmt;
    FloatParamSlider slFlt1EgAttack, slFlt1EgDecay, slFlt1EgSustain, slFlt1EgRelease;
    FloatParamSlider slFlt2Cutoff, slFlt2Slope, slFlt2EnvAmt;
    FloatParamSlider slFlt2EgAttack, slFlt2EgDecay, slFlt2EgSustain, slFlt2EgRelease;

    Label lblPitchLfoFreq, lblPitchLfoAmount, lblFilterLfoFreq, lblFilterLfoAmount;
    Label lblMasterVol, lblOscBal, lblPitchBendUp, lblPitchBendDown;
    Label lblAmpEgAttack, lblAmpEgDecay, lblAmpEgSustain, lblAmpEgRelease;
    FloatParamSlider slPitchLfoFreq, slPitchLfoAmount, slFilterLfoFreq, slFilterLfoAmount;
    FloatParamSlider slMasterVol, slOscBal;
    IntParamSlider slPitchBendUp, slPitchBendDown;
    FloatParamSlider slAmpEgAttack, slAmpEgDecay, slAmpEgSustain, slAmpEgRelease;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SARAHAudioProcessorEditor)
};
