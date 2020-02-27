#include <multiboot.h>
#include <printk.h>
#include <pmm.h>

void show_memory_map()
{
    printk("kernel in memory start: %x", kern_start);
    printk("kernel in memory end:   %x", kern_end);
    printk("kernel in memory used:  %d KB", (kern_end - kern_start) >> 10); // approx

    uint32_t mmap_addr = glb_mboot_ptr->mmap_addr;
    uint32_t mmap_length = glb_mboot_ptr->mmap_length;

    for (mmap_entry_t *mmap = (mmap_entry_t *)mmap_addr;
         (uint32_t)mmap < mmap_addr + mmap_length;
         mmap++)
    {
        // printk("Memory map:\n"
        //        "base_addr: H=%x, L=%x\n"
        //        "length: H=%x L=%x\n"
        //        "type=%x",
        //        mmap->base_addr_high, mmap->base_addr_low,
        //        mmap->length_high, mmap->l ength_low,
        //        mmap->type);
        printk("%x~%x, type=%d, about %dKB",
               mmap->base_addr_low,
               mmap->base_addr_low + mmap->length_low - 1,
               mmap->type,
               mmap->length_low >> 10);
    }
}

void init_pmm()
{
    // init free_areas
    for (uint32_t i = 0; i < MAX_ORDER; i++)
    {
        free_areas[i].free_list.next = NULL;
        free_areas[i].free_list.prev = NULL;
        free_areas[i].nr_free = 0;
    }
    // init all available memory segments
    uint32_t mmap_addr = glb_mboot_ptr->mmap_addr;
    uint32_t mmap_length = glb_mboot_ptr->mmap_length;

    for (mmap_entry_t *mmap = (mmap_entry_t *)mmap_addr;
         (uint32_t)mmap < mmap_addr + mmap_length;
         mmap++)
    {
        if (mmap->type == 1) 
        {
            // available memory 
            // 地址暂时仅32位就够了, 故只用到低位
            // memory begin: mmap->base_addr_low
            uint32_t mem_begin = mmap->base_addr_low;
            if ((PAGE_MASK & mem_begin) != mem_begin) 
            {
                // 正常来讲都是对齐了的
                mem_begin = (mem_begin + PAGE_SIZE) & PAGE_MASK;
            }
            // memory end(include): mmap->base_addr_low + mmap->length_low - 1
            uint32_t mem_end = (mmap->base_addr_low + mmap->length_low) & PAGE_MASK;
            uint32_t mem_len = mem_end - mem_begin;
            while (mem_len > 0)
            {
                for (uint32_t i = MAX_ORDER - 1; i >= 0; i--)
                {
                    uint32_t order_mem = 1 << i;
                    if (mem_len >= order_mem)
                    {
                        // free pages
                        free_pages(mem_begin, i);
                        mem_begin += order_mem;
                        mem_len -= order_mem;
                        break;
                    }
                    // else continue 试试低阶
                }
            }
        }
    }
}

void alloc_pages(int order)
{
    // TODO:
}

void free_pages(uint32_t addr, int order)
{
    struct list_head *page_head = &free_areas[order].free_list;
    while (1)
    {
        if ((page_head->next != NULL))
        {
            struct page *p = container_of(page_head->next, struct page, entry);
            if (addr < p->start_addr)
            {
                // 地址小于下一个, 直接插这儿
                list_add(&vir_to_page(addr)->entry, page_head);
                break;
            }
            else
            {
                page_head = page_head->next;
                // 看看下一个节点
            }
        }
        else
        {
            // 到最后了, 直接挂这儿
            list_add(&vir_to_page(addr)->entry, page_head);
            break;
        }
    }
    
}

void kmalloc()
{
    // TODO:
}

void kfree()
{
    // TODO:
}
