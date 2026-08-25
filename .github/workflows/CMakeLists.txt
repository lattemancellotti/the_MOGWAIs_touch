cmake_minimum_required(VERSION 3.15)
project(TheMogwaisTouch VERSION 1.0.0)

add_subdirectory(JUCE)

juce_add_plugin(TheMogwaisTouch
    COMPANY_NAME "MogwaiAudio"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_MIDI_INPUT FALSE
    PLUGIN_MANUFACTURER_CODE Moga
    PLUGIN_CODE Mgt1
    FORMATS VST3 AU Standalone
    PRODUCT_NAME "The Mogwai's Touch"
)

target_sources(TheMogwaisTouch
    PRIVATE
        PluginProcessor.cpp
        PluginEditor.cpp
)

target_link_libraries(TheMogwaisTouch
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
