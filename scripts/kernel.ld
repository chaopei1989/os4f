/*
 *      kernel.ld -- 针对 kernel 格式所写的链接脚本
 */

ENTRY(start)
SECTIONS
{
    /* 段起始位置 */

    PROVIDE( kern_start = . );
    . = 0x100000; 
    .init.text : 
    {
        *(.init.text)
        . = ALIGN(4096);
    }
    .init.data : 
    {
        *(.init.data)
        . = ALIGN(4096);
    }

    /*. += 0xC0000000;*/

    .text : /* AT(ADDR(.text) - 0xC0000000) */
    {
        *(.text)
        . = ALIGN(4096);
    }

    .data :
    {
        *(.data)
        *(.rodata)
        . = ALIGN(4096);
    }

    .bss :
    {
        *(.bss)
        . = ALIGN(4096);
    }

    .stab :
    {
        *(.stab)
        . = ALIGN(4096);
    }
    
    .stabstr :
    {
        *(.stabstr)
        . = ALIGN(4096);
    }
    PROVIDE( kern_end = . );

    /DISCARD/ : { *(.comment) *(.eh_frame) }
}
