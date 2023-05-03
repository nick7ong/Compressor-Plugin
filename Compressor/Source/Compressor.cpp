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
    forwardValue = 0.f;
    delayValue = 0.f;
}
Compressor::~Compressor() {}

void Compressor::updateParameters(double sampleRate, float newAttackTime, float newReleaseTime, float newThreshold,
                                  float newRatio, float newMakeupGain)
{
    this->sampleRate = sampleRate;
    attackTime = newAttackTime;
    releaseTime = newReleaseTime;
    threshold = newThreshold;
    ratio = newRatio;
    makeupGain = newMakeupGain;
}

void Compressor::ResetValues() 
{
    forwardValue = 0.f;
    delayValue = 0.f;
}

float Compressor::EnvelopeDetector(float inSample, int numChannels)
{
    // Rectify the input signal
    float rectifiedSample = std::abs(inSample);

    // RC Simulator
    // Compute coefficients of filter with on attack and release time
    float Tc = log(0.368);
    float a0 = Tc / (exp(sampleRate * attackTime * 0.001));
    float b1 = Tc / (exp(sampleRate * releaseTime * 0.001));

    // Calculate the forward value and update the delay value
    forwardValue = a0 * (pow(rectifiedSample, 2) + b1 * delayValue);
    delayValue = pow(rectifiedSample, 2) + forwardValue;

    // Calculate the RC value
    float rcValue = sqrt(delayValue);

    // Update the envelope value with the largest RC value from both channels
    if (numChannels == 2) {
        rcValue = std::max(rcValue, sqrt(forwardValue));
    }

    return 20 * log10(rcValue);
}

void Compressor::GainComputer(float envelopeValue)
{
    float dBOut = 0.0;
    
    //Below Knee/Threshold
    if (envelopeValue < threshold)
        dBOut = envelopeValue;
    //Above Knee/Threshold
    if (envelopeValue > threshold)
        dBOut = threshold + (envelopeValue - threshold / ratio);

    // Convert to lin()
    gain = pow(10.0, (dBOut - envelopeValue) / 20.0);
}

void Compressor::ProcessBuffer(juce::AudioBuffer<float>& inBuffer)
{
    int numChannels = inBuffer.getNumChannels();
    int numSamples = inBuffer.getNumSamples();

    for (int channel = 0; channel < numChannels; channel++) {
        auto* channelData = inBuffer.getWritePointer(channel);
        for (int sample = 0; sample < numSamples; sample++) {
            float envelopeValue = EnvelopeDetector(channelData[sample], numChannels);
            GainComputer(envelopeValue);
            channelData[sample] *= gain * (1.f + makeupGain);
        }
    }
}