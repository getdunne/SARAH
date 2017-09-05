#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthWaveform
{
private:
    enum WaveformTypeIndex {
        kSine = -1,
        kTriangle, kSquare, kSawtooth,  // valid for use as array indices

        kNumberOfWaveformsRequiringFFT,
        kNumberOfWaveformTypes
    } index;
    
    friend class SynthOscillatorBase;
    friend class SynthLFO;
    friend class SynthOscillator;

public:
    // default constructor
    SynthWaveform() : index(kSine) {}

    // set to default state after construction
    void setToDefault() { index = kSine; }

    // sine is special because we don't use array indices
    bool isSine() { return index == kSine; }

    // serialize: get human-readable name of this waveform
    String name();

    // deserialize: set index based on given name
    void setFromName(String wfName);

    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);
    void fromComboBox(ComboBox& cb);
    void toComboBox(ComboBox& cb);

private:
    // waveform names: ordered list of string literals
    static const char* const wfNames[];
};
