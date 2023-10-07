#include "include/math.h"

int16_t min(int16_t x, int16_t min)
{
    if (x < min) return min;
    return x;
}
int16_t max(int16_t x, int16_t max)
{
    if (x > max) return max;
    return x;
}
int16_t clamp(int16_t x, int16_t min, int16_t max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

int16_t toRange(int16_t x, int16_t xmin, int16_t xmax, int16_t ymin, int16_t ymax)
{
    return ((x - xmin) * ((float)(ymax - ymin) / (float)(xmax - xmin))) + ymin;
}