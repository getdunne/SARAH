#include "SynthParameters.h"

void SynthParameters::setDefaultValues()
{
    programName = "Default";
    main.masterLevel = 0.15;
    main.oscBlend= 0.5;
    main.pitchBendUpSemitones = 2;
    main.pitchBendDownSemitones = 2;

    osc1.pitchOffsetSemitones = 0;
    osc1.detuneOffsetCents = -10.0;

    osc2.pitchOffsetSemitones = 0;
    osc2.detuneOffsetCents = +10.0;

    ampEG.attackTimeSeconds = 0.1;
    ampEG.decayTimeSeconds = 0.1;
    ampEG.sustainLevel = 0.8;
    ampEG.releaseTimeSeconds = 0.5;

    filter1.cutoff = 1.0;
    filter1.dBperOctave = 12.0;
    filter1.envAmount = 0.0f;
    filter1EG.attackTimeSeconds = 0.0;
    filter1EG.decayTimeSeconds = 0.0;
    filter1EG.sustainLevel = 1.0;
    filter1EG.releaseTimeSeconds = 0.0;

    filter2.cutoff = 1.0;
    filter2.dBperOctave = 12.0;
    filter2.envAmount = 0.0f;
    filter2EG.attackTimeSeconds = 0.0;
    filter2EG.decayTimeSeconds = 0.0;
    filter2EG.sustainLevel = 1.0;
    filter2EG.releaseTimeSeconds = 0.0;

    pitch1EG.attackTimeSeconds = 0.0;
    pitch1EG.decayTimeSeconds = 0.0;
    pitch1EG.sustainLevel = 0.0;
    pitch1EG.releaseTimeSeconds = 0.0;

    pitch2EG.attackTimeSeconds = 0.0;
    pitch2EG.decayTimeSeconds = 0.0;
    pitch2EG.sustainLevel = 0.0;
    pitch2EG.releaseTimeSeconds = 0.0;

    pitchLFO.freqHz = 5.0;
    pitchLFO.amount = 0.0;

    filterLFO.freqHz = 5.0;
    filterLFO.amount = 0.0;
}

XmlElement* SynthParameters::getXml()
{
    XmlElement* xml = new XmlElement("program");

    xml->setAttribute("name", programName);

    xml->setAttribute("masterLevel", main.masterLevel);
    xml->setAttribute("oscBlend", main.oscBlend);
    xml->setAttribute("pitchBendUpSemitones", main.pitchBendUpSemitones);
    xml->setAttribute("pitchBendDownSemitones", main.pitchBendDownSemitones);

    xml->setAttribute("osc1Waveform", osc1.waveform.name());
    xml->setAttribute("osc1PitchOffsetSemitones", osc2.pitchOffsetSemitones);
    xml->setAttribute("osc1DetuneOffsetCents", osc1.detuneOffsetCents);

    xml->setAttribute("osc2Waveform", osc2.waveform.name());
    xml->setAttribute("osc2PitchOffsetSemitones", osc2.pitchOffsetSemitones);
    xml->setAttribute("osc2DetuneOffsetCents", osc2.detuneOffsetCents);

    xml->setAttribute("ampEgAttackTimeSeconds", ampEG.attackTimeSeconds);
    xml->setAttribute("ampEgDecayTimeSeconds", ampEG.decayTimeSeconds);
    xml->setAttribute("ampEgSustainLevel", ampEG.sustainLevel);
    xml->setAttribute("ampEgReleaseTimeSeconds", ampEG.releaseTimeSeconds);

    xml->setAttribute("flt1Cutoff", filter1.cutoff);
    xml->setAttribute("flt1dBperOctave", filter1.dBperOctave);
    xml->setAttribute("flt1EnvAmount", filter1.envAmount);
    xml->setAttribute("flt1EgAttackTimeSeconds", filter1EG.attackTimeSeconds);
    xml->setAttribute("flt1EgDecayTimeSeconds", filter1EG.decayTimeSeconds);
    xml->setAttribute("flt1EgSustainLevel", filter1EG.sustainLevel);
    xml->setAttribute("flt1EgReleaseTimeSeconds", filter1EG.releaseTimeSeconds);

    xml->setAttribute("flt2Cutoff", filter2.cutoff);
    xml->setAttribute("flt2dBperOctave", filter2.dBperOctave);
    xml->setAttribute("flt2EnvAmount", filter2.envAmount);
    xml->setAttribute("flt2EgAttackTimeSeconds", filter2EG.attackTimeSeconds);
    xml->setAttribute("flt2EgDecayTimeSeconds", filter2EG.decayTimeSeconds);
    xml->setAttribute("flt2EgSustainLevel", filter2EG.sustainLevel);
    xml->setAttribute("flt2EgReleaseTimeSeconds", filter2EG.releaseTimeSeconds);

    xml->setAttribute("pitchLfoWaveform", pitchLFO.waveform.name());
    xml->setAttribute("pitchLfoFreqHz", pitchLFO.freqHz);
    xml->setAttribute("pitchLfoAmount", pitchLFO.amount);

    xml->setAttribute("filterLfoWaveform", filterLFO.waveform.name());
    xml->setAttribute("filterLfoFreqHz", filterLFO.freqHz);
    xml->setAttribute("filterLfoAmount", filterLFO.amount);

    return xml;
}

void SynthParameters::putXml(XmlElement* xml)
{
    programName = xml->getStringAttribute("name");

    main.masterLevel = xml->getDoubleAttribute("masterLevel");
    main.oscBlend = xml->getDoubleAttribute("oscBlend");
    main.pitchBendUpSemitones = xml->getIntAttribute("pitchBendUpSemitones");
    main.pitchBendDownSemitones = xml->getIntAttribute("pitchBendDownSemitones");

    osc1.waveform.setFromName(xml->getStringAttribute("osc1Waveform"));
    osc2.pitchOffsetSemitones = xml->getIntAttribute("osc1PitchOffsetSemitones");
    osc1.detuneOffsetCents = xml->getDoubleAttribute("osc1DetuneOffsetCents");

    osc2.waveform.setFromName(xml->getStringAttribute("osc2Waveform"));
    osc2.pitchOffsetSemitones = xml->getIntAttribute("osc2PitchOffsetSemitones");
    osc2.detuneOffsetCents = xml->getDoubleAttribute("osc2DetuneOffsetCents");

    ampEG.attackTimeSeconds = xml->getDoubleAttribute("ampEgAttackTimeSeconds");
    ampEG.decayTimeSeconds = xml->getDoubleAttribute("ampEgDecayTimeSeconds");
    ampEG.sustainLevel = xml->getDoubleAttribute("ampEgSustainLevel");
    ampEG.releaseTimeSeconds = xml->getDoubleAttribute("ampEgReleaseTimeSeconds");

    filter1.cutoff = xml->getDoubleAttribute("flt1Cutoff");
    filter1.dBperOctave = xml->getDoubleAttribute("flt1dBperOctave");
    filter1.envAmount = xml->getDoubleAttribute("flt1EnvAmount");
    filter1EG.attackTimeSeconds = xml->getDoubleAttribute("flt1EgAttackTimeSeconds");
    filter1EG.decayTimeSeconds = xml->getDoubleAttribute("flt1EgDecayTimeSeconds");
    filter1EG.sustainLevel = xml->getDoubleAttribute("flt1EgSustainLevel");
    filter1EG.releaseTimeSeconds = xml->getDoubleAttribute("flt1EgReleaseTimeSeconds");

    filter2.cutoff = xml->getDoubleAttribute("flt2Cutoff");
    filter2.dBperOctave = xml->getDoubleAttribute("flt2dBperOctave");
    filter2.envAmount = xml->getDoubleAttribute("flt2EnvAmount");
    filter2EG.attackTimeSeconds = xml->getDoubleAttribute("flt2EgAttackTimeSeconds");
    filter2EG.decayTimeSeconds = xml->getDoubleAttribute("flt2EgDecayTimeSeconds");
    filter2EG.sustainLevel = xml->getDoubleAttribute("flt2EgSustainLevel");
    filter2EG.releaseTimeSeconds = xml->getDoubleAttribute("flt2EgReleaseTimeSeconds");

    pitchLFO.waveform.setFromName(xml->getStringAttribute("pitchLfoWaveform"));
    pitchLFO.freqHz = xml->getIntAttribute("pitchLfoFreqHz");
    pitchLFO.amount = xml->getDoubleAttribute("pitchLfoAmount");

    filterLFO.waveform.setFromName(xml->getStringAttribute("filterLfoWaveform"));
    filterLFO.freqHz = xml->getIntAttribute("filterLfoFreqHz");
    filterLFO.amount = xml->getDoubleAttribute("filterLfoAmount");
}
