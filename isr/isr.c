#include <isr.h>

extern interrupt_handler_t *interrupt_handlers;

// 调用中断处理函数
void isr_handler(pt_regs *regs)
{
    if (interrupt_handlers[regs->int_no])
    {
        interrupt_handlers[regs->int_no](regs);
    }
    else
    {
        // TODO:
    }
}