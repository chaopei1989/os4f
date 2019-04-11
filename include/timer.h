#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

#include "types.h"

#define HZ 100 // for i386, (1000ms/HZ)=10ms per tick. min 19 avail

#define CLOCK_TICK_RATE 1193180 // 8253/8254 PIT 时钟周期的频率

void init_timer(uint32_t frequency);

#endif // INCLUDE_TIMER_H_
