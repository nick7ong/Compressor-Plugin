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
    attackTimeKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackTimeKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromRGB(255, 99, 72));
    attackTimeKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour::fromRGB(245, 126, 105));
    attackTimeKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour::fromRGB(241, 242, 246));
    attackTimeKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    attackTimeKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colour::fromRGB(255, 99, 72));
    attackTimeKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colour::fromRGB(245, 126, 105));


    releaseTimeKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseTimeKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromRGB(255, 99, 72));
    releaseTimeKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour::fromRGB(245, 126, 105));
    releaseTimeKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour::fromRGB(241, 242, 246));
    releaseTimeKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    releaseTimeKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colour::fromRGB(255, 99, 72));
    releaseTimeKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colour::fromRGB(245, 126, 105));

    thresholdKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    thresholdKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromRGB(255, 99, 72));
    thresholdKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour::fromRGB(245, 126, 105));
    thresholdKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour::fromRGB(241, 242, 246));
    thresholdKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    thresholdKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colour::fromRGB(255, 99, 72));
    thresholdKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colour::fromRGB(245, 126, 105));

    ratioKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromRGB(255, 99, 72));
    ratioKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour::fromRGB(245, 126, 105));
    ratioKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour::fromRGB(241, 242, 246));
    ratioKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    ratioKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colour::fromRGB(255, 99, 72));
    ratioKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colour::fromRGB(245, 126, 105));

    makeupGainKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    makeupGainKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromRGB(255, 99, 72));
    makeupGainKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colour::fromRGB(245, 126, 105));
    makeupGainKnob.setColour(juce::Slider::ColourIds::trackColourId, juce::Colour::fromRGB(241, 242, 246));
    makeupGainKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    makeupGainKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colour::fromRGB(255, 99, 72));
    makeupGainKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colour::fromRGB(245, 126, 105));

    //Label Components
    attackTimeLabel.setText("Attack", juce::dontSendNotification);
    attackTimeLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(255, 99, 72));

    releaseTimeLabel.setText("Release", juce::dontSendNotification);
    releaseTimeLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(255, 99, 72));

    thresholdLabel.setText("Threshold", juce::dontSendNotification);
    thresholdLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(255, 99, 72));
    
    ratioLabel.setText("Ratio", juce::dontSendNotification);
    ratioLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(255, 99, 72));
    
    makeupGainLabel.setText("Makeup Gain", juce::dontSendNotification);
    makeupGainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(255, 99, 72));


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
    g.fillAll(juce::Colour::fromRGB(225, 224, 214));
}

void CompressorAudioProcessorEditor::resized()
{
    attackTimeKnob.setBounds(-20, 40, 200, 100);
    releaseTimeKnob.setBounds(140, 40, 280, 140);
    thresholdKnob.setBounds(140, 40, 280, 140);
    ratioKnob.setBounds(140, 40, 280, 140);
    makeupGainKnob.setBounds(140, 40, 140, 140);

    attackTimeLabel.setBounds(85, 20, 100, 20);
    releaseTimeLabel.setBounds(258, 20, 100, 20);
    thresholdLabel.setBounds(258, 20, 100, 20);
    ratioLabel.setBounds(258, 20, 100, 20);
    makeupGainLabel.setBounds(258, 20, 100, 20);
}
