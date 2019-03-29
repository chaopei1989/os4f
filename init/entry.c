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
    console_write_line("1");
    console_write_line("2");
    console_write_line("3");
    console_write_line("4");
    console_write_line("5");
    console_write_line("6");
    console_write_line("7");
    console_write_line("8");
    console_tail_status("It's a pity. That's all.");
    return 0;
}
