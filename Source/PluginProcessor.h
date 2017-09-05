#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthParameters.h"
#include "SynthSound.h"
#include "Synth.h"

class SARAHAudioProcessor
    : public AudioProcessor
    , public ChangeBroadcaster
{
public:
    SARAHAudioProcessor();
    virtual ~SARAHAudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void getCurrentProgramStateInformation(MemoryBlock& destData) override;
    void setCurrentProgramStateInformation(const void* data, int sizeInBytes) override;

public:
    SynthSound* getSound() { return pSound; }

private:
    static const int kNumberOfPrograms = 128;
    static const int kNumberOfVoices = 16;

    Synth synth;
    SynthSound* pSound;
    SynthParameters programBank[kNumberOfPrograms];
    int currentProgram;

private:
    void initializePrograms();

    //void loadNewSample(const void* data, int dataSize);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SARAHAudioProcessor)
};
