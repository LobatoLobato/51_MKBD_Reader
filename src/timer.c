#include "include/timer.h"
#include "include/defs.h"
#include "8052.h"

void timerInit(void)
{
  cli();
  TMOD |= 0x01;
  TL0 = 0x30;
  TH0 = 0xF8;
  TR0 = 1;
  ET0 = 1;
  sei();
}

void TIMER0_ISR(void) __interrupt(1)
{
  timerCallback();

  TL0 = 0x30;
  TH0 = 0xF8;
}