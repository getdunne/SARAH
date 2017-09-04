#include "GuiTabs.h"

GuiTabs::GuiTabs (SynthSound* pSynthSound)
{
	pMainTab = new GuiMainTab(pSynthSound);
	pOscTab = new GuiOscTab(pSynthSound);
	pAmpEgTab = new GuiAmpEgTab(pSynthSound);
	pFilter1Tab = new GuiFilterTab(pSynthSound, 0);
	pFilter2Tab = new GuiFilterTab(pSynthSound, 1);
	pPitchEgTab = new GuiPitchEgTab(pSynthSound);
	pLFOTab = new GuiLFOTab(pSynthSound);

    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedComponent->setTabBarDepth (32);
	tabbedComponent->addTab(TRANS("Main"), Colours::lightgrey, pMainTab, true);
    tabbedComponent->addTab (TRANS("Osc"), Colours::lightgrey, pOscTab, true);
	tabbedComponent->addTab(TRANS("Amp"), Colours::lightgrey, pAmpEgTab, true);
	tabbedComponent->addTab(TRANS("Flt1"), Colours::lightgrey, pFilter1Tab, true);
	tabbedComponent->addTab(TRANS("Flt2"), Colours::lightgrey, pFilter2Tab, true);
	tabbedComponent->addTab(TRANS("P.EG"), Colours::lightgrey, pPitchEgTab, true);
	tabbedComponent->addTab(TRANS("LFOs"), Colours::lightgrey, pLFOTab, true);
	tabbedComponent->setCurrentTabIndex(0);

    setSize (400, 300);
}

GuiTabs::~GuiTabs()
{
	// tabbedComponent will take care of deleting our tab objects
    tabbedComponent = nullptr;
}

//==============================================================================
void GuiTabs::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiTabs::resized()
{
    tabbedComponent->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
}

void GuiTabs::notify()
{
	pMainTab->notify();
	pOscTab->notify();
	pAmpEgTab->notify();
	pFilter1Tab->notify();
	pFilter2Tab->notify();
	pPitchEgTab->notify();
	pLFOTab->notify();
}
