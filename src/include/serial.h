#pragma once

#include <stdint.h>

void serialInit(uint32_t baudRate);
void serialWriteChar(char character);