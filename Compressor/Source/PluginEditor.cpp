//==============================================================================
// Color Palette
#define WHITE 241, 242, 246
#define LIGHTRED 245, 126, 105
#define RED 255, 99, 72
#define BACKGROUND 225, 224, 214
//==============================================================================

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorAudioProcessorEditor::CompressorAudioProcessorEditor (CompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (250, 350);

    // Make GUI components visible
    addAndMakeVisible(attackTimeKnob);
    addAndMakeVisible(releaseTimeKnob);
    addAndMakeVisible(thresholdKnob);
    addAndMakeVisible(ratioKnob);
    addAndMakeVisible(makeupGainSlider);

    addAndMakeVisible(attackTimeLabel);
    addAndMakeVisible(releaseTimeLabel);
    addAndMakeVisible(thresholdLabel);
    addAndMakeVisible(ratioLabel);
    addAndMakeVisible(makeupGainLabel);

    //==============================================================================
    // Configure GUI components
    attackTimeKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackTimeKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromRGB(RED));
    attackTimeKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour::fromRGB(LIGHTRED));
    attackTimeKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour::fromRGB(WHITE));
    attackTimeKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    attackTimeKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colour::fromRGB(RED));
    attackTimeKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colour::fromRGB(LIGHTRED));

    releaseTimeKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseTimeKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromRGB(RED));
    releaseTimeKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour::fromRGB(LIGHTRED));
    releaseTimeKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour::fromRGB(WHITE));
    releaseTimeKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 70, 20);
    releaseTimeKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colour::fromRGB(RED));
    releaseTimeKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colour::fromRGB(LIGHTRED));

    thresholdKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    thresholdKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromRGB(RED));
    thresholdKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour::fromRGB(WHITE));
    thresholdKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour::fromRGB(LIGHTRED));
    thresholdKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    thresholdKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colour::fromRGB(RED));
    thresholdKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colour::fromRGB(LIGHTRED));

    ratioKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromRGB(RED));
    ratioKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour::fromRGB(LIGHTRED));
    ratioKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour::fromRGB(WHITE));
    ratioKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    ratioKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colour::fromRGB(RED));
    ratioKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colour::fromRGB(LIGHTRED));

    makeupGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    makeupGainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromRGB(RED));
    makeupGainSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colour::fromRGB(WHITE));
    makeupGainSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colour::fromRGB(LIGHTRED));
    makeupGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight, false, 50, 20);
    makeupGainSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colour::fromRGB(RED));
    makeupGainSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colour::fromRGB(LIGHTRED));

    //==============================================================================
    // Add unit suffixes
    attackTimeKnob.setTextValueSuffix(" ms");
    releaseTimeKnob.setTextValueSuffix(" ms");
    thresholdKnob.setTextValueSuffix(" dB");
    ratioKnob.setTextValueSuffix(":1");
    makeupGainSlider.setTextValueSuffix(" dB");

    //==============================================================================
    // Display only 1 decimal place
    attackTimeKnob.setNumDecimalPlacesToDisplay(1);
    releaseTimeKnob.setNumDecimalPlacesToDisplay(1);
    thresholdKnob.setNumDecimalPlacesToDisplay(1);
    ratioKnob.setNumDecimalPlacesToDisplay(1);
    makeupGainSlider.setNumDecimalPlacesToDisplay(1);

    //==============================================================================
    //Label Components
    attackTimeLabel.setText("Attack", juce::dontSendNotification);
    attackTimeLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(RED));
    releaseTimeLabel.setText("Release", juce::dontSendNotification);
    releaseTimeLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(RED));
    thresholdLabel.setText("Threshold", juce::dontSendNotification);
    thresholdLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(RED));
    ratioLabel.setText("Ratio", juce::dontSendNotification);
    ratioLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(RED));
    makeupGainLabel.setText("Makeup Gain", juce::dontSendNotification);
    makeupGainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(RED));

    //==============================================================================
    // Set and link parameters pluginProcessor to GUI Objects with parameterTree
    auto parameterTree = audioProcessor.getParameters();
    attackTimeParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(0);
    releaseTimeParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(1);
    thresholdParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(2);
    ratioParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(3);
    makeupGainParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(4);

    //==============================================================================
    // set parameter ranges
    attackTimeKnob.setRange(attackTimeParameter->range.start, attackTimeParameter->range.end, attackTimeParameter->range.interval);
    releaseTimeKnob.setRange(releaseTimeParameter->range.start, releaseTimeParameter->range.end, releaseTimeParameter->range.interval);
    thresholdKnob.setRange(thresholdParameter->range.start, thresholdParameter->range.end, thresholdParameter->range.interval);
    ratioKnob.setRange(ratioParameter->range.start, ratioParameter->range.end, ratioParameter->range.interval);
    makeupGainSlider.setRange(makeupGainParameter->range.start, makeupGainParameter->range.end, makeupGainParameter->range.interval);
    attackTimeKnob.setValue(1.0, juce::NotificationType::dontSendNotification);
    releaseTimeKnob.setValue(10.0, juce::NotificationType::dontSendNotification);
    thresholdKnob.setValue(0.0, juce::NotificationType::dontSendNotification);
    ratioKnob.setValue(1.0, juce::NotificationType::dontSendNotification);
    makeupGainSlider.setValue(0.0, juce::NotificationType::dontSendNotification);

    //==============================================================================
    // onValueChange reassign parameter value to slider value
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
    makeupGainSlider.onValueChange = [this] {
        *makeupGainParameter = makeupGainSlider.getValue();
    };

}

CompressorAudioProcessorEditor::~CompressorAudioProcessorEditor()
{
}

//==============================================================================
void CompressorAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colour::fromRGB(BACKGROUND));
}

void CompressorAudioProcessorEditor::resized()
{
    int x = getWidth() / 10;
    int y = getHeight() / 10;

    //==============================================================================
    // Set bounds
    attackTimeKnob.setBounds(0.2 * x, 0.2 * y, 4.8 * x, 4 * y);
    releaseTimeKnob.setBounds(5 * x, 0.2 * y, 4.8 * x, 4 * y);
    thresholdKnob.setBounds(0.2 * x, 4.3 * y, 4.8 * x, 4 * y);
    ratioKnob.setBounds(5 * x, 4.3 * y, 4.8 * x, 4 * y);
    makeupGainSlider.setBounds(1.5 * x, 8.4 * y, 7 * x, 1.3 * y);

    attackTimeLabel.setBounds(1.7 * x, 1.5 * y, 2.8 * x, 0.6 * y);
    releaseTimeLabel.setBounds(6.3 * x, 1.5 * y, 2.8 * x, 0.6 * y);
    thresholdLabel.setBounds(1.2 * x, 5.6 * y, 2.8 * x, 0.6 * y);
    ratioLabel.setBounds(6.6 * x, 5.6 * y, 2.8 * x, 0.6 * y);
    makeupGainLabel.setBounds(2.4 * x, 9.2 * y, 4 * x, 0.6 * y);

}
