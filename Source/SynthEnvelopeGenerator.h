#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

typedef enum
{
    kIdle,
    kAttack,
    kDecay,
    kSustain,
    kRelease
} EG_Segment;

class SynthEnvelopeGenerator
{
private:
    double sampleRateHz;
    LinearSmoothedValue<double> interpolator;
    EG_Segment segment;

public:
    double attackSeconds, decaySeconds, releaseSeconds;
    double sustainLevel;    // [0.0, 1.0]

public:
    SynthEnvelopeGenerator();

    void start(double _sampleRateHz);    // called for note-on
    void release();                        // called for note-off
    void stop() { segment = kIdle; }    // force reset
    bool isRunning() { return segment != kIdle; }
    float getSample ();
};
