#include <console.h>
#include <gdt.h>
#include <idt.h>
#include <_string.h>
#include <printk.h>
#include <timer.h>
#include <multiboot.h>
#include <vmm.h>
#include <pmm.h>

static void console_fuck_welcome();

static int32_t check_protect_enable();

// tmp_mboot_ptr -> paging -> glb_mboot_ptr
extern multiboot_t *tmp_mboot_ptr;

multiboot_t *glb_mboot_ptr;

static void kern_init();

// 开启分页机制之后的内核栈
uint8_t kern_stack[STACK_SIZE];

// before page available, we need tmp pgd and pte under 1M memory.
// And this pgd and pte are one-page-align(4KB, 0x1000)
// TODO: why 0x1000? 0-640KB not used in grub?

__attribute__((section(".init.data"))) pgd_t *pgd_tmp = (pgd_t *)0x1000;

__attribute__((section(".init.data"))) pte_t *pte_low_4M = (pte_t *)0x2000;

__attribute__((section(".init.data"))) pte_t *pte_high_4M = (pte_t *)0x3000;

/**
 * kernel entry method.
 * init.text and init.data located at 0x100000+, used for PGD and PTE.
 */
__attribute__((section(".init.text"))) void kern_entry()
{
    // enable paging first.
    // load PGD(Page Global Directory) and PTE(Page Table Entry)
    pgd_tmp[0] = (uint32_t) pte_low_4M | PAGE_PRESENT | PAGE_WRITE;
    pgd_tmp[INDEX_PGD(PAGE_OFFSET)] = (uint32_t) pte_high_4M | PAGE_PRESENT | PAGE_WRITE;

    for (int32_t i = 0; i < 1024; i++)
    {
        // every 4KB for one pte.
        pte_low_4M[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
        // low 4M memory and high 4M virtual memory all map to low 4M physical memory.
        pte_high_4M[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
    }

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

    // switch kernel stack, so paging cannot be a method(cannot return successfully).
    asm volatile(
        "mov %0, %%esp;"
        "xor %%ebp, %%ebp;"
        :
        : "r"(kern_stack));

    // welcome, m*ther f*cker.
    console_fuck_welcome();

    glb_mboot_ptr = tmp_mboot_ptr + PAGE_OFFSET;

    kern_init();
}

static void kern_init()
{
    // int reject
    asm volatile("cli");
    if (check_protect_enable())
    {
        printk("PE and A20 maybe set by grub, we just make sure new gdt init here.");
    }
    else
    {
        // TODO: entry PE
    }
    // flush gdt
    init_gdt();
    // flush idt
    init_idt();
    // init timer for 8253/8254 PIT
    init_timer(HZ);

    // int accept
    // asm volatile ("sti");
    //
    print_cur_status(); // should be 0x216, int accepct

    // test trap
    asm volatile("int $0xff");

    // TODO: others
    elf_from_multiboot(glb_mboot_ptr);

    show_memory_map();

    // ret to boot.s, loop hlt
}

static int32_t check_protect_enable()
{
    uint32_t reg_cr0 = 0;

    asm volatile("push %%eax;"
                 "mov %%cr0, %%eax;"
                 "mov %%eax, %0;"
                 "pop %%eax;"
                 : "=m"(reg_cr0));
    return reg_cr0 & 0x1;
}

static void console_fuck_welcome()
{
    console_clear();
    console_head_status("Welcome to OS4F, Enjoy it!");
    printk("                       .::::.");
    printk("                     .::::::::.");
    printk("                    :::::::::::");
    printk("                 ..:::::::::::'");
    printk("              '::::::::::::'");
    printk("                .::::::::::");
    printk("           '::::::::::::::..");
    printk("                ..::::::::::::.");
    printk("              ``::::::::::::::::");
    printk("               ::::``:::::::::'        .:::.");
    printk("              ::::'   ':::::'       .::::::::.");
    printk("            .::::'      ::::     .:::::::'::::.");
    printk("           .:::'       :::::  .:::::::::' ':::::.");
    printk("          .::'        :::::.:::::::::'      ':::::.");
    printk("         .::'         ::::::::::::::'         ``::::.");
    printk("     ...:::           ::::::::::::'              ``::.");
    printk("    ```` ':.          ':::::::::'                  ::::..");
    printk("                       '.:::::'                    ':'````..");
    console_tail_status("It's a pity. That's all.");
}
