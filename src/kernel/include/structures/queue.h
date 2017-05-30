#include <stdint.h>
#pragma once

struct kps2_queue
{
	(void *)elements;
	size_t element_size;
	uint16_t count;
	uint16_t max_count;
}
