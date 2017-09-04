#pragma once
/*
	Class Synth represents the Synthesizer itself. It derives from juce::Synthsiser,
	and adds a member function to notify all active voices when any sound parameter
	changes, e.g. when a change has been made in the GUI editor, or due to parameter
	automation from the plugin host (DAW).
*/
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthParameters.h"

class Synth : public Synthesiser
{
public:
	void soundParameterChanged();
};
