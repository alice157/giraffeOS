# GiraffeOS
## An Experimental Microkernal in C
### Current Status: `It boots, and has a rudimentary vga text-mode driver`

GiraffeOS is currently under heavy development, and is currently not ready for 
general use (not that it's intended to be!).

Todo:
- [x] Make it boot
- [x] Basic VGA text support
- [ ] Paging
- [ ] Switch to NASM
- [ ] Improve build tooling to make it easier to include assembly
- [ ] Software and hardware interupts (add a few syscalls)
- [ ] malloc() and beginnings of memory management (most work is expected to take place here)
- [ ] Begin keeping track of processes
- [ ] ELF loading (will be precompiled in to binary to get around the lack of FS)
- [ ] Userspace PS/2 Keyboard driver
- [ ] fork()
- [ ] Userspace FAT16 driver
- [ ] Improve build tooling to generate a usable hard disk image
- [ ] Extremely basic shell
