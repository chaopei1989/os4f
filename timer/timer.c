#include <timer.h>
#include <inout.h>
#include <printk.h>
#include <idt.h>
#include <int.h>
#include <console.h>

char buff[1024];

void timer_callback(pt_regs *regs)
{
    static uint32_t tick = 0;
    static uint32_t wall_time = 0;
    // (1000ms/HZ)=10ms per tick.
    if (++tick == 100)
    {
        tick = 0;
        printk_buff(buff, 1023, 0, "Welcome to OS4F, Enjoy it! Wall Time: %x", ++wall_time);
        console_head_status(buff);
    }
}

void init_timer(uint32_t frequency)
{
    register_interrupt_handler(IRQ0, timer_callback);

    // Intel 8253/8254 PIT芯片 I/O端口地址范围是40h~43h
    // 输入频率为 CLOCK_TICK_RATE=1193180，frequency 即每秒中断次数
    uint32_t divisor = CLOCK_TICK_RATE / frequency;

    // D7 D6 D5 D4 D3 D2 D1 D0
    // 0  0  1  1  0  1  1  0
    // 即就是 36 H
    // 设置 8253/8254 芯片工作在模式 3 下
    outb(0x43, 0x36);

    // 拆分低字节和高字节
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)(divisor >> 8);

    // 分别写入低字节和高字节
    outb(0x40, low);
    outb(0x40, high);
}
