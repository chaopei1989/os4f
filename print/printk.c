#include <types.h>
#include <_string.h>
#include <vargs.h>
#include <console.h>
#include <printk.h>
#include <gdt.h>

static void printk_buff_args(char *buff, int32_t len, int32_t buff_offset, char *fmt, char *args);

void printk(char *fmt, ...)
{
    // TODO: 由于现在只能栈上分配内存, 我们暂定最多1024字节
    char buff[1024];
    memset(buff, 0, 1024);
    va_list args;
    VA_START(args, fmt);
    printk_buff_args((char *)buff, 1024 - 1, 0, fmt, args);
    console_write_line(buff);
    VA_END(args);
}

void printk_buff(char *buff, int32_t len, int32_t buff_offset, char *fmt, ...)
{
    va_list args;
    VA_START(args, fmt);
    printk_buff_args((char *)buff, len, buff_offset, fmt, args);
    VA_END(args);
}

static void printk_buff_args(char *buff,
                             int32_t len,
                             int32_t buff_offset,
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
                int32_t next_arg_len = strlen((const char *)next_arg);
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
                uint32_t next_arg = VA_ARG(args, uint32_t);
                char msg[11];
                // 取值
                h32toa((uint32_t)next_arg, msg);
                int32_t next_arg_len;
                next_arg_len = sizeof(msg) - 1;
                if (next_arg_len > 0 && next_arg_len + buff_offset <= len - 1)
                {
                    memcpy((void *)buff + buff_offset, (void *)msg, next_arg_len);
                    buff_offset += next_arg_len;
                }
                break;
            }
            case 'd':
            {
                ++i;
                uint32_t next_arg = VA_ARG(args, uint32_t);
                char msg[11];
                // 取值
                int32_t next_arg_len = itoa((int32_t)next_arg, msg);
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
    uint32_t reg_cs = 0, reg_ds = 0, reg_es = 0, reg_ss = 0, reg_ebp = 0, reg_esp = 0;
    uint32_t reg_cr0 = 0;
    uint32_t reg_eflags = 0;
    asm volatile("mov %%cs, %0;"
                 "mov %%ds, %1;"
                 "mov %%es, %2;"
                 "mov %%ss, %3;"
                 "mov %%ebp, %4;"
                 "mov %%esp, %5;"
                 "push %%eax;"
                 "mov %%cr0, %%eax;"
                 "mov %%eax, %6;"
                 "pushfl;"
                 "pop %%eax;"
                 "mov %%eax, %7;"
                 "push %%eax;"
                 "popfl;"
                 "pop %%eax;"
                 : "=m"(reg_cs), "=m"(reg_ds), "=m"(reg_es), "=m"(reg_ss),
                   "=m"(reg_ebp), "=m"(reg_esp),
                   "=m"(reg_cr0),
                   "=m"(reg_eflags));

    printk("@ring %x;\n"
           "cs  = %x; ds  = %x;\n"
           "es  = %x; ss  = %x;\n"
           "ebp = %x; esp = %x;\n"
           "cr0 = %x; efl = %x;",
           reg_ds & 0x3,
           reg_cs, reg_ds,
           reg_es, reg_ss,
           reg_ebp, reg_esp,
           reg_cr0, reg_eflags);
}
