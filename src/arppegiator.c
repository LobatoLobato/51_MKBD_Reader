#include "include/arppegiator.h"
#include <stdbool.h>
#include "8052.h"

__idata ArppegiatorNote sequence[ARPPEGIATOR_SIZE] = {{.note = 0, .velocity = 0}};

uint8_t sequence_size = 0;

void remove(uint8_t note) __reentrant
{
  __bit shift = false;
  for (uint8_t i = 0; i < ARPPEGIATOR_SIZE; i++) {
    if (sequence[i].note == note) shift = true;
    if (shift) sequence[i] = sequence[i + 1];
  }

  if (shift) sequence_size--;
}

void push(uint8_t note, uint8_t velocity) __reentrant
{
  if (ARPPEGIATOR_SIZE == sequence_size) {
    remove(sequence[0].note);
  }

  sequence[sequence_size].note     = note;
  sequence[sequence_size].velocity = velocity;
  sequence_size++;
}

const struct __arppegiator_ns __Arppegiator = {
    .remove = remove,
    .push   = push,
};
