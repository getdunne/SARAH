#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthParameters.h"

class Synth;

class SynthSound : public SynthesiserSound
{
private:
    Synth& synth;    // reference to owner Synth (does not change)

public:
    SynthSound(Synth& ownerSynth);
    
    // our sound applies to all notes, all channels
    bool appliesToNote(int /*midiNoteNumber*/) override { return true; }
    bool appliesToChannel(int /*midiChannel*/) override { return true; }

    // pointer to current parameters (may change, e.g. when new program selected)
    SynthParameters* pParams;

    // call to notify owner Synth, that one or more parameters have been changed
    void parameterChanged();
};
