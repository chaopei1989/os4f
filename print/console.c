#include "console.h"

/**
 * VGA 0xB8000～0xB8F9F~0xBFFFF
 * 每双字节代表一个字符
 * 单行: 80字符, 0xA0字节
 * 单屏: 80字符*25行, 80*25*2=0xFA0字节
 * 
 * 0xB8000~0xB809F 首行状态栏 H
 * 0xB80A0~0xB813F msg
 * ...
 * 0xB8E60~0xB8EFF msg
 * 0xB8F00~0xB8F9F 末行状态栏 T
 * 
 * TODO: 其他分辨率暂时不管 
 */
#define VIDEO_MSG_START 0xB80A0

#define VIDEO_H_STAT_START 0xB8000

#define VIDEO_T_STAT_START 0xB8F00

#define DEF_F_COLOR rc_white

#define DEF_B_COLOR rc_black

struct console_print_cursor
{
    /**
     * 当前光标所在
     */
    uint16_t *curr;

    /**
     * 文字显示区域的开头, 从VIDEO_MEM_START到from之间均为空字符
     */
    uint16_t *from;
};

/**
 * 当前cursor所在
 */
struct console_print_cursor s_cursor = {
    .curr = (uint16_t *)VIDEO_MSG_START,
    .from = (uint16_t *)VIDEO_MSG_START,
};

inline uint16_t atrr_char(char c, real_color_t f_color, real_color_t b_color);

void console_clear()
{
}

void console_write(char *msg)
{
}

void console_write_f(char *msg, real_color_t f_color)
{
}

void console_write_f_b(char *msg,
                       real_color_t f_color,
                       real_color_t b_color)
{
}

void head_status()
{
    uint16_t *base_addr = (uint16_t *)VIDEO_H_STAT_START;
    for (size_t i = 0; i < 80; i++)
    {
        base_addr[i] = atrr_char('H', rc_red, rc_black);
    }
}

void tail_status()
{
    uint16_t *base_addr = (uint16_t *)VIDEO_T_STAT_START;
    for (size_t i = 0; i < 80; i++)
    {
        base_addr[i] = atrr_char('A', rc_blue, rc_black);
    }
}

uint16_t atrr_char(char c, real_color_t f_color, real_color_t b_color)
{
    uint8_t attribute_byte = (f_color << 4) | (b_color & 0x0F);
    uint16_t ret = c | (attribute_byte << 8);
    return ret;
}