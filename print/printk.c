#include <types.h>
#include <string.h>
#include <vargs.h>
#include <console.h>
#include <printk.h>

static void _printk_buff_args(char *buff, int len, int buff_offset, char *fmt, char *args);

void printk(char *fmt, ...)
{
    // TODO: 由于现在只能栈上分配内存, 我们暂定最多1024字节
    char buff[1024];
    memset(buff, 0, 1024);
    va_list args;
    VA_START(args, fmt);
    _printk_buff_args((char *)buff, 1024 - 1, 0, fmt, args);
    console_write_line(buff);
    VA_END(args);
}

void printk_buff(char *buff, int len, int buff_offset, char *fmt, ...)
{
    va_list args;
    VA_START(args, fmt);
    _printk_buff_args((char *)buff, len, buff_offset, fmt, args);
    VA_END(args);
}

static void _printk_buff_args(char *buff,
                              int len,
                              int buff_offset,
                              char *fmt,
                              va_list args)
{
    if (buff_offset > len - 1)
    {
        // out of bound
        return;
    }
    for (size_t i = 0;; i++)
    {
        if (fmt[i] == '\0' || buff_offset == len - 1)
        {
            buff[buff_offset] = '\0';
            return;
        }
        else if (fmt[i] == '%')
        {
            switch (fmt[i + 1])
            {
            case 's':
            {
                ++i;
                const char *next_arg = VA_ARG(args, const char *);
                // 取内容
                int next_arg_len = strlen((const char *)next_arg);
                if (next_arg_len > 0 && next_arg_len + buff_offset <= len - 1)
                {
                    memcpy((void *)buff + buff_offset, (void *)next_arg, next_arg_len);
                    buff_offset += next_arg_len;
                }
                break;
            }
            case 'x':
            {
                ++i;
                unsigned int next_arg = VA_ARG(args, unsigned int);
                char msg[11];
                // 取值
                h32toa((unsigned int)next_arg, msg);
                int next_arg_len;
                next_arg_len = sizeof(msg) - 1;
                if (next_arg_len > 0 && next_arg_len + buff_offset <= len - 1)
                {
                    memcpy((void *)buff + buff_offset, (void *)msg, next_arg_len);
                    buff_offset += next_arg_len;
                }
                break;
            }
            default:
            {
                buff[buff_offset++] = '%';
                break;
            }
            }
        }
        else
        {
            buff[buff_offset++] = fmt[i];
        }
    }
}

void print_cur_status()
{
    static int round = 0;
    uint32_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0;
    uint32_t reg_cr0 = 0;

    asm volatile("mov %%cs, %0;"
                 "mov %%ds, %1;"
                 "mov %%es, %2;"
                 "mov %%ss, %3;"
                 "mov %%ebp, %4;"
                 "mov %%esp, %5;"
                 "push %%eax;"
                 "mov %%cr0, %%eax;"
                 "mov %%eax, %6;"
                 "pop %%eax;"
                 : "=m"(reg0), "=m"(reg1), "=m"(reg2), "=m"(reg3), "=m"(reg4), "=m"(reg5),
                   "=m"(reg_cr0));

    // 打印当前的运行级别
    printk("round %x:\n"
           "  @ring %x;\n"
           "  cs = %x; ds = %x;\n"
           "  es = %x; ss = %x;\n"
           "  ebp= %x; esp= %x;\n"
           "  cr0 = %x",
           round, reg1 & 0x3, reg0, reg1, reg2, reg3, reg4, reg5, reg_cr0);
    ++round;
}
