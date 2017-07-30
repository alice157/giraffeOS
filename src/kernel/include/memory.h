#include <stddef.h>
#include <stdint.h>
#pragma once

#define HEAP_BASE 0x40000
#define CHUNKS 1024
#define PAGE_TABLE (void *)0xFFFFF000
typedef struct __attribute__((__packed__)) kmemchunkheader_s
{
	uint32_t flags;
	void * next_chunk;
	void * prev_chunk;
} kmemchunkheader;

typedef struct kmemchunk_s
{
	kmemchunkheader header;
	uint8_t memory[0x1000 << 10 - sizeof(kmemchunkheader)];
} kmemchunk;

void kinit_heap(void);

uint8_t map_page(void * phys, void * virt);
