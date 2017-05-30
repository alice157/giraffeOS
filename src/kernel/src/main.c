#include <stdint.h>

#include "vga.h"

void kernel_main(void)
{
	uint8_t * tab_test = "A\tAA\tAAA\tAAAA\nAAAA\tAAA\tAA\tA\n\0";
	kvga_init(kvga_color(VGA_COLOR_WHITE, VGA_COLOR_LIGHT_BLUE));
	kvga_write_string((uint8_t *)"Hello World\nNewline Test\n\0");
	kvga_write_string(tab_test);
}
