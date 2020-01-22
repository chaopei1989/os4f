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

/**
 * 从grub提供的multiboot_t结构体中打印可用内存区域
 */
void show_memory_map();

/**
 * 根据multiboot结构体计算剩余物理内存, 并初始化物理内存管理
 */
void init_pmm();

#define alloc_page alloc_pages(0)

void alloc_pages(int order);

void free_pages(uint32_t addr, int order);

void kmalloc();

void kfree();

#endif
