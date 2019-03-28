#include "console.h"

int kern_entry()
{
    // uint8_t *input = (uint8_t *)0xB8000;
    // uint8_t color = (0 << 4) | (15 & 0x0F);

    // *input++ = 'Z'; *input++ = color;
    // *input++ = 'e'; *input++ = color;
    // *input++ = 'n'; *input++ = color;
    // *input++ = 'g'; *input++ = color;
    // *input++ = 'X'; *input++ = color;
    // *input++ = 'i'; *input++ = color;
    // *input++ = 'a'; *input++ = color;
    // *input++ = 'o'; *input++ = color;
    // *input++ = 'C'; *input++ = color;
    // *input++ = 'h'; *input++ = color;
    // *input++ = 'a'; *input++ = color;
    // *input++ = 'o'; *input++ = color;
    // *input++ = ' '; *input++ = color;
    // *input++ = 'O'; *input++ = color;
    // *input++ = 'S'; *input++ = color;
    // *input++ = '4'; *input++ = color;
    // *input++ = 'F'; *input++ = color;
    head_status();
    tail_status();
    return 0;
}
