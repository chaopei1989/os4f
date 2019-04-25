#include <int.h>
#include <printk.h>
#include <inout.h>

void register_interrupt_handler(uint8_t n, interrupt_handler_t h)
{
    interrupt_handlers[n] = h;
}

// 调用中断处理函数
void isr_handler(pt_regs_t *regs)
{
    if (interrupt_handlers[regs->int_no])
    {
        interrupt_handlers[regs->int_no](regs);
    }
    else
    {
        // TODO:
        printk("isr_handler: default handle, int %d", regs->int_no);
    }
}

void irq_handler(pt_regs_t *regs)
{
    // 发送中断结束信号给 PICs
    // 按照我们的设置，从 32 号中断起为用户自定义中断
    // 因为单片的 Intel 8259A 芯片只能处理 8 级中断
    // 故大于等于 40 的中断号是由从片处理的
    if (regs->int_no >= 40)
    {
        // 发送重设信号给从片
        outb(0xA0, 0x20);
    }
    // 发送重设信号给主片
    outb(0x20, 0x20);

    if (interrupt_handlers[regs->int_no])
    {
        interrupt_handlers[regs->int_no](regs);
    }
    else
    {
        // TODO:
        printk("irq_handler: default handle, int %d", regs->int_no);
    }
}
