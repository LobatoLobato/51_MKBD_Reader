#pragma once
#include <stdint.h>

int8_t clamp(int8_t x, int8_t min, int8_t max);
int8_t min(int8_t x, int8_t min);
int8_t max(int8_t x, int8_t max);
int16_t toRange(int16_t x, int16_t xmax, int16_t ymax);