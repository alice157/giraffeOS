global _loader
extern kernel_main
MBALIGN equ 1<<0
MEMINFO equ 1<<1
FLAGS	equ MBALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

KERNEL_VIRTUAL_BASE equ 0xC0000000
KERNEL_PAGE_NUMBER equ (KERNEL_PAGE_NUMBER >> 22) ; divides by 1 << 22, 4MB

section .data
align (0x1000)
BootPageDirectory:
	dd 0x00000083 ; Identity map first 4MB of physical space
	times 767 dd 0x00000000 ; Blank out all the other pages
	dd 0x00000083 ; Map 4MB from 0x00000000 to 0xC0000000 (calculated by page)
	times 255 dd 0 ; Blank out more pages

align(0x1000)

section .text
MultiBootHeader:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

STACKSIZE equ 0x4000 ;16KB initial stack

_loader:
	mov ecx, (BootPageDirectory - KERNEL_VIRTUAL_BASE) ; set page directory address
	mov cr3, ecx

	mov ecx, cr4
	or ecx, 0x00000010 ; enable 4MB pages, no page table needed
	mov cr4, ecx

	mov ecx, (BootPageDirectory - KERNEL_VIRTUAL_BASE)
	and ecx, 0xFFFFF000
	or ecx, 0x00000083
	mov [BootPageDirectory - KERNEL_VIRTUAL_BASE + 1023*4], ecx

	mov ecx, cr0
	or ecx, 0x80000001 ; enable paging
	mov cr0, ecx
	lea ecx, [StartInHigherHalf]
	jmp ecx

StartInHigherHalf:
	mov dword [BootPageDirectory], 0 ;undo the indentity map, we don't need it anymore
	invlpg [0] ; remove page from cache
	invlpg [1023 * 4]
	mov esp, stack+STACKSIZE
	push eax ; Multiboot magic number
	push ebx ; Multiboot info structure (may not be in first 4MB TODO: fix this)

	call kernel_main
hang:
	hlt ; Should never reach this point but whatever
	jmp hang

section .bss
align 32
stack:
	resb STACKSIZE
