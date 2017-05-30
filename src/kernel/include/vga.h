// lots of this adapted from http://wiki.osdev.org/Bare_Bones
#include <stdint.h>
#include <stddef.h>
#include "util.h"
#pragma once


#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_LOCATION (kvga_cursor_y*VGA_WIDTH)+kvga_cursor_x
enum kvga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

uint16_t * kvga_buffer;
uint16_t kvga_current_color;
uint8_t kvga_cursor_x;
uint8_t kvga_cursor_y;

void kvga_write_string(uint8_t * string);
void kvga_update_cursor();
void kvga_init(uint8_t color);
uint8_t kvga_color(uint8_t fg, uint8_t bg);
uint16_t kvga_entry(uint8_t character, uint8_t color);
void kvga_clear(uint8_t color);
void kvga_write_entry(uint16_t entry);
void kvga_advance_cursor(int8_t dx);
void kvga_set_cursor(uint8_t x, uint8_t y);
void kvga_set_color(uint8_t color);
void kvga_write_character(uint8_t character);
uint16_t kvga_newline(void);
