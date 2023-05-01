/*
  ==============================================================================

    Compressor.h
    Created: 1 May 2023 2:43:52pm
    Author:  nnjto

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

    void updateParameters(float newAttackTime, float newReleaseTime, float newThreshold,
                          float newRatio, float newMakeupGain);
    std::vector<float> EnvelopeDetector(juce::AudioBuffer<float>&);
    void GainComputer(std::vector<float>);
    void ProcessBuffer(juce::AudioBuffer<float>&);

private:
    double sampleRate;
    int bufferSize;

    // Envelope Detector Variables
    float attackTime, releaseTime;

    // Gain Computer Variables
    float threshold, ratio;

    // DCAand Gain
    std::vector<float> gain;
    float makeupGain;

};