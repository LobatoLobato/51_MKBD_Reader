#include "include/timer.h"
#include "include/defs.h"
#include "8052.h"

volatile uint8_t tl0 = 0xFF;
volatile uint8_t th0 = 0xFE;

void timerInit(float microseconds)
{
    float periodMicroseconds = (1.0 / MCLK);

    microseconds *= 0.000001;

    uint16_t count = ((uint32_t)(UINT16_MAX + 1) - (uint16_t)(microseconds / periodMicroseconds)) + 1;

    tl0 = count & 0xFF;
    th0 = count >> 8;

    cli();
    TMOD |= 0x01;
    TL0 = tl0;
    TH0 = th0;
    TR0 = 1;
    ET0 = 1;
    sei();
}

void TIMER0_ISR(void) __interrupt(1)
{
    timerCallback();

    TL0 = tl0;
    TH0 = th0;
}