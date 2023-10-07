#include <stdint.h>
#include <stdbool.h>

#include "8052.H"
#include "include/timer.h"
#include "include/midi.h"
#include "include/serial.h"
#include "include/defs.h"
#include "include/key.h"
#include "include/math.h"
#include "include/ADC080X.h"
#include "include/button.h"

#define NUM_KEYS         61u

#define SUSTAIN_PEDAL    BUTTONS_CH0
#define KEY_HOLD         BUTTONS_CH1
#define OCTAVE_UP        BUTTONS_CH2
#define OCTAVE_DOWN      BUTTONS_CH3
#define TRANSPOSE        BUTTONS_CH4

#define MOD_WHEEL        ADC080X_CH0
#define PITCH_BEND_WHEEL ADC080X_CH1
#define PORTAMENTO       ADC080X_CH2

volatile uint8_t keys[NUM_KEYS] = {KEY_IDLE};

// Executes in approximately 520uS
void timerCallback(void)
{
  for (uint8_t i = 0; i < NUM_KEYS; i++) {
    if (keys[i] < KEY_IDLE - 1) keys[i]++;
  }
}

void main(void)
{
  KEY_ROW_1 = 0x00;
  KEY_ROW_2 = 0x00;

  ADC080XInit();
  midiInit();
  timerInit();
  sei();

  __bit portamentoIsActive = 0;

  uint8_t octave   = 3;
  int8_t transpose = 0;

  uint8_t adcChannel       = 0;
  uint8_t prevAdcResult[3] = {0};

  while (1) {
    int16_t adcResult = ADC080XAsyncRead(adcChannel);

    if (ADC080XReady() && adcResult != prevAdcResult[adcChannel]) {
      prevAdcResult[adcChannel] = adcResult;

      if (adcResult < 2) adcResult = 0;

      uint16_t ccValue = toRange(adcResult, 255, 127);

      if (adcChannel == MOD_WHEEL) {
        sendMidi(MIDI_CC, MIDI_CH1, MIDI_CC_MOD_WHEEL, ccValue);
      } else if (adcChannel == PITCH_BEND_WHEEL) {
        if (125 < adcResult && adcResult < 129) {
          ccValue = MIDI_PITCH_BEND_CENTER;
        } else {
          ccValue = toRange(adcResult, 255, 0x3FFF);
        }
        sendMidi(MIDI_PITCH_BEND, MIDI_CH1, ccValue & 0x7F, ccValue >> 7);
      } else if (adcChannel == PORTAMENTO) {
        if ((__bit)ccValue != portamentoIsActive) {
          sendMidi(MIDI_CC, MIDI_CH1, MIDI_CC_PORTAMENTO, (__bit)ccValue * 127);
        }
        portamentoIsActive = ccValue;
        sendMidi(MIDI_CC, MIDI_CH1, MIDI_CC_PORTAMENTO_TIME, ccValue);
      }
    }
    if (ADC080XReady()) adcChannel = ++adcChannel % 3;

    if (loadButtons()) {
      if (readButtonEdge(KEY_HOLD, CHANGE) && readButton(SUSTAIN_PEDAL) == 1) {
        sendMidi(MIDI_CC, MIDI_CH1, 64, readButton(KEY_HOLD) * 127);
      }

      if (readButtonEdge(SUSTAIN_PEDAL, CHANGE) && readButton(KEY_HOLD) == 1) {
        sendMidi(MIDI_CC, MIDI_CH1, 64, readButton(SUSTAIN_PEDAL) * 127);
      }

      if (readButtonEdge(OCTAVE_UP, FALLING)) {
        if (readButton(TRANSPOSE) == 0) {
          transpose = max(transpose + 1, 12);
        } else {
          octave = max(octave + 1, (KEY_MAX_OFFSET - 12) / 12);
        }
      }

      if (readButtonEdge(OCTAVE_DOWN, FALLING)) {
        if (readButton(TRANSPOSE) == 0) {
          transpose = min(transpose - 1, -12);
        } else {
          octave = min(octave - 1, 0);
        }
      }
    }

    for (uint8_t i = 0; i < NUM_KEYS; i++) {
      uint8_t *key      = &keys[i];
      __bit keyTrigger0 = readKeyTrigger(i, 0);
      __bit keyTrigger1 = readKeyTrigger(i, 1);

      if (keyTrigger0 == 1 && KEY_IS_IDLE(*key)) {
        KEY_SET_PRIMED(*key);
      } else if (keyTrigger0 == 0 && KEY_IS_PRIMED(*key)) {
        KEY_SET_IDLE(*key);
      } else if (keyTrigger1 == 1 && KEY_IS_PRIMED(*key)) {
        uint8_t offset = clamp((octave * 12) + transpose, 0, KEY_MAX_OFFSET);
        uint8_t note   = i + offset;

        sendMidi(MIDI_NOTEON, MIDI_CH1, note, *key);

        KEY_SET_PRESSED(*key, offset);
      } else if ((keyTrigger1 == 0 || keyTrigger0 == 0) && KEY_IS_PRESSED(*key)) {
        uint8_t note = i + KEY_GET_OFFSET(*key);

        sendMidi(MIDI_NOTEOFF, MIDI_CH1, note, 0);

        KEY_SET_IDLE(*key);
      }
    }
  }
}