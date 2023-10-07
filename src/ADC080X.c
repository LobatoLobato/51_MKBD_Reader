#include "include/ADC080X.h"

void shift_out(uint8_t value)
{
    ADC080X_SHIFT_OUT_LATCH = 1;
    for (int8_t i = 7; i >= 0; i--) {
        ADC080X_SHIFT_OUT = value & (1 << i);
        ADC080X_SHIFT_CLK = 1;
        ADC080X_SHIFT_CLK = 0;
    }
    ADC080X_SHIFT_OUT_LATCH = 0;
    ADC080X_SHIFT_OUT_LATCH = 1;
}

void start_conversion(uint8_t channel)
{
    shift_out(channel | ADC080X_SHIFT_START_BIT);
    shift_out(channel & ~ADC080X_SHIFT_START_BIT);
}

uint8_t load_result(uint8_t channel)
{
    shift_out(channel | ADC080X_SHIFT_LD_BIT);
    shift_out(channel & ~ADC080X_SHIFT_LD_BIT);
    shift_out(channel | ADC080X_SHIFT_LD_BIT);

    uint8_t result = 0x00;
    for (uint8_t i = 0; i < 8; i++) {
        result |= ADC080X_SHIFT_IN << i;
        ADC080X_SHIFT_CLK = 0;
        ADC080X_SHIFT_CLK = 1;
    }

    return result;
}

void ADC080XInit(void)
{
    shift_out(0x00 | ADC080X_SHIFT_LD_BIT);
    EX0 = 1; /* Enable Ext. interrupt0 */
    IT0 = 1; /* Select Ext. interrupt0 on falling edge */
}

__bit soc_flag          = 0;
volatile __bit eoc_flag = 1;

void ADC080X_EOC_ISR(void) __interrupt(0)
{
    eoc_flag = 1;
}

int16_t ADC080XAsyncRead(uint8_t channel)
{
    if (soc_flag == 1 && eoc_flag == 0) {
        return -1;
    } else if (soc_flag == 0) {
        soc_flag = 1;
        eoc_flag = 0;

        start_conversion(channel);

        return -1;
    }

    uint8_t result = load_result(channel);

    soc_flag = 0;

    return (uint8_t)result;
}

uint8_t ADC080XRead(uint8_t channel)
{
    int16_t result = ADC080XAsyncRead(channel);

    while (result == -1) {
        result = ADC080XAsyncRead(channel);
    }
    return (uint8_t)result;
}

__bit ADC080XReady(void)
{
    return eoc_flag == 1;
}