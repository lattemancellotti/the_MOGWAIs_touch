#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class TheMogwaisTouchAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TheMogwaisTouchAudioProcessorEditor (TheMogwaisTouchAudioProcessor&);
    ~TheMogwaisTouchAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    TheMogwaisTouchAudioProcessor& audioProcessor;

    // Manopole dell'interfaccia
    juce::Slider decaySlider;
    juce::Slider dryMixSlider;
    juce::Slider reverbMixSlider;

    // Etichette dei controlli
    juce::Label decayLabel;
    juce::Label dryMixLabel;
    juce::Label reverbMixLabel;

    // Connessione tra manopole e motore DSP
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> dryMixAttachment;
    std::unique_ptr<SliderAttachment> reverbMixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheMogwaisTouchAudioProcessorEditor)
};
