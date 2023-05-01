/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class CompressorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    CompressorAudioProcessorEditor (CompressorAudioProcessor&);
    ~CompressorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CompressorAudioProcessor& audioProcessor;

    juce::Slider attackTimeKnob;
    juce::Label attackTimeLabel;
    juce::Slider releaseTimeKnob;
    juce::Label releaseTimeLabel;
    juce::Slider thresholdKnob;
    juce::Label thresholdLabel;
    juce::Slider ratioKnob;
    juce::Label ratioLabel;
    juce::Slider makeupGainKnob;
    juce::Label makeupGainLabel;

    juce::AudioParameterFloat* attackTimeParameter;
    juce::AudioParameterFloat* releaseTimeParameter;
    juce::AudioParameterFloat* thresholdParameter;
    juce::AudioParameterFloat* ratioParameter;
    juce::AudioParameterFloat* makeupGainParameter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorAudioProcessorEditor)
};
