#pragma once
#include <stdint.h>
#include "8052.h"
#include "include/math.h"

#define KEY_COL             P1
#define KEY_ROW_1           P0
#define KEY_ROW_2           P2

#define KEY_MAX_OFFSET      60u
#define KEY_PRIMED          0u
#define KEY_IDLE            (uint8_t)(UINT8_MAX - KEY_MAX_OFFSET - 1)
#define KEY_PRESSED         (uint8_t)(UINT8_MAX - KEY_MAX_OFFSET)
#define KEY_IS_IDLE(key)    (key == KEY_IDLE)
#define KEY_IS_PRIMED(key)  (key < KEY_IDLE)
#define KEY_IS_PRESSED(key) (key >= KEY_PRESSED)

#define KEY_SET_IDLE(key)   (key = KEY_IDLE)
#define KEY_SET_PRIMED(key) (key = KEY_PRIMED)
#define KEY_SET_PRESSED(key, offset) \
    (key = KEY_PRESSED + clamp(offset, 0, KEY_MAX_OFFSET))

__bit readKeyTrigger(uint8_t key, __bit trigger);
uint8_t getKeyOffset(uint8_t key);