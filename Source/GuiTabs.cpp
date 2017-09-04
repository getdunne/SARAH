#include "GuiTabs.h"

GuiTabs::GuiTabs (SynthSound* pSynthSound)
    : mainTab(pSynthSound)
    , oscTab(pSynthSound)
    , ampEgTab(pSynthSound)
    , filter1Tab(pSynthSound, 0)
    , filter2Tab(pSynthSound, 1)
    , pitchEgTab(pSynthSound)
    , lfoTab(pSynthSound)
{
    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedComponent->setTabBarDepth (32);
    tabbedComponent->addTab(TRANS("Main"), Colours::lightgrey, &mainTab, true);
    tabbedComponent->addTab(TRANS("Osc"), Colours::lightgrey, &oscTab, true);
    tabbedComponent->addTab(TRANS("Amp"), Colours::lightgrey, &ampEgTab, true);
    tabbedComponent->addTab(TRANS("Flt1"), Colours::lightgrey, &filter1Tab, true);
    tabbedComponent->addTab(TRANS("Flt2"), Colours::lightgrey, &filter2Tab, true);
    tabbedComponent->addTab(TRANS("P.EG"), Colours::lightgrey, &pitchEgTab, true);
    tabbedComponent->addTab(TRANS("LFOs"), Colours::lightgrey, &lfoTab, true);
    tabbedComponent->setCurrentTabIndex(0);
}

GuiTabs::~GuiTabs()
{
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
    mainTab.notify();
    oscTab.notify();
    ampEgTab.notify();
    filter1Tab.notify();
    filter2Tab.notify();
    pitchEgTab.notify();
    lfoTab.notify();
}
