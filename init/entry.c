#include "console.h"

int kern_entry()
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

    pe();
    return 0;
}
