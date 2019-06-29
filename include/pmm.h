#ifndef INCLUDE_PMM_H_
#define INCLUDE_PMM_H_

#include <types.h>

// define some constant addr for physical memory

/**
 * VGA start
 */ 
#define VGA_START 0xB8000

/**
 * 8KB stack size
 */
#define STACK_SIZE 8192

extern struct multiboot *tmp_mboot_ptr;

// extern uint8_t ;

extern uint8_t kern_start[];

extern uint8_t kern_end[];

void show_memory_map();

void kmalloc();

void kfree();

#endif
