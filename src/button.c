#include "include/button.h"

uint8_t button_states      = 0xFF;
uint8_t prev_button_states = 0xFF;

__bit loadButtons(void)
{
  BUTTONS_SHIFT_LD = 1;
  BUTTONS_SHIFT_LD = 0;
  BUTTONS_SHIFT_LD = 1;

  uint8_t result = 0x00;
  for (uint8_t i = 0; i < 8; i++) {
    result |= BUTTONS_SHIFT_IN << i;
    BUTTONS_SHIFT_CLK = 0;
    BUTTONS_SHIFT_CLK = 1;
  }

  prev_button_states = button_states;

  if (button_states != result) {
    button_states = result;
    return true;
  }

  return false;
}

__bit readButton(uint8_t button)
{
  return button_states & (1 << button);
}

__bit readButtonEdge(uint8_t button, uint8_t edge)
{
  __bit isPressed  = button_states & (1 << button);
  __bit wasPressed = prev_button_states & (1 << button);

  if ((edge & FALLING) && !isPressed && wasPressed) {
    return 1;
  }

  if ((edge & RISING) && isPressed && !wasPressed) {
    return 1;
  }

  return 0;
}