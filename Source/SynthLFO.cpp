#include "SynthLFO.h"
#include <cmath>
#include "../JuceLibraryCode/JuceHeader.h"	// only for double_Pi constant

// Square/Triangle/Sawtooth waves are computed directly; sine requires
// table lookup with linear interpolation.
float SynthLFO::getSineSample()
{
	// compute index of earlier sample, and fraction of way to next one
	float fsi = phase * fftSize;
	int sampleIndex = int(fsi);
	float frac = fsi - sampleIndex;

	// get earlier sample s0, and later one s1
	float s0 = sineTable[sampleIndex];
	if (++sampleIndex >= fftSize) sampleIndex = 0;
	float s1 = sineTable[sampleIndex];

	// linear interpolation
	return (1.0f - frac) * s0 + frac * s1;
}

float SynthLFO::getSample()
{
	float sample = 0.0f;

	switch (waveForm)
	{
	case kSine:
		sample = getSineSample();
		break;
	case kSquare:
		sample = (phase <= 0.5f) ? 1.0f : -1.0f;
		break;
	case kTriangle:
		sample = 2.0f * (0.5f - std::fabs(phase - 0.5f)) - 1.0f;
		break;
	case kSawtooth:
		sample = 2.0f * phase - 1.0f;
		break;
	}

	phase += phaseDelta;
	while (phase > 1.0) phase -= 1.0;

	return sample;
}
