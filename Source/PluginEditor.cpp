#include "PluginProcessor.h"
#include "PluginEditor.h"

SARAHAudioProcessorEditor::SARAHAudioProcessorEditor (SARAHAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , processor (p)
    , guiTabs(p.getSound())
{
    setSize (600, 400);
    addAndMakeVisible(&guiTabs);
    p.addChangeListener(this);
}

SARAHAudioProcessorEditor::~SARAHAudioProcessorEditor()
{
    processor.removeChangeListener(this);
}

void SARAHAudioProcessorEditor::paint (Graphics& g)
{
    ignoreUnused(g);
}

void SARAHAudioProcessorEditor::resized()
{
    guiTabs.setBounds(0, 0, proportionOfWidth(1.0000f), proportionOfHeight(1.0000f));
}

void SARAHAudioProcessorEditor::changeListenerCallback(ChangeBroadcaster* source)
{
    ignoreUnused(source);
    guiTabs.notify();
}