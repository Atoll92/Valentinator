cmake_minimum_required(VERSION 3.22)
project(Valentinator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build universal binary (arm64 + x86_64) for Rosetta compatibility
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")

# --- Fetch JUCE ---
include(FetchContent)
FetchContent_Declare(
    juce
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.12
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(juce)

# --- Plugin Target ---
juce_add_plugin(Valentinator
    COMPANY_NAME          "ValentinatorAudio"
    BUNDLE_ID             "com.valentinatoraudio.valentinator"
    PLUGIN_MANUFACTURER_CODE Vlnt
    PLUGIN_CODE           Valn
    FORMATS               VST3 AU Standalone
    PRODUCT_NAME          "Valentinator"
    PLUGIN_NAME           "Valentinator"
    DESCRIPTION           "Marine underwater audio effect processor"
    IS_SYNTH              FALSE
    NEEDS_MIDI_INPUT      FALSE
    NEEDS_MIDI_OUTPUT     FALSE
    IS_MIDI_EFFECT        FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
)

target_sources(Valentinator PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
    Source/DSP/UnderwaterChain.cpp
    Source/DSP/PitchWobble.cpp
    Source/DSP/ParameterLayout.cpp
    Source/GUI/MarineLookAndFeel.cpp
    Source/GUI/OceanBackground.cpp
)

target_include_directories(Valentinator PRIVATE Source)

# --- Binary Resources (background image) ---
juce_add_binary_data(ValentinatorBinaryData
    SOURCES
        Assets/background.png
)

target_compile_definitions(Valentinator PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_DISPLAY_SPLASH_SCREEN=0
)

target_link_libraries(Valentinator
    PRIVATE
        ValentinatorBinaryData
        juce::juce_audio_utils
        juce::juce_dsp
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
