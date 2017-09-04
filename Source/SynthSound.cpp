#pragma once
#include "SynthSound.h"
#include "Synth.h"

SynthSound::SynthSound(Synth& ownerSynth)
    : SynthesiserSound()
    , synth(ownerSynth)
{
}

void SynthSound::parameterChanged()
{
    synth.soundParameterChanged();
}
