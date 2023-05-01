/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorAudioProcessorEditor::CompressorAudioProcessorEditor (CompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    // Make GUI components visible
    addAndMakeVisible(attackTimeKnob);
    addAndMakeVisible(releaseTimeKnob);
    addAndMakeVisible(thresholdKnob);
    addAndMakeVisible(ratioKnob);
    addAndMakeVisible(makeupGainKnob);

    // Configure GUI components

    // Set and link parameters pluginProcessor to GUI Objects with parameterTree
    auto parameterTree = audioProcessor.getParameters();
    attackTimeParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(0);
    releaseTimeParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(1);
    thresholdParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(2);
    ratioParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(3);
    makeupGainParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(4);

    // set range
    attackTimeKnob.setRange(attackTimeParameter->range.start, attackTimeParameter->range.end, attackTimeParameter->range.interval);
    releaseTimeKnob.setRange(releaseTimeParameter->range.start, releaseTimeParameter->range.end, releaseTimeParameter->range.interval);
    thresholdKnob.setRange(thresholdParameter->range.start, thresholdParameter->range.end, thresholdParameter->range.interval);
    ratioKnob.setRange(ratioParameter->range.start, ratioParameter->range.end, ratioParameter->range.interval);
    makeupGainKnob.setRange(makeupGainParameter->range.start, makeupGainParameter->range.end, makeupGainParameter->range.interval);
    attackTimeKnob.setValue(1.0, juce::NotificationType::dontSendNotification);
    releaseTimeKnob.setValue(10.0, juce::NotificationType::dontSendNotification);
    thresholdKnob.setValue(0.0, juce::NotificationType::dontSendNotification);
    ratioKnob.setValue(1.0, juce::NotificationType::dontSendNotification);
    makeupGainKnob.setValue(0.0, juce::NotificationType::dontSendNotification);

    // reassign parameter value to slider value
    attackTimeKnob.onValueChange = [this] {
        *attackTimeParameter = attackTimeKnob.getValue();
    };
    releaseTimeKnob.onValueChange = [this] {
        *releaseTimeParameter = releaseTimeKnob.getValue();
    };
    thresholdKnob.onValueChange = [this] {
        *thresholdParameter = thresholdKnob.getValue();
    };
    ratioKnob.onValueChange = [this] {
        *ratioParameter = ratioKnob.getValue();
    };
    makeupGainKnob.onValueChange = [this] {
        *makeupGainParameter = makeupGainKnob.getValue();
    };

}

CompressorAudioProcessorEditor::~CompressorAudioProcessorEditor()
{
}

//==============================================================================
void CompressorAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void CompressorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
