#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
class CompressorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    CompressorAudioProcessorEditor (CompressorAudioProcessor&);
    ~CompressorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    CompressorAudioProcessor& audioProcessor;

    // GUI Components
    juce::Slider attackTimeKnob;
    juce::Label attackTimeLabel;
    juce::Slider releaseTimeKnob;
    juce::Label releaseTimeLabel;
    juce::Slider thresholdKnob;
    juce::Label thresholdLabel;
    juce::Slider ratioKnob;
    juce::Label ratioLabel;
    juce::Slider makeupGainSlider;
    juce::Label makeupGainLabel;

    // Audio Parameters
    juce::AudioParameterFloat* attackTimeParameter;
    juce::AudioParameterFloat* releaseTimeParameter;
    juce::AudioParameterFloat* thresholdParameter;
    juce::AudioParameterFloat* ratioParameter;
    juce::AudioParameterFloat* makeupGainParameter;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorAudioProcessorEditor)
};
