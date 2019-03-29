#include "console.h"

int kern_entry()
{
    console_clear();
    console_head_status();
    console_tail_status();
    return 0;
}
