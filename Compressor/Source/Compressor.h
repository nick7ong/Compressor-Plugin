/*
  ==============================================================================

    Compressor.h
    Created: 1 May 2023 2:43:52pm
    Author:  Nicholas Tong

  ==============================================================================
*/

#pragma once

#include <vector>
#include "JuceHeader.h"

class Compressor {
public:
    Compressor(double sampleRate, float attackTime, float releaseTime,
               float threshold, float ratio, float makeupGain);
    ~Compressor();

    void updateParameters(double sampleRate, float newAttackTime, float newReleaseTime, float newThreshold,
                          float newRatio, float newMakeupGain);
    float EnvelopeDetector(float inSample, int numChannels);
    void GainComputer(float gainValue);
    void ProcessBuffer(juce::AudioBuffer<float>&);
    void ResetValues();

private:
    double sampleRate;

    // Envelope Detector Variables
    float attackTime, releaseTime, forwardValue, delayValue;

    // Gain Computer Variables
    float threshold, ratio;

    // DCAand Gain
    float gain;
    float makeupGain;

};