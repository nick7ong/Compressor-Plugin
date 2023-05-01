/*
  ==============================================================================

    Compressor.cpp
    Created: 1 May 2023 2:43:52pm
    Author:  Nicholas Tong

  ==============================================================================
*/

#include "Compressor.h"

Compressor::Compressor(double sampleRate, float attackTime, float releaseTime,
                       float threshold, float ratio, float makeupGain)
{
    this->sampleRate = sampleRate;
    this->attackTime = attackTime;
    this->releaseTime = releaseTime;
    this->threshold = threshold;
    this->ratio = ratio;
    this->makeupGain = makeupGain;

    this->bufferSize = 480;
    gain.resize(bufferSize);
    std::fill(gain.begin(), gain.end(), 0.0);
}
Compressor::~Compressor() {}

void Compressor::updateParameters(float newAttackTime, float newReleaseTime, float newThreshold,
                                  float newRatio, float newMakeupGain)
{
    attackTime = newAttackTime;
    releaseTime = newReleaseTime;
    threshold = newThreshold;
    ratio = newRatio;
    makeupGain = newMakeupGain;
}

std::vector<float> Compressor::EnvelopeDetector(juce::AudioBuffer<float>& inBuffer)
{
    std::vector<float> envelopeValues(inBuffer.getNumSamples());

    // Rectify the input signal
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++) 
    {
        for (int sample = 0; sample < inBuffer.getNumSamples(); sample++) 
        {
            inBuffer.setSample(channel, sample, std::abs(inBuffer.getSample(channel, sample)));
        }
    }

    // RC Simulator
    // Compute coefficients of filter with on attack and release time
    float Tc = log(0.368);
    float a0 = Tc / (exp(sampleRate * attackTime * 0.001));
    float b1 = Tc / (exp(sampleRate * releaseTime * 0.001));
    std::vector<float> rcBuffer(inBuffer.getNumSamples(), 0.0);
    float forwardValue = 0.0;
    float delayValue = 0.0;

    for (int sample = 0; sample < inBuffer.getNumSamples(); sample++) 
    {
        forwardValue = a0 * (pow(inBuffer.getSample(0, sample), 2) + b1 * delayValue);
        rcBuffer[sample] = pow(inBuffer.getSample(0, sample), 2) + forwardValue;
        delayValue = rcBuffer[sample];
    }

    // log dB Conversion
    for (int sample = 0; sample < inBuffer.getNumSamples(); ++sample) {
        envelopeValues[sample] = 20 * log10(sqrt(rcBuffer[sample]));
    }

    return envelopeValues;
}
void Compressor::GainComputer(std::vector<float> envelopeValues)
{
    std::vector<float> dBOut(envelopeValues.size(), 0.0);

    for (int val = 0; val < envelopeValues.size(); val++) {
        //Below Knee/Threshold
        if (envelopeValues[val] < threshold)
            dBOut[val] = envelopeValues[val];
        //Above Knee/Threshold
        if (envelopeValues[val] > threshold)
            dBOut[val] = threshold + (envelopeValues[val] - threshold / ratio);
    }

    // Convert to lin()
    for (int n = 0; n < gain.size(); ++n) {
        gain[n] = pow(10.0, (dBOut[n] - envelopeValues[n]) / 20.0);
    }
}
void Compressor::ProcessBuffer(juce::AudioBuffer<float>& inBuffer)
{
    std::vector<float> envelopeValues = EnvelopeDetector(inBuffer);
    GainComputer(envelopeValues);

    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++) {
        auto* channelData = inBuffer.getWritePointer(channel);
        for (int sample = 0; sample < inBuffer.getNumSamples(); sample++) {
            channelData[sample] *= gain[sample] * makeupGain;
        }
    }
}