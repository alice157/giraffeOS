#include <stddef.h>
#include <stdint.h>
#pragma once

typedef struct __attribute__((__packed__)) kmemchunkheader_s
{
	uint32_t flags;
	void * next_chunk;
	void * prev_chunk;
} kmemchunkheader;

typedef struct memchunk_s
{
	kmemchunkheader header;
	uint8_t memory[0x1000 << 10 - 4];
} memchunk;
