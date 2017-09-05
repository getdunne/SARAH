#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthEnvelopeGenerator
{
private:
    double sampleRateHz;
    LinearSmoothedValue<double> interpolator;

    enum class EG_Segment
    {
        idle,
        attack,
        decay,
        sustain,
        release
    } segment;

public:
    double attackSeconds, decaySeconds, releaseSeconds;
    double sustainLevel;    // [0.0, 1.0]

public:
    SynthEnvelopeGenerator();

    void start(double _sampleRateHz);   // called for note-on
    void release();                     // called for note-off
    bool isRunning() { return segment != EG_Segment::idle; }
    void stop() { segment = EG_Segment::idle; }
    float getSample();
};
