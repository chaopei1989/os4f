#ifndef INCLUDE_PAGE_H_
#define INCLUDE_PAGE_H_

#include<list.h>

#define PAGE_SHIFT      12

#define PAGE_SIZE       (1 << PAGE_SHIFT)

// 页掩码，用于 4KB 对齐
#define PAGE_MASK      0xFFFFF000

struct page {
    // 该页的初始物理地址
    uint32_t start_addr;
    // 挂list用的
    struct list_head entry;
};

#endif
