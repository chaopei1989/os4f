#!Makefile

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))

CC = gcc
LD = ld
ASM = nasm

LOOP_DEV = /dev/loop30

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include -fno-pie
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib
ASM_FLAGS = -f elf -g -F stabs

all: $(S_OBJECTS) $(C_OBJECTS) link 

.c.o:
	@echo 编译代码文件 $< ...
	$(CC) $(C_FLAGS) $< -o $@

.s.o:
	@echo 编译汇编文件 $< ...
	$(ASM) $(ASM_FLAGS) $<

link:
	@echo 链接内核文件...
	$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o kernel.bin

.PHONY:clean
clean:
	$(RM) $(S_OBJECTS) $(C_OBJECTS) kernel.bin

.PHONY:update_image
update_image:
	sudo losetup -o 1048576 $(LOOP_DEV) hda_32M.img
	sudo mount $(LOOP_DEV) mnt/
	sudo cp kernel.bin mnt/boot/kernel.bin
	sleep 1
	sudo umount mnt
	sudo losetup -d $(LOOP_DEV)

.PHONY:qemu
qemu:
	sudo qemu-system-i386 -hda hda_32M.img -m 32M

.PHONY:qemu-curses
qemu-curses:
	sudo qemu-system-i386 -hda hda_32M.img -curses -m 32M

.PHONY:debug-qemu
debug-qemu:
	sudo qemu-system-i386 -s -S -kernel kernel.bin -hda hda_32M.img -m 32M

.PHONY:debug-qemu-curses
debug-qemu-curses:
	sudo qemu-system-i386 -S -kernel kernel.bin -hda hda_32M.img -m 32M

.PHONY:kill
kill:
	ps -ef | grep qemu | grep -v grep | awk '{print $$2}'|xargs sudo kill -9
