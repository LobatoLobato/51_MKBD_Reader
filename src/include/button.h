#pragma once
#include <stdint.h>
#include <stdbool.h>

#include "8052.h"

#define BUTTONS_SHIFT_CLK P3_0
#define BUTTONS_SHIFT_IN  P3_6
#define BUTTONS_SHIFT_LD  P3_7

#define BUTTONS_CH0       0
#define BUTTONS_CH1       1
#define BUTTONS_CH2       2
#define BUTTONS_CH3       3
#define BUTTONS_CH4       4
#define BUTTONS_CH5       5
#define BUTTONS_CH6       6
#define BUTTONS_CH7       7

enum BUTTON_EDGE {
    FALLING = 0,
    RISING  = 1,
};

__bit loadButtons(void);
__bit readButton(uint8_t button);
__bit readButtonEdge(uint8_t button, uint8_t edge);