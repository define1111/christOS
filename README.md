# christOS
This is my simple operating system designed for self-education purposes.
Why such a strange name? Because you can be able to do something on system programming only with God's help.

## Features:
* bootloader switches from real-mode to protected-mode.
* bootloader reads any elf-i386 kernels

## How to use it?
0. Use this command to build the disk.img of OS:
```
make
```

1. Or that command for run OS in QEMU:
```
make qemu
```

2. Clean project from bin files:
```
make clean
```

## How it works?
Now it works too obvious.
