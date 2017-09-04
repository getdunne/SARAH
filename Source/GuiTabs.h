#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "GuiMainTab.h"
#include "GuiOscTab.h"
#include "GuiAmpEgTab.h"
#include "GuiFilterTab.h"
#include "GuiPitchEgTab.h"
#include "GuiLFOTab.h"

class GuiTabs  : public Component
{
public:
    GuiTabs (SynthSound* pSynthSound);
    ~GuiTabs();

    void paint (Graphics& g) override;
    void resized() override;

	void notify();

private:
    ScopedPointer<TabbedComponent> tabbedComponent;
	GuiMainTab mainTab;
	GuiOscTab oscTab;
	GuiAmpEgTab ampEgTab;
	GuiFilterTab filter1Tab, filter2Tab;
	GuiPitchEgTab pitchEgTab;
	GuiLFOTab lfoTab;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiTabs)
};
