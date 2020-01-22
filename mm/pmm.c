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
        //        mmap->length_high, mmap->length_low,
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
    // TODO:
}

void alloc_page(int order)
{
    // TODO:
}

void free_page(uint32_t addr, int order)
{
    // TODO:
}

void kmalloc()
{
    // TODO:
}

void kfree()
{
    // TODO:
}
