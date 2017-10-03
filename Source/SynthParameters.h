#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthWaveform.h"
#include "SynthOscillatorBase.h"

class SynthParameters : public SynthOscillatorBase
{
public:
    // program name
    String programName;

    // main
    struct MainParams {
        float masterLevel;
        float oscBlend;                        // [0.0, 1.0] relative osc1 level
        int pitchBendUpSemitones;
        int pitchBendDownSemitones;
    } main;
    
    // oscillators
    struct OscillatorParams {
        SynthWaveform waveform;
        int pitchOffsetSemitones;
        float detuneOffsetCents;
    } osc1, osc2;

    // filters
    struct FilterParams {
        float cutoff;                       // [0.0, 1.0]
        float Q;                            // [0.1, 10.0]
        float envAmount;                    // [0.0, 1.0]
    } filter1, filter2;
    
    // envelope generators
    struct EnvelopeParams {
        float attackTimeSeconds;
        float decayTimeSeconds;
        float sustainLevel;                // [0.0, 1.0]
        float releaseTimeSeconds;
    } ampEG, filter1EG, filter2EG, pitch1EG, pitch2EG;

    // LFOs
    struct LFOParams {
        SynthWaveform waveform;
        float freqHz;
        float amount;        // cents for pitchLFO, percent for filterLFO
    } pitchLFO, filterLFO;

public:
    // Set default values
    void setDefaultValues();

    // Save and Restore from XML
    XmlElement* getXml();
    void putXml(XmlElement* xml);
};
