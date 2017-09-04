#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "GuiTabs.h"

class SARAHAudioProcessorEditor
    : public AudioProcessorEditor
    , public ChangeListener
{
public:
    SARAHAudioProcessorEditor (SARAHAudioProcessor&);
    ~SARAHAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

    virtual void changeListenerCallback(ChangeBroadcaster* source);

private:
    SARAHAudioProcessor& processor;
    GuiTabs guiTabs;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SARAHAudioProcessorEditor)
};
