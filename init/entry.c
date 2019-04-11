#include <console.h>
#include <gdt.h>
#include <idt.h>
#include <string.h>
#include <printk.h>
#include <timer.h>

static void console_fuck_welcome();

static int check_protect_enable();

int kern_entry()
{
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
    print_cur_status();
    // timer 
    init_timer(100);
    // test interrupt
    asm volatile("int $0x02");
    asm volatile("int $0x04");
    asm volatile("int $0x06");
    // 开启中断
    asm volatile ("sti");
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
