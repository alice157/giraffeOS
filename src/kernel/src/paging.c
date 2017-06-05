#include "paging.h"
void kpage_directory_init(uint32_t * directory)
{
	for (int i = 0; i < 1024; i++)
		directory[i] = 0x00000002; //Address 0x00000000, RW, Kernel mode, not present
}

void kpage_table_init(uint32_t * table, size_t base_addr)
{
	for (int i = 0; i < 1024; i++)
		table[i] = (base_addr + i * 0x1000) | 3;
}

void kload_page_directory(uint32_t * directory)
{
	__asm__ volatile(	".intel_syntax noprefix;"
										"mov cr3, eax;"
										".att_syntax prefix;"
										:
										: "r" (directory));
}

void kenable_paging(void)
{
	__asm__ volatile( ".intel_syntax noprefix;"
										"mov eax, cr0;"
										"or eax, 0x80000000;"
										"mov cr0, eax;"
										".att_syntax prefix;");
}
