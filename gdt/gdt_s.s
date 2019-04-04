[GLOBAL gdt_flush]  
[EXTERN print_cur_status]

gdt_flush:
    mov eax, [esp+4]    ; 参数存入 eax 寄存器
    lgdt [eax]          ; 加载到 GDTR [修改原先GRUB设置]

    mov ax, 0x08        ; 加载我们的数据段描述符
    mov ds, ax          ; 更新所有可以更新的段寄存器
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov eax, cr0        ; CR0 最低位置为0
    or eax, 0x1
    mov cr0, eax

    in al, 92h          ; A20, 开启之后恐怕跳转就会失败
    or al, 00000010b
    out 92h, al

    jmp 0x10:.flush     ; 远跳转， 0x08 是我们的代码段描述符
                        ; 远跳目的是清空流水线并串行化处理器
.flush:
    ; call print_cur_status
    ret