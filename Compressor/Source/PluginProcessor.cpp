/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorAudioProcessor::CompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    compressor(getSampleRate(), 1.f, 10.f, 0.f, 1.f, 0.f) // Initialize Compressor with default parameters
#endif
{
    attackTimeParameter = new juce::AudioParameterFloat(juce::ParameterID("1", 1), "Attack Time Knob", 1.f, 100.f, 0.1f);
    releaseTimeParameter = new juce::AudioParameterFloat(juce::ParameterID("2", 2), "Release Time Knob", 10.f, 1000.f, 10.f);
    thresholdParameter = new juce::AudioParameterFloat(juce::ParameterID("3", 3), "Threshold Knob", -60.f, 0.f, 1.f);
    ratioParameter = new juce::AudioParameterFloat(juce::ParameterID("4", 4), "Ratio Knob", 1.f, 20.f, 0.1f);
    makeupGainParameter = new juce::AudioParameterFloat(juce::ParameterID("5", 5), "Makeup Gain Knob", 0.f, 20.f, 0.1f);

    addParameter(attackTimeParameter);
    addParameter(releaseTimeParameter);
    addParameter(thresholdParameter);
    addParameter(ratioParameter);
    addParameter(makeupGainParameter);

    double fs = 48000;
    compressor.updateParameters(fs, *attackTimeParameter, *releaseTimeParameter, *thresholdParameter, 
                                *ratioParameter, *makeupGainParameter);
    currentAttackTime = *attackTimeParameter;
    currentReleaseTime = *releaseTimeParameter;
    currentThreshold = *thresholdParameter;
    currentRatio = *ratioParameter;
    currentGain = *makeupGainParameter;

}

CompressorAudioProcessor::~CompressorAudioProcessor()
{
}

//==============================================================================
const juce::String CompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CompressorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void CompressorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

}

void CompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CompressorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    if (*attackTimeParameter != currentAttackTime || *releaseTimeParameter != currentReleaseTime || 
        *thresholdParameter != currentThreshold || *ratioParameter != currentRatio || *makeupGainParameter != currentGain) {
        compressor.updateParameters(getSampleRate(), *attackTimeParameter, *releaseTimeParameter, *thresholdParameter,
            *ratioParameter, *makeupGainParameter);
        currentAttackTime = *attackTimeParameter;
        currentReleaseTime = *releaseTimeParameter;
        currentThreshold = *thresholdParameter;
        currentRatio = *ratioParameter;
        currentGain = *makeupGainParameter;
    }

    compressor.ProcessBuffer(buffer);
}

//==============================================================================
bool CompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CompressorAudioProcessor::createEditor()
{
    return new CompressorAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void CompressorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CompressorAudioProcessor();
}
