#ifndef INCLUDE_VMM_H_
#define INCLUDE_VMM_H_

#include<types.h>

/**
 *  mem offset used by kernel after paging.
 */
#define PAGE_OFFSET     0x0 // 0xC0000000

#define PAGING(addr) (PAGE_OFFSET + addr)

/**
 * For pgd or pte, low 0(P) bit refer to whether vm available.
 * 1 is available, 0 is unavailable.
 * If P bit is 0 when paging, PAGE_FAULT interrupt occur.
 * 在页转换过程中，如果说涉及的页目录或页表的表项无效，则会导致一个异常。
 * 如果 P = 0 ，那么除表示表项无效外，其余位可供程序自由使用。
 * 例如，操作系统可以使用这些位来保存已存储在磁盘上的页面的序号。
 */
#define PAGE_PRESENT    0x1

/** 
 * R/W -- 位 1 是读 / 写 (Read/Write) 标志。如果等于 1 ，表示页面可以被读、写或执行。
 * 如果为 0 ，表示页面只读或可执行。
 * 当处理器运行在超级用户特权级 （级别 0,1 或 2） 时，则 R/W 位不起作用。
 * 页目录项中的 R/W 位对其所映射的所有页面起作用。
 */
#define PAGE_WRITE  0x2

/**
 * U/S -- 位 2 是用户 / 超级用户 (User/Supervisor) 标志。
 * 如果为 1 ，那么运行在任何特权级上的程序都可以访问该页面。
 * 如果为 0 ，那么页面只能被运行在超级用户特权级 (0,1 或 2) 上的程序访问。
 * 页目录项中的 U/S 位对其所映射的所有页面起作用。
 */
#define PAGE_USER   0x4

// 虚拟分页大小
#define PAGE_SIZE   4096

// 页掩码，用于 4KB 对齐
#define PAGE_MASK      0xFFFFF000

// 页目录数据类型
typedef uint32_t pgd_t;

// 页表数据类型
typedef uint32_t pte_t;

#define INDEX_PGD(addr) (((addr) >> 22) & 0x3FF)

#define INDEX_PTE(addr) (((addr) >> 12) & 0x3FF)

#endif
