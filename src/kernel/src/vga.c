#include "vga.h"

int strlen(uint8_t * string)
{
	int count = 0;
	while (string[count])
		count++;
	return count;
}

void kvga_write_string(uint8_t * string)
{
	size_t len = strlen(string);
	for (uint16_t i = 0; i < len; i++)
	{
		switch (string[i])
		{
			case '\n':
				kvga_advance_cursor(kvga_newline());
				break;
			case '\t':
			default:
				kvga_buffer[VGA_LOCATION] = kvga_entry(string[i], kvga_current_color);
				kvga_advance_cursor(1);
		}
	}
	kvga_update_cursor();
}

void kvga_init(uint8_t color)
{
	kvga_buffer = (uint16_t *)0xB8000;
	kvga_clear(color);
}

uint8_t kvga_color(uint8_t fg, uint8_t bg)
{
	return fg | (bg << 4);
}

uint16_t kvga_entry(uint8_t character, uint8_t color)
{
	return character | (color << 8);
}

void kvga_clear(uint8_t color)
{
	uint16_t clear_value = kvga_entry(' ', color);
	for (int y=0; y<VGA_HEIGHT; y++)
		for(int x=0; x<VGA_WIDTH; x++)
			kvga_buffer[y*VGA_WIDTH + x] = clear_value;
	kvga_set_color(color);
	kvga_set_cursor(0, 0);
}

void kvga_write_entry(uint16_t entry)
{
	kvga_buffer[kvga_cursor_y*VGA_WIDTH + kvga_cursor_x] = entry;
	kvga_advance_cursor(1);
	kvga_update_cursor();
}

void kvga_write_character(uint8_t character)
{
	kvga_buffer[kvga_cursor_y*VGA_WIDTH + kvga_cursor_x] = kvga_entry(character, kvga_current_color);
	kvga_advance_cursor(1);
	kvga_update_cursor();
}

void kvga_advance_cursor(int8_t dx)
{
	uint8_t x = (kvga_cursor_x + dx) % VGA_WIDTH;
	kvga_cursor_y = (kvga_cursor_y + (kvga_cursor_x + dx) / VGA_WIDTH) % VGA_HEIGHT;
	kvga_cursor_x = x;
}

void kvga_update_cursor(void)
{
	uint16_t position = kvga_cursor_y * VGA_WIDTH + kvga_cursor_x;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(position&0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)(position >> 8)&0xFF);
}

void kvga_set_cursor(uint8_t x, uint8_t y)
{
	kvga_cursor_x = x % VGA_WIDTH;
	kvga_cursor_y = y % VGA_HEIGHT;
	kvga_update_cursor();
}

void kvga_set_color(uint8_t color)
{
	kvga_current_color = color;
}

uint16_t kvga_newline(void)
{
	uint16_t advancement = 0;
	do
	{
		kvga_buffer[kvga_cursor_y * VGA_WIDTH + (advancement + kvga_cursor_x)] = kvga_entry(' ', kvga_current_color);
		advancement++;
	} while ((kvga_cursor_x + advancement) % VGA_WIDTH);
	kvga_cursor_y = 0;
	return advancement;
}

uint16_t kvga_tab(void)
{
	uint16_t spaces = 4 - (kvga_cursor_x % 4);
	for (int i = 0; i < spaces; i++)
		kvga_buffer[VGA_LOCATION + i] = kvga_entry(' ' , kvga_current_color);
	return spaces;
}
