#ifndef INCLUDE_PRINTK_H_
#define INCLUDE_PRINTK_H_

/**
 * 格式化输出msg到屏幕
 */ 
void printk(char *fmt, ...);

/**
 * 格式化输出到指定buff
 */ 
void printk_buff(char *buff, int32_t len, int32_t buff_offset, char *fmt, ...);

/**
 * 打印当前的程序运行状态（各大寄存器，栈顶栈底）
 */ 
void print_cur_status();

#endif // INCLUDE_PRINTK_H_
