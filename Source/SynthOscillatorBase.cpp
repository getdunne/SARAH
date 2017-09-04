#include "SynthOscillatorBase.h"

static const char* WFundefined = "Undefined";

static const char* WFname[] = {
	"Sine",
	"Triangle",
	"Square",
	"Sawtooth"
};

String SynthOscillatorBase::WaveformName(WaveformEnum wf)
{
	int arrayIndex = int(wf) + 1;
	if (arrayIndex >= 0 && arrayIndex < sizeof(WFname) / sizeof(char*))
		return String(WFname[arrayIndex]);
	else return String(WFundefined);
}

const SynthOscillatorBase::WaveformEnum SynthOscillatorBase::WaveformEnumFromName(String wfname)
{
	int wfIndex = 0;
	for (int i = 0; i < 4; i++)
	{
		if (!strcmp(wfname.toUTF8(), WFname[i]))
		{
			wfIndex = i - 1;
			break;
		}
	}
	return (SynthOscillatorBase::WaveformEnum)wfIndex;
}

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

		fftWave[kTriangle][i] = 2.0f * (0.5f - std::fabs(phi - 0.5f)) - 1.0f;
		fftWave[kSquare][i] = (phi <= 0.5f) ? 1.0f : -1.0f;
		fftWave[kSawtooth][i] = 2.0f * phi - 1.0f;
	}

	forwardFFT->performRealOnlyForwardTransform(fftWave[kTriangle]);
	forwardFFT->performRealOnlyForwardTransform(fftWave[kSquare]);
	forwardFFT->performRealOnlyForwardTransform(fftWave[kSawtooth]);
}

void SynthOscillatorBase::Cleanup()
{
#ifndef JUCE_MAC
	delete forwardFFT;
	delete inverseFFT;
#endif
}

float SynthOscillatorBase::sineTable[fftSize];
SynthOscillatorBase::FFTbuf SynthOscillatorBase::fftWave[kNumberOfWaveforms];

SynthOscillatorBase::SynthOscillatorBase()
	: waveForm(kUndefined)
	, phase(0.0)
	, phaseDelta(0.0)
{
}
