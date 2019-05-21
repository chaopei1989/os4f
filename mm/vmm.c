#include <vmm.h>

// 开启分页机制之后的内核栈
char kern_stack[STACK_SIZE];

// before page available, we need tmp pgd and pte under 1M memory.
// And this pgd and pte are one-page-align(4KB, 0x1000)
// TODO: why 0x1000? 0-640KB not used in grub?
__attribute__((section(".init.data"))) pgd_t *pgd_tmp = (pgd_t *)0x1000;

__attribute__((section(".init.data"))) pgd_t *pte_low = (pgd_t *)0x2000;

__attribute__((section(".init.data"))) pgd_t *pte_high = (pgd_t *)0x3000;

int enable_paging()
{
    // TODO: load PGD(Page Global Directory) and PTE(Page Table Entry)
    
    // tmp pgd and pte
    asm volatile("mov %0, %%cr3"
                 :
                 : "r"(pgd_tmp));

    // enable paging, cr0 paging set 1
    uint32_t cr0;
    asm volatile("mov %%cr0, %0"
                 : "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0"
                 :
                 : "r"(cr0));

    // TODO: switch kernel stack

    return 0;
}
