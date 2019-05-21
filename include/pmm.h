#ifndef INCLUDE_PMM_H_
#define INCLUDE_PMM_H_

#include <types.h>

extern uint8_t kern_start[];

extern uint8_t kern_end[];

void show_memory_map();

void kmalloc();

void kfree();

#endif
