#include "include/serial.h"
#include "include/defs.h"
#include "8052.H"

void serialInit(uint32_t baudRate)
{
  cli();
  SCON = 0x50;
  TMOD |= 0x20;
  TH1 = 0xFF - (UARTCLK / baudRate - 1);
  TR1 = 1;
  sei();
}

void serialWriteChar(char character)
{
  SBUF = character;
  while (TI == 0)
    ;
  TI = 0;
}
