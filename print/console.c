#include "console.h"
#include "string.h"

/**
 * VGA 0xB8000～0xB8F9F~0xBFFFF
 * 每双字节代表一个字符
 * 单行: 80字符, 0xA0字节
 * 单屏: 80字符*25行, 80*25*2=0xFA0字节
 * 
 * 0xB8000~0xB809F 首行状态栏 H, VIDEO_H_STAT_START~
 * 0xB80A0~0xB813F msg, VIDEO_MSG_START~
 * ...
 * 0xB8E60~0xB8EFF msg
 * 0xB8F00~0xB8F9F 末行状态栏 T, VIDEO_T_STAT_START~
 * 
 * TODO: 其他分辨率暂时不管 
 */
#define VIDEO_MSG_START 0xB80A0

#define VIDEO_H_STAT_START 0xB8000

#define VIDEO_T_STAT_START 0xB8F00

#define LEN_SINGLE_LINE 80

#define DEFAULT_FOREGROUND_COLOR rc_white

#define DEFAUlt_BACKGROUND_COLOR rc_black

/**
 * 当前cursor所在
 */
uint16_t *s_cursor = VIDEO_MSG_START;

void console_clear()
{
    memset((void *)VIDEO_MSG_START, 0, VIDEO_T_STAT_START - VIDEO_MSG_START);
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

/**
 * 指定字符指定前景背景颜色, 返回对应的双字节内存表示
 */
inline uint16_t _atrr_char(char c, real_color_t f_color, real_color_t b_color);

void console_head_status(char *head_msg)
{
    uint16_t *base_addr = (uint16_t *)VIDEO_H_STAT_START;
    const int str_len = strlen(head_msg);
    const int cpy_len = LEN_SINGLE_LINE >= str_len ? str_len : LEN_SINGLE_LINE;
    memcpy(base_addr, head_msg, cpy_len);
}

void console_tail_status(char *tail_msg)
{
    uint16_t *base_addr = (uint16_t *)VIDEO_T_STAT_START;
    const int str_len = strlen(tail_msg);
    const int cpy_len = LEN_SINGLE_LINE >= str_len ? str_len : LEN_SINGLE_LINE;
    memcpy(base_addr, tail_msg, cpy_len);
}

uint16_t _atrr_char(char c, real_color_t f_color, real_color_t b_color)
{
    uint8_t attribute_byte = (f_color << 4) | (b_color & 0x0F);
    uint16_t ret = c | (attribute_byte << 8);
    return ret;
}