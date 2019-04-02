#include <console.h>
#include <string.h>
#include <inout.h>

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

#define LEN_ROWS 25

#define BYTE_SINGLE_LINE 0xA0

#define DEFAULT_FOREGROUND_COLOR rc_white

#define DEFAULT_BACKGROUND_COLOR rc_black

struct cursor
{
    uint16_t *curr;
    uint16_t x;
    uint16_t y;
};

/**
 * 当前cursor总是处在一行的开头
 */
struct cursor s_cursor = {
    .curr = VIDEO_MSG_START,
    .x = 1,
    .y = 0,
};

/**
 * 指定字符指定前景背景颜色, 返回对应的双字节内存表示
 */
inline uint16_t _atrr_char(char c, real_color_t f_color, real_color_t b_color);

/**
 * 指定字符串指定前景背景颜色显示在指定行 
 */
static void console_print_line(uint16_t *base_addr,
                               const char *msg,
                               real_color_t f_color,
                               real_color_t b_color);

static void move_cursor(uint16_t x, uint16_t y);

static void scroll_up_line(uint16_t line);

void console_clear()
{
    for (uint16_t *addr = VIDEO_MSG_START; addr < VIDEO_T_STAT_START; addr++)
    {
        // 全部空格符号
        *addr = _atrr_char(
            ' ', DEFAULT_FOREGROUND_COLOR, DEFAULT_BACKGROUND_COLOR);
    }
    s_cursor.curr = VIDEO_MSG_START;
    s_cursor.x = 0;
    s_cursor.y = 1;
    move_cursor(s_cursor.x, s_cursor.y);
}

void console_write_line(const char *msg)
{
    console_print_line(
        s_cursor.curr, msg, DEFAULT_FOREGROUND_COLOR, DEFAULT_BACKGROUND_COLOR);
    s_cursor.curr += LEN_SINGLE_LINE;
    s_cursor.x = 0;
    s_cursor.y += 1;
    move_cursor(s_cursor.x, s_cursor.y);
    // 如果到了最后一行, 往上滚一行
    if (s_cursor.y == LEN_ROWS - 1)
    {
        scroll_up_line(1);
    }
}

void console_head_status(const char *head_msg)
{
    uint16_t *base_addr = (uint16_t *)VIDEO_H_STAT_START;
    console_print_line(base_addr, head_msg, rc_white, rc_blue);
}

void console_tail_status(const char *tail_msg)
{
    uint16_t *base_addr = (uint16_t *)VIDEO_T_STAT_START;
    console_print_line(base_addr, tail_msg, rc_white, rc_red);
}

uint16_t _atrr_char(char c, real_color_t f_color, real_color_t b_color)
{
    uint8_t attribute_byte = (b_color << 4) | (f_color & 0x0F);
    uint16_t ret = c | (attribute_byte << 8);
    return ret;
}

static void console_print_line(uint16_t *base_addr,
                               const char *msg,
                               real_color_t f_color,
                               real_color_t b_color)
{
    int end = 0;
    for (size_t i = 0; i < LEN_SINGLE_LINE; i++)
    {
        if (!end) // 没到要显示字符的结尾
        {
            char c = msg[i];
            end = (c == 0) ? 1 : 0;
            base_addr[i] = _atrr_char(c, f_color, b_color);
        }
        else
        {
            // 剩下的全部空格符号
            base_addr[i] = _atrr_char(
                ' ', DEFAULT_FOREGROUND_COLOR, DEFAULT_BACKGROUND_COLOR);
        }
    }
}

static void move_cursor(uint16_t x, uint16_t y)
{
    uint16_t cursor_location = y * LEN_SINGLE_LINE + x;

    // 在这里用到的两个内部寄存器的编号为14与15，分别表示光标位置
    // 的高8位与低8位。
    outb(0x3D4, 14);                   // 告诉 VGA 我们要设置光标的高字节
    outb(0x3D5, cursor_location >> 8); // 发送高 8 位
    outb(0x3D4, 15);                   // 告诉 VGA 我们要设置光标的低字节
    outb(0x3D5, cursor_location);      // 发送低 8 位
}

static void scroll_up_line(uint16_t line)
{
    // 还剩line行是空
    uint16_t cpy_lines = LEN_ROWS - 2 - line;
    if (cpy_lines > 0)
    {
        // 上滚是最简单的, 直接memcpy
        memcpy(VIDEO_MSG_START,
               VIDEO_T_STAT_START - cpy_lines * BYTE_SINGLE_LINE,
               cpy_lines * BYTE_SINGLE_LINE);
        s_cursor.curr -= line * LEN_SINGLE_LINE;
        s_cursor.x = 0;
        s_cursor.y -= line;
    }
    else
    {
        s_cursor.curr = VIDEO_MSG_START;
        s_cursor.x = 0;
        s_cursor.y = 1;
    }
    move_cursor(s_cursor.x, s_cursor.y);
    for (uint16_t *addr = VIDEO_MSG_START + cpy_lines * BYTE_SINGLE_LINE;
         addr < VIDEO_T_STAT_START; addr++)
    {
        // 全部空格符号
        *addr = _atrr_char(
            ' ', DEFAULT_FOREGROUND_COLOR, DEFAULT_BACKGROUND_COLOR);
    }
}
