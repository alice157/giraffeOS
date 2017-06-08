#include "util.h"

void memdump(uint32_t * src, uint16_t size)
{
	for (uint16_t i = 0; i < size; i++)
	{
		kvga_write_string("0x");
		kvga_write_string(itoa(src + i, 16));
		kvga_write_string("  0x");
		kvga_write_string(itoa(src[i], 16));
		kvga_write_string(i && !(i%4) ? "\n" : "\t");
	}
}
