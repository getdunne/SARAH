#pragma once
#include "SynthOscillatorBase.h"

class SynthOscillator : public SynthOscillatorBase
{
public:
    SynthOscillator();
    
    void setFrequency(double sampleRateHz, int midiNoteNumber, double centOffset);
    float getSample();

    void setFilterParams(float cutoff, float dBperOctave);
    void setFilterCutoffDelta(float fcDelta);

private:
    int noteNumber;
    float waveTable[2 * fftSize];

    float filterCutoff;            // a fraction [0.0, 1,0]
    float filterSlope;            // dB per octave
};
