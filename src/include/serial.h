#pragma once

#include <stdint.h>

void serialInit(uint32_t baudRate);
void serialWriteChar(char character);
void serialWriteString(char *string);
void serialWriteUint16(uint16_t value, uint8_t base);