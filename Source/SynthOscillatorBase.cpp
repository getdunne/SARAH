#include "SynthOscillatorBase.h"

dsp::FFT *SynthOscillatorBase::forwardFFT;
dsp::FFT *SynthOscillatorBase::inverseFFT;

void SynthOscillatorBase::Initialize()
{
    forwardFFT = new dsp::FFT(fftOrder);
    inverseFFT = new dsp::FFT(fftOrder);

    zeromem(fftWave, sizeof(fftWave));
    for (int i = 0; i < fftSize; i++)
    {
        float phi = float(i) / fftSize;

        sineTable[i] = std::sin(2.0f * float_Pi * phi);

        fftWave[SynthWaveform::kTriangle][i] = 2.0f * (0.5f - std::fabs(phi - 0.5f)) - 1.0f;
        fftWave[SynthWaveform::kSquare][i] = (phi <= 0.5f) ? 1.0f : -1.0f;
        fftWave[SynthWaveform::kSawtooth][i] = 2.0f * phi - 1.0f;
    }

    forwardFFT->performRealOnlyForwardTransform(fftWave[SynthWaveform::kTriangle]);
    forwardFFT->performRealOnlyForwardTransform(fftWave[SynthWaveform::kSquare]);
    forwardFFT->performRealOnlyForwardTransform(fftWave[SynthWaveform::kSawtooth]);
}

void SynthOscillatorBase::Cleanup()
{
#ifndef JUCE_MAC
    delete forwardFFT;
    delete inverseFFT;
#endif
}

float SynthOscillatorBase::sineTable[fftSize];
SynthOscillatorBase::FFTbuf SynthOscillatorBase::fftWave[kWaveTableCount];
