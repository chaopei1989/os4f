#include <gdt.h>
#include <printk.h>

// 全局描述符表长度
#define GDT_LENGTH 5

// 全局描述符表定义
gdt_entry_t gdt_entries[GDT_LENGTH];

// GDTR
gdt_ptr_t gdt_ptr;

static void gdt_set_gate(int32_t num, uint32_t base,
                         uint32_t limit, uint8_t access, uint8_t gran);

// 声明内核栈地址
extern uint32_t stack;

// 初始化全局描述符表
void init_gdt()
{
    // 全局描述符表界限 e.g. 从 0 开始，所以总长要 - 1
    gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_LENGTH - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    // 采用 Intel 平坦模型
    printk("Init GDT Now");
    gdt_set_gate(0, 0, 0, 0, 0);                // 按照 Intel 文档要求，第一个描述符必须全 0
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // 代码段
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // 数据段
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // 用户模式代码段
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // 用户模式数据段
    // 加载全局描述符表地址到 GPTR 寄存器
    printk("Flush GDT");
    gdt_flush((uint32_t)&gdt_ptr);
    print_cur_gdt();
}

// 全局描述符表构造函数，根据下标构造
// 参数分别是 数组下标、基地址、限长、访问标志，其它访问标志
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access = access;
}

void print_cur_gdt()
{
    gdt_ptr_t reg_gdtr;
    asm volatile("sgdt %0;"
                 : "=m"(reg_gdtr));
    gdt_entry_t *cur_gdts = (gdt_entry_t *)reg_gdtr.base;
    printk("print_cur_gdt:\n"
           "gdtr_H32= %x;\n"
           "gdtr_L16= %x;\n"
           "Index|Base      |Limit     |Access    |Gran      ",
           reg_gdtr.base,
           reg_gdtr.limit);
    for (int i = 0; i < (reg_gdtr.limit + 1) / 8; i++)
    {
        uint32_t base = ((cur_gdts + i)->base_low) |
                        ((cur_gdts + i)->base_middle << 16) |
                        ((cur_gdts + i)->base_high << 24);
        uint32_t limit = ((cur_gdts + i)->limit_low) |
                         ((cur_gdts + i)->granularity << 16);
        printk("%d   |%x|%x|%x|%x|",
               i, base, limit, (cur_gdts + i)->access, (cur_gdts + i)->granularity);
    }
}
