#include <console.h>
#include <gdt.h>
#include <string.h>
#include <printk.h>

static void console_fuck_welcome();

static int check_protect_enable();

int kern_entry()
{
    console_fuck_welcome();
    print_cur_status();
    print_cur_gdt();
    // print EIP
    // x86_get_pc();
    // uint32_t reg_eax = 0;
    // asm volatile("mov %%eax, %0;"
    //              : "=m"(reg_eax));
    // printk(after x86_get_pc_thunk, reg_eax=%x", reg_eax);

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
