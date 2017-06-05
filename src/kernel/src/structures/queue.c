#include "structures/queue.h"

void kqueue_init(kqueue * queue, size_t element_size, uint16_t max_count)
{
	queue->elements = (void *)0x1000;
	queue->element_size = element_size;
	queue->count = 0;
	queue->max_count = max_count;
}
