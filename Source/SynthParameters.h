#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthOscillatorBase.h"

#define kMaxProgramNameLength 24    // max length supported by VST2
#define kProgNameBufferLength 25    // 1 extra byte for null terminator

class SynthParameters : public SynthOscillatorBase
{
public:
    // program name
    typedef char ProgramName[kProgNameBufferLength];
    ProgramName programName;

    // main
    struct MainParams {
        double masterLevel;
        double oscBlend;                        // [0.0, 1.0] relative osc1 level
        int pitchBendUpSemitones;
        int pitchBendDownSemitones;
    } main;
    
    // oscillators
    struct OscillatorParams {
        WaveformEnum waveform;
        int pitchOffsetSemitones;
        double detuneOffsetCents;
    } osc1, osc2;

    // filters
    struct FilterParams {
        double cutoff;                        // [0.0, 1.0]
        double dBperOctave;
        double envAmount;                    // [0.0, 1.0]
    } filter1, filter2;
    
    // envelope generators
    struct EnvelopeParams {
        double attackTimeSeconds;
        double decayTimeSeconds;
        double sustainLevel;                // [0.0, 1.0]
        double releaseTimeSeconds;
    } ampEG, filter1EG, filter2EG, pitch1EG, pitch2EG;

    // LFOs
    struct LFOParams {
        WaveformEnum waveform;
        double freqHz;
        double amount;        // cents for pitchLFO, percent for filterLFO
    } pitchLFO, filterLFO;

public:
    // Set default values
    void setDefaultValues();

    // Save and Restore from XML
    XmlElement* getXml();
    void putXml(XmlElement* xml);
};
