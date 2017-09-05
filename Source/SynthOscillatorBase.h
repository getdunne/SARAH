#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthWaveform.h"

class SynthOscillatorBase
{
public:
    SynthOscillatorBase() : phase(0.0f), phaseDelta(0.0f) {}

    // Unfortunately, FFT objects can't be allocated/initialized statically, so we need these:
    static void Initialize();    // call once when plugin is created
    static void Cleanup();        // call once when plugin is destroyed

    void setWaveform(SynthWaveform wf) { waveform = wf; }
    void setFrequency(float cyclesPerSample) { phaseDelta = cyclesPerSample; }
    float getSample() { return 0.0; }    // always override this

protected:
    SynthWaveform waveform;
    float phase;            // [0.0, 1.0]
    float phaseDelta;       // cycles per sample (fraction)

protected:
    static const int fftOrder = 10;
    static const int fftSize = 1 << fftOrder;

    static float sineTable[fftSize];

    static dsp::FFT *forwardFFT;
    static dsp::FFT *inverseFFT;
    typedef float FFTbuf[2 * fftSize];

    static const int kWaveTableCount = SynthWaveform::kNumberOfWaveformsRequiringFFT;
    static FFTbuf fftWave[kWaveTableCount];

    static float* getFourierTable(SynthWaveform wf) { return fftWave[wf.index]; }
};
