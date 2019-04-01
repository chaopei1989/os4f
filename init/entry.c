#include "console.h"
#include "gdt.h"

static void console_fuck_welcome();

static void protect_enable();

int kern_entry()
{
    console_fuck_welcome();
    protect_enable();
    return 0;
}

static void protect_enable()
{
    console_write_line("Protect-Mode ready to enable.");
    init_gdt();
}

static void console_fuck_welcome()
{
    console_clear();
    console_head_status("Welcome to OS4F, Enjoy it!");
    console_write_line("                       .::::.");
    console_write_line("                     .::::::::.");
    console_write_line("                    :::::::::::");
    console_write_line("                 ..:::::::::::'");
    console_write_line("              '::::::::::::'");
    console_write_line("                .::::::::::");
    console_write_line("           '::::::::::::::..");
    console_write_line("                ..::::::::::::.");
    console_write_line("              ``::::::::::::::::");
    console_write_line("               ::::``:::::::::'        .:::.");
    console_write_line("              ::::'   ':::::'       .::::::::.");
    console_write_line("            .::::'      ::::     .:::::::'::::.");
    console_write_line("           .:::'       :::::  .:::::::::' ':::::.");
    console_write_line("          .::'        :::::.:::::::::'      ':::::.");
    console_write_line("         .::'         ::::::::::::::'         ``::::.");
    console_write_line("     ...:::           ::::::::::::'              ``::.");
    console_write_line("    ```` ':.          ':::::::::'                  ::::..");
    console_write_line("                       '.:::::'                    ':'````..");
    console_tail_status("It's a pity. That's all.");
}
