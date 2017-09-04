#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthOscillatorBase
{
public:
	SynthOscillatorBase();

	// Unfortunately, FFT objects can't be allocated/initialized statically, so we need these:
	static void Initialize();	// call once when plugin is created
	static void Cleanup();		// call once when plugin is destroyed

	enum WaveformEnum
	{
		kUndefined = -2,
		kSine = -1,
		kTriangle = 0,
		kSquare,
		kSawtooth,

		// final entry: number of waveforms requiring FFT processing
		kNumberOfWaveforms
	};
	static String WaveformName(WaveformEnum wf);
	static const WaveformEnum WaveformEnumFromName(String wfName);

	void setWaveform(WaveformEnum wf) { waveForm = wf; }
	void setFrequency(float cyclesPerSample) { phaseDelta = cyclesPerSample; }
	float getSample() { return 0.0; }	// always override this

protected:
	WaveformEnum waveForm;
	float phase;			// [0.0, 1.0]
	float phaseDelta;		// cycles per sample (fraction)

protected:
	enum
	{
		fftOrder = 10,
		fftSize = 1 << fftOrder
	};

	static float sineTable[fftSize];

	static dsp::FFT *forwardFFT;
	static dsp::FFT *inverseFFT;
	typedef float FFTbuf[2 * fftSize];

	static FFTbuf fftWave[kNumberOfWaveforms];
};
