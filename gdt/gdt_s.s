[GLOBAL gdt_flush]
[GLOBAL x86_get_pc]
[EXTERN print_cur_status]

gdt_flush:
    push    eax            ; save eax

    mov     eax, [esp+8]   ; 参数存入 eax 寄存器
    lgdt    [eax]          ; 加载到 GDTR [修改原先GRUB设置]

    mov     ax, 0x10       ; 加载数据段描述符 0x10
    mov     ds, ax         ; 更新所有可以更新的段寄存器
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax

    pop     eax            ; restore eax
    jmp     0x8:.flush         ; 远跳转， 0x08 代码段描述符
                           ; 远跳目的是清空流水线并串行化处理器

.flush:
    ; call print_cur_status
    ret

x86_get_pc:
    mov     eax, DWORD [esp]
    ret
