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
	GuiMainTab* pMainTab;
	GuiOscTab* pOscTab;
	GuiAmpEgTab* pAmpEgTab;
	GuiFilterTab* pFilter1Tab;
	GuiFilterTab* pFilter2Tab;
	GuiPitchEgTab* pPitchEgTab;
	GuiLFOTab* pLFOTab;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiTabs)
};
