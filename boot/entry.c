#include <console.h>
#include <gdt.h>
#include <idt.h>
#include <string.h>
#include <printk.h>
#include <timer.h>
#include <multiboot.h>

static void console_fuck_welcome();

static int check_protect_enable();

int kern_entry()
{
    // int reject
    asm volatile ("cli");
    console_fuck_welcome();
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

    // ret to boot.s, loop hlt
    return 0;
}

static int check_protect_enable()
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