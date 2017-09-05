#include "SynthOscillator.h"
#include <cmath>
#include "../JuceLibraryCode/JuceHeader.h"    // only for double_Pi constant

SynthOscillator::SynthOscillator()
    : SynthOscillatorBase()
    , noteNumber(-1)
{
    setFilterParams(1.0f, 12.0f);
}

void SynthOscillator::setFrequency(double sampleRateHz, int midiNoteNumber, double centOffset)
{
    double cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    cyclesPerSecond *= std::pow(2.0, centOffset / 1200);
    phaseDelta = float(cyclesPerSecond / sampleRateHz);
    int maxHarmonicToRetain = int(1.0 / (2.0 * phaseDelta));
    if (maxHarmonicToRetain >= fftSize / 2) maxHarmonicToRetain = fftSize / 2;

    if (noteNumber != midiNoteNumber && waveform.isSine())
    {
        zeromem(waveTable, sizeof(waveTable));
        for (int ip = 1; ip < maxHarmonicToRetain; ip++)
        {
            int in = fftSize - ip;
            float* fftBuffer = SynthOscillatorBase::getFourierTable(waveform);
            memcpy(waveTable + ip, fftBuffer + ip, 2 * sizeof(float)); // positive frequency coefficient
            memcpy(waveTable + in, fftBuffer + in, 2 * sizeof(float)); // negative frequency coefficient
        }
        inverseFFT->performRealOnlyInverseTransform(waveTable);
    }
    noteNumber = midiNoteNumber;
}

void SynthOscillator::setFilterParams(float cutoff, float dBPerOctave)
{
    filterCutoff = cutoff;
    filterSlope = dBPerOctave;
}

void SynthOscillator::setFilterCutoffDelta(float fcDelta)
{
    if (waveform.isSine()) return;

    zeromem(waveTable, sizeof(waveTable));
    int maxHarmonicToRetain = int(1.0 / (2.0 * phaseDelta));
    if (maxHarmonicToRetain >= fftSize / 2) maxHarmonicToRetain = fftSize / 2;

    float cutoffHarmonic = (filterCutoff + fcDelta) * fftSize / 2;

    for (int ip = 1; ip < maxHarmonicToRetain; ip++)
    {
        int in = fftSize - ip;
        float* fftBuffer = SynthOscillatorBase::getFourierTable(waveform);
        memcpy(waveTable + ip, fftBuffer + ip, 2 * sizeof(float)); // positive frequency coefficient
        memcpy(waveTable + in, fftBuffer + in, 2 * sizeof(float)); // negative frequency coefficient

        float fv = 1.0f;
        if (ip > int(cutoffHarmonic)) fv = std::pow(ip / cutoffHarmonic, -filterSlope / 6.0f);
        waveTable[ip + 0] *= fv;
        waveTable[ip + 1] *= fv;
        waveTable[in + 0] *= fv;
        waveTable[in + 1] *= fv;
    }
    inverseFFT->performRealOnlyInverseTransform(waveTable);
}

float SynthOscillator::getSample()
{
    int sampleIndex = int(phase * fftSize + 0.5f);
    if (sampleIndex >= fftSize) sampleIndex = 0;

    phase += phaseDelta;
    while (phase > 1.0) phase -= 1.0;

    if (waveform.isSine()) return sineTable[sampleIndex];
    else return waveTable[sampleIndex];
}
