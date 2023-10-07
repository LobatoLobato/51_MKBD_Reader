#pragma once
#include <stdint.h>

#include "8052.h"

#define ADC080X_SHIFT_CLK       P3_0
#define ADC080X_EOC             P3_2
#define ADC080X_SHIFT_IN        P3_3
#define ADC080X_SHIFT_OUT       P3_4
#define ADC080X_SHIFT_OUT_LATCH P3_5

#define ADC080X_SHIFT_START_BIT 0x08
#define ADC080X_SHIFT_LD_BIT    0x10

#define ADC080X_CH0             0x00
#define ADC080X_CH1             0x01
#define ADC080X_CH2             0x02
#define ADC080X_CH3             0x03

void ADC080XInit(void);

int16_t ADC080XAsyncRead(uint8_t channel);
uint8_t ADC080XRead(uint8_t channel);
__bit ADC080XReady(void);

void ADC080X_EOC_ISR(void) __interrupt(0);