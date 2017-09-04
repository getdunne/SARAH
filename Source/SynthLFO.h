#pragma once
#include "SynthOscillatorBase.h"

class SynthLFO : public SynthOscillatorBase
{
public:
	SynthLFO() : SynthOscillatorBase() {}
    
	float getSample();

protected:
	float getSineSample();
};
