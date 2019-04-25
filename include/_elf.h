#ifndef INCLUDE_ELF_H_
#define INCLUDE_ELF_H_

#define ELF32_ST_TYPE(i) ((i)&0xf)

#include <types.h>

// ELF section head struct, 40bytes
typedef struct elf_section_header
{
    uint32_t name;
    uint32_t type;
    uint32_t flags;
    uint32_t addr;
    uint32_t offset;
    uint32_t size;
    uint32_t link;
    uint32_t info;
    uint32_t addralign;
    uint32_t entsize;
} __attribute__((packed)) elf_section_header_t;

// custom struct
// ELF symbol
typedef struct elf_symbol
{
    uint32_t name;
    uint32_t value;
    uint32_t size;
    uint8_t info;
    uint8_t other;
    uint16_t shndx;
} __attribute__((packed)) elf_symbol_t;

// custom struct
// ELF info
typedef struct elf
{
    elf_symbol_t *symtab;
    uint32_t symtabsz;
    const char *strtab;
    uint32_t strtabsz;
} elf_t;

#endif
