#include "Synth.h"
#include "SynthVoice.h"

void Synth::soundParameterChanged()
{
	// Some sound parameter has been changed. Notify all active voices.
	const ScopedLock sl(lock);

	for (int i = 0; i < voices.size(); ++i)
	{
		SynthVoice* const voice = dynamic_cast<SynthVoice*>(voices.getUnchecked(i));
		if (voice->isVoiceActive())
			voice->soundParameterChanged();
	}
}
