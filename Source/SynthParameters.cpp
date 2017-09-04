#include "SynthParameters.h"

void SynthParameters::setDefaultValues()
{
	sprintf(programName, "Default");
	main.masterLevel = 0.15;
	main.oscBlend= 0.5;
	main.pitchBendUpSemitones = 2;
	main.pitchBendDownSemitones = 2;

	osc1.waveform = kSine;
	osc1.pitchOffsetSemitones = 0;
	osc1.detuneOffsetCents = -10.0;

	osc2.waveform = kSine;
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

	pitchLFO.waveform = kSine;
	pitchLFO.freqHz = 5.0;
	pitchLFO.amount = 0.0;

	filterLFO.waveform = kSine;
	filterLFO.freqHz = 5.0;
	filterLFO.amount = 0.0;
}

XmlElement* SynthParameters::getXml()
{
	XmlElement* xml = new XmlElement("program");

	xml->setAttribute(String("name"), String(programName));

	xml->setAttribute(String("masterLevel"), main.masterLevel);
	xml->setAttribute(String("oscBlend"), main.oscBlend);
	xml->setAttribute(String("pitchBendUpSemitones"), main.pitchBendUpSemitones);
	xml->setAttribute(String("pitchBendDownSemitones"), main.pitchBendDownSemitones);

	xml->setAttribute(String("osc1Waveform"), SynthOscillatorBase::WaveformName(osc1.waveform));
	xml->setAttribute(String("osc1PitchOffsetSemitones"), osc2.pitchOffsetSemitones);
	xml->setAttribute(String("osc1DetuneOffsetCents"), osc1.detuneOffsetCents);

	xml->setAttribute(String("osc2Waveform"), SynthOscillatorBase::WaveformName(osc2.waveform));
	xml->setAttribute(String("osc2PitchOffsetSemitones"), osc2.pitchOffsetSemitones);
	xml->setAttribute(String("osc2DetuneOffsetCents"), osc2.detuneOffsetCents);

	xml->setAttribute(String("ampEgAttackTimeSeconds"), ampEG.attackTimeSeconds);
	xml->setAttribute(String("ampEgDecayTimeSeconds"), ampEG.decayTimeSeconds);
	xml->setAttribute(String("ampEgSustainLevel"), ampEG.sustainLevel);
	xml->setAttribute(String("ampEgReleaseTimeSeconds"), ampEG.releaseTimeSeconds);

	xml->setAttribute(String("flt1Cutoff"), filter1.cutoff);
	xml->setAttribute(String("flt1dBperOctave"), filter1.dBperOctave);
	xml->setAttribute(String("flt1EnvAmount"), filter1.envAmount);
	xml->setAttribute(String("flt1EgAttackTimeSeconds"), filter1EG.attackTimeSeconds);
	xml->setAttribute(String("flt1EgDecayTimeSeconds"), filter1EG.decayTimeSeconds);
	xml->setAttribute(String("flt1EgSustainLevel"), filter1EG.sustainLevel);
	xml->setAttribute(String("flt1EgReleaseTimeSeconds"), filter1EG.releaseTimeSeconds);

	xml->setAttribute(String("flt2Cutoff"), filter2.cutoff);
	xml->setAttribute(String("flt2dBperOctave"), filter2.dBperOctave);
	xml->setAttribute(String("flt2EnvAmount"), filter2.envAmount);
	xml->setAttribute(String("flt2EgAttackTimeSeconds"), filter2EG.attackTimeSeconds);
	xml->setAttribute(String("flt2EgDecayTimeSeconds"), filter2EG.decayTimeSeconds);
	xml->setAttribute(String("flt2EgSustainLevel"), filter2EG.sustainLevel);
	xml->setAttribute(String("flt2EgReleaseTimeSeconds"), filter2EG.releaseTimeSeconds);

	xml->setAttribute(String("pitchLfoWaveform"), SynthOscillatorBase::WaveformName(pitchLFO.waveform));
	xml->setAttribute(String("pitchLfoFreqHz"), pitchLFO.freqHz);
	xml->setAttribute(String("pitchLfoAmount"), pitchLFO.amount);

	xml->setAttribute(String("filterLfoWaveform"), SynthOscillatorBase::WaveformName(filterLFO.waveform));
	xml->setAttribute(String("filterLfoFreqHz"), filterLFO.freqHz);
	xml->setAttribute(String("filterLfoAmount"), filterLFO.amount);

	return xml;
}

void SynthParameters::putXml(XmlElement* xml)
{
	xml->getStringAttribute("name").copyToUTF8(programName, sizeof(programName));

	main.masterLevel = xml->getDoubleAttribute("masterLevel");
	main.oscBlend = xml->getDoubleAttribute("oscBlend");
	main.pitchBendUpSemitones = xml->getIntAttribute("pitchBendUpSemitones");
	main.pitchBendDownSemitones = xml->getIntAttribute("pitchBendDownSemitones");

	osc1.waveform = SynthOscillatorBase::WaveformEnumFromName(xml->getStringAttribute("osc1Waveform"));
	osc2.pitchOffsetSemitones = xml->getIntAttribute("osc1PitchOffsetSemitones");
	osc1.detuneOffsetCents = xml->getDoubleAttribute("osc1DetuneOffsetCents");

	osc2.waveform = SynthOscillatorBase::WaveformEnumFromName(xml->getStringAttribute("osc2Waveform"));
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

	pitchLFO.waveform = SynthOscillatorBase::WaveformEnumFromName(xml->getStringAttribute("pitchLfoWaveform"));
	pitchLFO.freqHz = xml->getIntAttribute("pitchLfoFreqHz");
	pitchLFO.amount = xml->getDoubleAttribute("pitchLfoAmount");

	filterLFO.waveform = SynthOscillatorBase::WaveformEnumFromName(xml->getStringAttribute("filterLfoWaveform"));
	filterLFO.freqHz = xml->getIntAttribute("filterLfoFreqHz");
	filterLFO.amount = xml->getDoubleAttribute("filterLfoAmount");
}
