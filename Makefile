CC = gcc
AS = nasm
DD = dd
LD = ld
PY = python3
QEMU = qemu-system-i386

ASFLAGS = -f elf

CFLAGS += -m32 -fno-builtin -fno-omit-frame-pointer -fno-stack-protector
CFLAGS += -Wall -Wformat=2 -Wno-unused-function -Werror
CFLAGS += -fno-pie -I inc 

LDFLAGS = -m elf_i386

all: disk.img

qemu: disk.img
	$(QEMU) $< 

disk.img: obj/bootloader
	$(DD) if=/dev/zero of=$@ bs=512 count=10000
	$(DD) conv=notrunc if=obj/bootloader of=$@ bs=512 count=1 seek=0

obj/bootloader: obj/boot.o obj/main.o
	$(LD) $(LDFLAGS) -N -e start -Ttext 0x7C00 -o $@.out $^
	objdump -S $@.out > $@.asm
	objcopy -S -O binary -j .text $@.out $@
	$(PY) boot/verify.py

obj/main.o: boot/main.c
	$(CC) -nostdinc $(CFLAGS) -Os -c -o $@ $<

obj/boot.o: boot/boot.asm boot/verify.py
	mkdir -p obj
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf disk.img obj/
