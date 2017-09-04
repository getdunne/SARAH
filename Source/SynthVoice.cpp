#include "SynthVoice.h"
#include <cmath>

void SynthVoice::setPitchBend(int pitchWheelPos)
{
    if (pitchWheelPos > 8192)
    {
        // shifting up
        pitchBend = float(pitchWheelPos - 8192) / (16383 - 8192);
    }
    else
    {
        // shifting down
        pitchBend = float(8192 - pitchWheelPos) / -8192;    // negative number
    }
}

float SynthVoice::pitchBendCents()
{
    if (pitchBend >= 0.0f)
    {
        // shifting up
        return pitchBend * pParams->main.pitchBendUpSemitones * 100;
    }
    else
    {
        // shifting down
        return pitchBend * pParams->main.pitchBendDownSemitones * 100;
    }
}

SynthVoice::SynthVoice()
    : SynthesiserVoice()
    , pParams(0)
    , noteVelocity(0.0f)
    , pitchBend(0.0f)
    , osc1Level(0.0f)
    , osc2Level(0.0f)
    , tailOff(false)
{
}

// Set up voice according to current sound parameters and pitch bend
void SynthVoice::setup (bool pitchBendOnly)
{
    // Always set oscillator waveforms, to ensure they get initialized first time
    osc1.setWaveform(pParams->osc1.waveform);
    osc2.setWaveform(pParams->osc2.waveform);
    pitchLFO.setWaveform(pParams->pitchLFO.waveform);
    filterLFO.setWaveform(pParams->filterLFO.waveform);

    if (!pitchBendOnly)
    {
        osc1.setFilterParams(0.1f * float(pParams->filter1.cutoff), float(pParams->filter1.dBperOctave));
        osc2.setFilterParams(0.1f * float(pParams->filter2.cutoff), float(pParams->filter2.dBperOctave));
    }

    float masterLevel = float(noteVelocity * pParams->main.masterLevel);
    double sampleRateHz = getSampleRate();
    int midiNote = getCurrentlyPlayingNote();
    double pbCents = pitchBendCents();

    osc1.setFrequency(sampleRateHz, midiNote + pParams->osc1.pitchOffsetSemitones,
        pParams->osc1.detuneOffsetCents + pbCents);
    if (!pitchBendOnly)
    {
        osc1Level.reset(sampleRateHz, ampEG.isRunning() ? 0.1 : 0.0);
        osc1Level.setValue(float(pParams->main.oscBlend * masterLevel));
    }

    osc2.setFrequency(sampleRateHz, midiNote + pParams->osc2.pitchOffsetSemitones,
        pParams->osc2.detuneOffsetCents + pbCents);
    if (!pitchBendOnly)
    {
        osc2Level.reset(sampleRateHz, ampEG.isRunning() ? 0.1 : 0.0);
        osc2Level.setValue(float((1.0 - pParams->main.oscBlend) * masterLevel));
    }

    if (!pitchBendOnly)
    {
        pitchLFO.setFrequency(float(pParams->pitchLFO.freqHz / sampleRateHz));
        filterLFO.setFrequency(float(pParams->filterLFO.freqHz / sampleRateHz));

        ampEG.attackSeconds = pParams->ampEG.attackTimeSeconds;
        ampEG.decaySeconds = pParams->ampEG.decayTimeSeconds;
        ampEG.sustainLevel = pParams->ampEG.sustainLevel;
        ampEG.releaseSeconds = pParams->ampEG.releaseTimeSeconds;

        flt1EG.attackSeconds = pParams->filter1EG.attackTimeSeconds;
        flt1EG.decaySeconds = pParams->filter1EG.decayTimeSeconds;
        flt1EG.sustainLevel = pParams->filter1EG.sustainLevel;
        flt1EG.releaseSeconds = pParams->filter1EG.releaseTimeSeconds;

        flt2EG.attackSeconds = pParams->filter2EG.attackTimeSeconds;
        flt2EG.decaySeconds = pParams->filter2EG.decayTimeSeconds;
        flt2EG.sustainLevel = pParams->filter2EG.sustainLevel;
        flt2EG.releaseSeconds = pParams->filter2EG.releaseTimeSeconds;

        pitch1EG.attackSeconds = pParams->pitch1EG.attackTimeSeconds;
        pitch1EG.decaySeconds = 0.0;
        pitch1EG.sustainLevel = 1.0;
        pitch1EG.releaseSeconds = pParams->pitch1EG.releaseTimeSeconds;

        pitch2EG.attackSeconds = pParams->pitch2EG.attackTimeSeconds;
        pitch2EG.decaySeconds = 0.0;
        pitch2EG.sustainLevel = 1.0;
        pitch2EG.releaseSeconds = pParams->pitch2EG.releaseTimeSeconds;
    }
}

void SynthVoice::pitchWobble(double cents1, double cents2)
{
    double sampleRateHz = getSampleRate();

    int midiNote = getCurrentlyPlayingNote();
    double pbCents = pitchBendCents();
    osc1.setFrequency(sampleRateHz, midiNote + pParams->osc1.pitchOffsetSemitones,
        pParams->osc1.detuneOffsetCents + pbCents + cents1);
    osc2.setFrequency(sampleRateHz, midiNote + pParams->osc2.pitchOffsetSemitones,
        pParams->osc2.detuneOffsetCents + pbCents + cents2);
}

void SynthVoice::soundParameterChanged()
{
    if (pParams == 0) return;
    setup(false);
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    ignoreUnused(midiNoteNumber);    // accessible as SynthesiserVoice::getCurrentlyPlayingNote();
    tailOff = false;
    noteVelocity = velocity;

    pParams = dynamic_cast<SynthSound*>(sound)->pParams;
    double sampleRateHz = getSampleRate();
    setPitchBend(currentPitchWheelPosition);

    setup(false);
    ampEG.start(sampleRateHz);
    flt1EG.start(sampleRateHz);
    flt2EG.start(sampleRateHz);
    pitch1EG.start(sampleRateHz);
    pitch2EG.start(sampleRateHz);

    noteSampleCounter = 0;
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    ignoreUnused(velocity);

    if (allowTailOff & !tailOff)
    {
        tailOff = true;
        ampEG.release();
        flt1EG.release();
        flt2EG.release();
        if (pitch1EG.releaseSeconds == 0.0) pitch1EG.stop(); else pitch1EG.release();
        if (pitch2EG.releaseSeconds == 0.0) pitch2EG.stop(); else pitch2EG.release();
    }
    else
    {
        clearCurrentNote();
    }
}

void SynthVoice::pitchWheelMoved(int newValue)
{
    setPitchBend(newValue);
    setup(true);
}

void SynthVoice::controllerMoved(int controllerNumber, int newValue)
{
    // nothing yet
    ignoreUnused(controllerNumber);
    ignoreUnused(newValue);
}

void SynthVoice::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    while (--numSamples >= 0)
    {
        if (!ampEG.isRunning())
        {
            clearCurrentNote();
            flt1EG.stop();
            flt2EG.stop();
            pitch1EG.stop();
            pitch2EG.stop();
            break;
        }

        float feg1 = flt1EG.getSample() * 0.1f * float(pParams->filter1.envAmount);
        float feg2 = flt2EG.getSample() * 0.1f * float(pParams->filter2.envAmount);
        float flfo = filterLFO.getSample() * 0.01f * float(pParams->filterLFO.amount);
        float peg1 = pitch1EG.getSample() * float(pParams->pitch1EG.sustainLevel) * 100;
        float peg2 = pitch2EG.getSample() * float(pParams->pitch2EG.sustainLevel) * 100;
        float plfo = pitchLFO.getSample() * float(pParams->pitchLFO.amount);
        if (--noteSampleCounter < 0)
        {
            pitchWobble(peg1 + plfo, peg2 + plfo);
            osc1.setFilterCutoffDelta(feg1 + flfo);
            osc2.setFilterCutoffDelta(feg2 + flfo);
            noteSampleCounter = 441;
        }

        float aeg = ampEG.getSample();
        float osc = osc1.getSample() * osc1Level.getNextValue() + osc2.getSample() * osc2Level.getNextValue();
        outputBuffer.addSample(0, startSample, osc * aeg);
        outputBuffer.addSample(1, startSample, osc * aeg);

        ++startSample;
    }
}
