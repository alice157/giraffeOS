#include <stdint.h>

#include "vga.h"

void kernel_main(void)
{
	kvga_init(kvga_color(VGA_COLOR_WHITE, VGA_COLOR_LIGHT_BLUE));
	kvga_write_string("ayy we didn't crash");
}
