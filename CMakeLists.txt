cmake_minimum_required(VERSION 3.22)
project(Chromesthesia VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Universal binary — arm64 (Apple Silicon native) + x86_64 (Rosetta)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "Build architectures" FORCE)

# JUCE 6.1.6 — already present at ../JUCE (sibling of project root)
add_subdirectory(../JUCE "${CMAKE_BINARY_DIR}/JUCE")

juce_add_plugin(Chromesthesia
    COMPANY_NAME                "Handsome Labs"
    PLUGIN_NAME                 "Chromesthesia"
    PLUGIN_DESCRIPTION          "Pitch-to-color synesthesia training"
    PLUGIN_MANUFACTURER_CODE    KrIs
    PLUGIN_CODE                 Chsz
    FORMATS                     VST3 AU
    IS_SYNTH                    TRUE
    NEEDS_MIDI_INPUT            TRUE
    NEEDS_MIDI_OUTPUT           FALSE
    IS_MIDI_EFFECT              FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD     FALSE
    VST3_CATEGORIES             "Instrument|Synth"
    AU_MAIN_TYPE                "kAudioUnitType_MusicDevice"
)

juce_generate_juce_header(Chromesthesia)

target_sources(Chromesthesia PRIVATE
    src/PluginProcessor.cpp
    src/PluginEditor.cpp
    src/ColorEngine.cpp
    src/FullscreenColorWindow.cpp
)

target_compile_definitions(Chromesthesia PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_DISPLAY_SPLASH_SCREEN=0
)

target_link_libraries(Chromesthesia
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

# Ad-hoc code signing — runs automatically after every build.
# Signs in the build output directory (no sudo needed).
# cp -r preserves the signature when installing to /Library.
set(_VST3 "${CMAKE_BINARY_DIR}/Chromesthesia_artefacts/$<CONFIG>/VST3/Chromesthesia.vst3")
set(_AU   "${CMAKE_BINARY_DIR}/Chromesthesia_artefacts/$<CONFIG>/AU/Chromesthesia.component")

add_custom_command(TARGET Chromesthesia_VST3 POST_BUILD
    COMMAND codesign --force --deep --sign - "${_VST3}"
    COMMENT "Signing Chromesthesia.vst3"
)

add_custom_command(TARGET Chromesthesia_AU POST_BUILD
    COMMAND codesign --force --deep --sign - "${_AU}"
    COMMENT "Signing Chromesthesia.component"
)
