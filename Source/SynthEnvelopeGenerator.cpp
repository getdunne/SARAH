#include "SynthEnvelopeGenerator.h"
#include <cmath>

static const char* const segNames[] = { "idle", "attack", "decay", "sustain", "release" };

SynthEnvelopeGenerator::SynthEnvelopeGenerator()
    : sampleRateHz(44100)
    , attackSeconds(0.01)
    , decaySeconds(0.1)
    , releaseSeconds(0.5)
    , sustainLevel(0.5)
    , segment(kIdle)
{
    interpolator.setValue(0.0);
    interpolator.reset(sampleRateHz, 0.0);
}

void SynthEnvelopeGenerator::start (double _sampleRateHz)
{
    //Logger::writeToLog(String("EG start ") + String(segNames[segment]));

    sampleRateHz = _sampleRateHz;

    if (segment == kIdle)
    {
        // start new attack segment from zero
        interpolator.setValue(0.0);
        interpolator.reset(sampleRateHz, attackSeconds);
    }
    else
    {
        // note is still playing but has been retriggered or stolen
        // start new attack from where we are
        double currentValue = interpolator.getNextValue();
        interpolator.setValue(currentValue);
        interpolator.reset(sampleRateHz, attackSeconds * (1.0 - currentValue));
    }

    segment = kAttack;
    interpolator.setValue(1.0);
}

void SynthEnvelopeGenerator::release()
{
    segment = kRelease;
    interpolator.setValue(interpolator.getNextValue());
    interpolator.reset(sampleRateHz, releaseSeconds);
    interpolator.setValue(0.0);
}

float SynthEnvelopeGenerator::getSample()
{
    if (segment == kSustain) return float(sustainLevel);

    if (segment == kIdle || interpolator.isSmoothing())
        return float(interpolator.getNextValue());

    if (segment == kAttack)    // end of attack segment
    {
        if (decaySeconds > 0.0)
        {
            // there is a decay segment
            segment = kDecay;
            interpolator.reset(sampleRateHz, decaySeconds);
            interpolator.setValue(sustainLevel);
            return 1.0;
        }
        else
        {
            // no decay segment; go straight to sustain
            segment = kSustain;
            return float(sustainLevel);
        }
    }
    else if (segment == kDecay)    // end of decay segment
    {
        segment = kSustain;
        return float(sustainLevel);
    }
    else if (segment == kRelease)    // end of release
    {
        segment = kIdle;
    }

    // after end of release segment
    return 0.0f;
}
