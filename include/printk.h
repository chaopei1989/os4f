#ifndef INCLUDE_PRINTK_H_
#define INCLUDE_PRINTK_H_

/**
 * 格式化输出msg到屏幕
 */ 
void printk(char *fmt, ...);

/**
 * 格式化输出到指定buff
 */ 
void printk_buff(char *buff, int len, int buff_offset, char *fmt, ...);

void print_cur_status();

#endif // INCLUDE_PRINTK_H_
