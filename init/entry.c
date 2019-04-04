#include <console.h>
#include <gdt.h>
#include <string.h>
#include <printk.h>

static void console_fuck_welcome();

static void protect_enable();

int kern_entry()
{
    console_fuck_welcome();
    protect_enable();
    
    print_cur_status();
    return 0;
}

static void protect_enable()
{
    printk("Protect-Mode ready to enable.");
    init_gdt();
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
