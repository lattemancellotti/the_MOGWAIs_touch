#include "PluginProcessor.h"
#include "PluginEditor.h"

TheMogwaisTouchAudioProcessor::TheMogwaisTouchAudioProcessor()
    : AudioProcessor (BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                                       .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "Parameters", createParameters())
{
}

TheMogwaisTouchAudioProcessor::~TheMogwaisTouchAudioProcessor() {}

juce::AudioProcessorValueTreeState::ParameterLayout TheMogwaisTouchAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    params.push_back(std::make_unique<juce::AudioParameterFloat>("decay", "Decay", 0.1f, 0.95f, 0.7f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("dryMix", "Dry Mix", 0.0f, 1.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("reverbMix", "Reverb Mix", 0.0f, 1.0f, 0.5f));
    return { params.begin(), params.end() };
}

void TheMogwaisTouchAudioProcessor::prepareToPlay (double, int) {}
void TheMogwaisTouchAudioProcessor::releaseResources() {}

void TheMogwaisTouchAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    
    auto dryMix = apvts.getRawParameterValue("dryMix")->load();
    auto reverbMix = apvts.getRawParameterValue("reverbMix")->load();

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            float in = channelData[sample];
            channelData[sample] = in * dryMix + (in * 0.5f) * reverbMix;
        }
    }
}

juce::AudioProcessorEditor* TheMogwaisTouchAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor (*this);
}

void TheMogwaisTouchAudioProcessor::getStateInformation (juce::MemoryBlock&) {}
void TheMogwaisTouchAudioProcessor::setStateInformation (const void*, int) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TheMogwaisTouchAudioProcessor();
}
