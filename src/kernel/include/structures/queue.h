#include <stdint.h>
#include <stddef.h>
#pragma once

typedef struct kqueue_s
{
	void * elements;
	size_t element_size;
	uint16_t count;
	uint16_t max_count;
} kqueue;

void kqueue_init(kqueue * queue, size_t element_size, uint16_t max_count);
