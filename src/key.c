#include "include/key.h"

__bit readKeyTrigger(uint8_t key, __bit trigger)
{
  uint8_t col      = ((uint8_t)(key / 8) % 4) * 2;
  uint8_t col_mask = (trigger + 1) << col;
  uint8_t row_mask = 1 << (key % 8);

  KEY_COL = col_mask;

  return (__bit)((key < 32 ? KEY_ROW_1 : KEY_ROW_2) & row_mask);
}