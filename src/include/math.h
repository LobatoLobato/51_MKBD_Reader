#pragma once
#include <stdint.h>

int16_t clamp(int16_t x, int16_t min, int16_t max);
int16_t min(int16_t x, int16_t min);
int16_t max(int16_t x, int16_t max);
int16_t toRange(int16_t x, int16_t xmin, int16_t xmax, int16_t ymin, int16_t ymax);