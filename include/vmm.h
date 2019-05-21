#ifndef INCLUDE_VMM_H_
#define INCLUDE_VMM_H_

#include<types.h>

// 页目录数据类型
typedef uint32_t pgd_t;

// 页表数据类型
typedef uint32_t pte_t;

int enable_paging();

#endif
