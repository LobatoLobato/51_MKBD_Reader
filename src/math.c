#include "include/math.h"

int8_t min(int8_t x, int8_t min)
{
  if (x < min) return min;
  return x;
}
int8_t max(int8_t x, int8_t max)
{
  if (x > max) return max;
  return x;
}
int8_t clamp(int8_t x, int8_t min, int8_t max)
{
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

int16_t toRange(int16_t x, int16_t xmax, int16_t ymax)
{
  return ((x) * ((float)(ymax) / (float)(xmax)));
}