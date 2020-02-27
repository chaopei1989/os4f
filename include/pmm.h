#ifndef INCLUDE_PMM_H_
#define INCLUDE_PMM_H_

#include <types.h>
#include <page.h>
#include <vmm.h>

// define some constant addr for physical memory

/**
 * VGA start
 */ 
#define VGA_START 0xB8000

/**
 * 8KB stack size
 */
#define STACK_SIZE 8192

// 8MB的内核地址空间
#define KERNEL_SPACE (8 * 1024 * 1024)

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

// 8M内核虚拟地址映射page结构体数组, 一共2K个
struct page mem_map[KERNEL_SPACE / PAGE_SIZE];

// 内核的所有内存地址都可以直接找到对应的page对象
#define vir_to_page(vir_addr) (mem_map + ((vir_addr - PAGE_OFFSET) >> PAGE_SHIFT))

// 伙伴算法节点
struct pmm_node
{
    // 该页的起始位置
    uint32_t start_addr;
    // 是否已经分配 0/1
    uint32_t flag;
    // 大小B
    uint32_t size;
};

#define MAX_ORDER 11

struct free_area {
    // 空闲内存块链表
	struct list_head free_list;
    //该组类别块空闲的个数
	unsigned long nr_free;
};

// 只考虑单一内存区域
struct free_area free_areas[MAX_ORDER];


#endif
