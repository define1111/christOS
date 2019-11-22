AS = nasm
DD = dd

ASFLAGS = -f bin

all: disk.img

qemu: disk.img
	qemu-system-i386 disk.img

disk.img: boot/boot.o
	$(DD) if=/dev/zero of=disk.img bs=512 count=10000
	$(DD) conv=notrunc if=obj/boot.o of=disk.img bs=512 count=1 seek=0

boot/boot.o: boot/boot.asm
	$(AS) $(ASFLAGS) boot/boot.asm -o obj/boot.o
