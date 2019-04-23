#include <_elf.h>
#include <multiboot.h>
#include <printk.h>

// 从 multiboot_t 结构获取ELF信息
elf_t elf_from_multiboot(multiboot_t *mb)
{
    elf_t elf;
    printk("multiboot_t section num:%d\n"
           "multiboot_t section size(per):%d\n"
           "multiboot_t section addr(start):%x\n"
           "multiboot_t section shndx(index):%x",
           mb->num, mb->size, mb->addr, mb->shndx);
    elf_section_header_t *headsptr = (elf_section_header_t *)mb->addr;
    // .shstrtab section
    elf_section_header_t *shstrtabptr = headsptr + mb->shndx;
    for (size_t i = 0; i < mb->num; i++)
    {
        const char *name = (const char *)(shstrtabptr->addr + headsptr[i].name);
        printk("section name: %s", name);
        if (strcmp(name, ".strtab") == 0)
        {
            elf.strtab = (const char *)headsptr[i].addr;
            elf.strtabsz = headsptr[i].size;
        }
        else if (strcmp(name, ".symtab") == 0)
        {
            elf.symtab = (elf_symbol_t *)headsptr[i].addr;
            elf.symtabsz = headsptr[i].size;
        }
    }
    return elf;
}

// 查看ELF的符号信息
const char *elf_lookup_symbol(uint32_t addr, elf_t *elf)
{
    return NULL;
}
