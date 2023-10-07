#include "include/serial.h"
#include "8052.H"

void serialInit(uint32_t baudRate)
{
    cli();
    SCON = 0x50;
    TMOD |= 0x20;
    TH1 = 0xFF - (uint8_t)(UARTCLK / baudRate - 1);
    TR1 = 1;
    sei();
}

void serialWriteChar(char character)
{
    SBUF = character == '\n' ? 0x0D : character;
    while (TI == 0)
        ;
    TI = 0;
}

void serialWriteString(char *string)
{
    while (*string) {
        serialWriteChar(*string);
        string++;
    }
}

void serial_putuint_aux(uint16_t x, uint8_t base)
{
    if (x > 0) {
        serial_putuint_aux(x / base, base);
    }
    if (x > 0) {
        serialWriteChar("0123456789ABCDEF"[x % base]);
    }
}

void serialWriteUint16(uint16_t x, uint8_t base)
{
    if (x == 0) {
        serialWriteChar('0');
        return;
    }
    serial_putuint_aux(x, base);
}
