#pragma once
#include <stdint.h>

void timerInit(float microseconds);
void timerCallback(void);

void TIMER0_ISR(void) __interrupt(1);