#include "memory.c"

void kinit_heap(void)
{
	void * prev_chunk = 0;
	for(int i = 0; i < CHUNKS; i++)
	{
		*(kmemchunk *)(HEAP_BASE + i * sizeof(kmemchunk)) = {.header = (kmemchunkheader)(.flags = 0, .next_chunk = (prev_chunk + 2(sizeof(kmemchunk))) * (i < (CHUNKS - 1)), .prev_chunk = prev_chunk)};
		prev_chunk += sizeof(kmemchunk);
	}
}

uint8_t map_page(void * phys, void * virt)
{
	if (phys & 0xFFC00000 != phys || virt & 0xFFC00000 != virt)
		return 2;
	// 1 means the page exists, 2 means one of the addresses isn't 4MB aligned
	int page = PAGE_TABLE + virt/0x40000
	if ((PAGE_TABLE + page * 4) & 1)
 		return 1;
	(PAGE_TABLE + page * 4) = phys | 0x00000083;
	__asm__ volatile(".intel_syntax noprefix;"
									 "invlpg %0;"
									 ".att_syntax prefix;"
									 : : "a"(phys));
}

