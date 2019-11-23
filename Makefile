AS = nasm
DD = dd
PY = python3

ASFLAGS = -f bin

all: disk.img

qemu: disk.img
	qemu-system-i386 $< 

disk.img: obj/boot.o
	$(DD) if=/dev/zero of=$@ bs=512 count=10000
	$(DD) conv=notrunc if=obj/boot.o of=$@ bs=512 count=1 seek=0

obj/boot.o: boot/boot.asm boot/verify.py
	mkdir -p obj
	$(AS) $(ASFLAGS) $< -o $@
	$(PY) boot/verify.py

clean:
	rm -rf disk.img obj/
