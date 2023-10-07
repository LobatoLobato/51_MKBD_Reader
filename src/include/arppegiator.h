#pragma once
#include <stdint.h>

#define ARPPEGIATOR_SIZE 63

typedef struct {
  uint8_t note;
  uint8_t velocity;
} ArppegiatorNote;

extern const struct __arppegiator_ns {
  void (*push)(uint8_t note, uint8_t velocity) __reentrant;
  void (*remove)(uint8_t note) __reentrant;
} __Arppegiator;
#define Arppegiator __Arppegiator