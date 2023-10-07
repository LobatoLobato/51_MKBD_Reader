#pragma once
#include <stdint.h>

enum MidiMessageType {
    MIDI_NOTEOFF    = 0x8,
    MIDI_NOTEON     = 0x9,
    MIDI_CC         = 0xB,
    MIDI_PITCH_BEND = 0xE,
};

enum MidiCCFunctions {
    MIDI_CC_MOD_WHEEL       = 1,
    MIDI_CC_PORTAMENTO      = 65,
    MIDI_CC_PORTAMENTO_TIME = 5,
};

enum MidiChannels {
    MIDI_CH1  = 0,
    MIDI_CH2  = 1,
    MIDI_CH3  = 2,
    MIDI_CH4  = 3,
    MIDI_CH5  = 4,
    MIDI_CH6  = 5,
    MIDI_CH7  = 6,
    MIDI_CH8  = 7,
    MIDI_CH9  = 8,
    MIDI_CH10 = 9,
    MIDI_CH11 = 10,
    MIDI_CH12 = 11,
    MIDI_CH13 = 12,
    MIDI_CH14 = 13,
    MIDI_CH15 = 14,
    MIDI_CH16 = 15,
};

#define MIDI_PITCH_BEND_CENTER 0x2000

void midiInit(__bit turnAllNotesOff);
void sendMidi(uint8_t messageType, uint8_t channel, uint8_t byte1, uint8_t byte2);
