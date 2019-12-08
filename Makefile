CC = gcc
AS = nasm
GNUAS = as
DD = dd
LD = ld
PY = python3
QEMU = qemu-system-i386

ASFLAGS = -f elf
GNUASFLAGS = --32

CFLAGS += -m32 -fno-builtin -fno-omit-frame-pointer -fno-stack-protector \
-Wall -Wformat=2 -Wno-unused-function -fno-pie -I inc \

LDFLAGS = -m elf_i386

all: disk.img

qemu: disk.img
	$(QEMU) $< 

disk.img: obj/bootloader obj/kernel
	$(DD) if=/dev/zero of=$@ bs=512 count=10000
	$(DD) conv=notrunc if=obj/bootloader of=$@ bs=512 count=1 seek=0
	$(DD) conv=notrunc if=obj/kernel of=$@ bs=512 seek=1

obj/bootloader: obj/boot.o obj/main.o
	$(LD) $(LDFLAGS) -N -e start -Ttext 0x7C00 -o $@.out $^
	objdump -S $@.out > $@.asm
	objcopy -S -O binary -j .text $@.out $@
	$(PY) boot/verify.py

obj/kernel: obj/entry.o obj/init.o obj/string.o obj/assert.o obj/panic.o obj/video.o obj/stdio.o obj/p_paging.o obj/pic.o obj/gdt_idt_table.c.o obj/gdt_idt_table.s.o obj/interrupts.c.o obj/interrupts.s.o
	$(LD) $(LDFLAGS) -T kern/kernel.ld -o $@ $^

obj/entry.o: kern/entry.asm
	$(AS) $(ASFLAGS) $< -o $@

obj/gdt_idt_table.c.o: kern/gdt_idt_table.c
	$(CC) -nostdinc $(CFLAGS) -c -o $@ $<

obj/gdt_idt_table.s.o: kern/gdt_idt_table.s
	$(GNUAS) $(GNUASFLAGS) -o $@ $<

obj/interrupts.c.o: kern/interrupts.c
	$(CC) -nostdinc $(CFLAGS) -c -o $@ $<

obj/interrupts.s.o: kern/interrupts.s
	$(GNUAS) $(GNUASFLAGS) -o $@ $<

obj/pic.o: kern/pic.c
	$(CC) -nostdinc $(CFLAGS) -c -o $@ $<

obj/assert.o: kern/assert.c
	$(CC) -nostdinc $(CFLAGS) -c -o $@ $<

obj/panic.o: kern/panic.c
	$(CC) -nostdinc $(CFLAGS) -c -o $@ $<

obj/video.o: kern/video.c
	$(CC) -nostdinc $(CFLAGS) -c -o $@ $<

obj/string.o: lib/string.c
	$(CC) -nostdinc $(CFLAGS) -c -o $@ $<

obj/stdio.o: lib/stdio.c
	$(CC) -nostdinc $(CFLAGS) -c -o $@ $<

obj/p_paging.o: kern/p_paging.c
	$(CC) -nostdinc $(CFLAGS) -c -o $@ $<

obj/init.o: kern/init.c
	$(CC) -nostdinc $(CFLAGS) -c -o $@ $<

obj/main.o: boot/main.c
	$(CC) -nostdinc $(CFLAGS) -Os -c -o $@ $<

obj/boot.o: boot/boot.asm
	mkdir -p obj
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf disk.img obj/
