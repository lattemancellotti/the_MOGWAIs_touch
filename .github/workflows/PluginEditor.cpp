#include "PluginProcessor.h"
#include "PluginEditor.h"

TheMogwaisTouchAudioProcessorEditor::TheMogwaisTouchAudioProcessorEditor (TheMogwaisTouchAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Dimensione della finestra del plugin (Larghezza x Altezza in pixel)
    setSize (450, 280);

    // Stile dei controlli (Manopole rotanti)
    auto setupSlider = [this](juce::Slider& slider, juce::Label& label, const juce::String& text) {
        slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
        slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0xffd4af37)); // Oro Mogwai
        slider.setColour(juce::Slider::thumbColourId, juce::Colours::white);
        addAndMakeVisible(slider);

        label.setText(text, juce::dontSendNotification);
        label.setJustificationType(juce::Justification::centred);
        label.setColour(juce::Label::textColourId, juce::Colour(0xffd4af37));
        addAndMakeVisible(label);
    };

    setupSlider(decaySlider, decayLabel, "DECAY");
    setupSlider(dryMixSlider, dryMixLabel, "DRY MIX");
    setupSlider(reverbMixSlider, reverbMixLabel, "REVERB MIX");

    // Collegamento ai parametri del DSP
    decayAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "decay", decaySlider);
    dryMixAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "dryMix", dryMixSlider);
    reverbMixAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "reverbMix", reverbMixSlider);
}

TheMogwaisTouchAudioProcessorEditor::~TheMogwaisTouchAudioProcessorEditor() {}

void TheMogwaisTouchAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Sfondo dark metallico
    g.fillAll (juce::Colour (0xff1c1c24));

    // Bordo dorato esterno
    g.setColour (juce::Colour (0xffd4af37));
    g.drawRect (getLocalBounds(), 3.0f);

    // Titolo principale
    g.setFont (juce::FontOptions (20.0f, juce::Font::bold));
    g.drawText ("THE MOGWAI'S TOUCH", 0, 15, getWidth(), 30, juce::Justification::centred);

    // Sottotitolo
    g.setFont (juce::FontOptions (10.0f, juce::Font::italic));
    g.setColour (juce::Colours::lightgrey);
    g.drawText ("Atmospheric Stereo Reverb Processor", 0, 40, getWidth(), 20, juce::Justification::centred);
}

void TheMogwaisTouchAudioProcessorEditor::resized()
{
    // Posizionamento delle manopole in riga
    int yPos = 80;
    int sliderWidth = 120;
    int sliderHeight = 120;
    int spacing = 20;

    decaySlider.setBounds(30, yPos, sliderWidth, sliderHeight);
    decayLabel.setBounds(30, yPos + sliderHeight, sliderWidth, 20);

    dryMixSlider.setBounds(30 + sliderWidth + spacing, yPos, sliderWidth, sliderHeight);
    dryMixLabel.setBounds(30 + sliderWidth + spacing, yPos + sliderHeight, sliderWidth, 20);

    reverbMixSlider.setBounds(30 + (sliderWidth + spacing) * 2, yPos, sliderWidth, sliderHeight);
    reverbMixLabel.setBounds(30 + (sliderWidth + spacing) * 2, yPos + sliderHeight, sliderWidth, 20);
}
