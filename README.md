# christOS
This is my simple operating system designed for self-education purposes.
Why such a strange name? Because you can be able to do something on system programming only with God's help.

## Features:
* bootloader reads and loads any elf32-i386 kernels
* bootloader switches from real-mode to protected-mode
* hello-world kernel
* console done (simplest video driver)

## How to use it?
0. Use this command to build the disk.img of OS:
```
$ make
```

1. Or that command for run OS in QEMU:
```
$ make qemu
```

2. Clean project from bin files:
```
$ make clean
```

## How it works?
Now it works too obvious.

## References:
* JOS
* MINIX 3
* github.com/ArseniyBorezkiy/oc-kernel/
* https://subscribe.ru/archive/comp.soft.myosdev/
