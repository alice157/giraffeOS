#include <stdint.h>
#pragma once

#define KERNEL_LOAD_ADDR 0xC0000000
static inline void outb(uint16_t port, uint8_t val)
{
	__asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
	uint8_t ret;
	__asm__ volatile("inb %0, %1" : "=a"(ret) : "Nd"(port));
	return ret;
}

static inline uint32_t get_esp(void)
{
	uint32_t esp;
	__asm__ volatile(	".intel_syntax noprefix;"
										"mov eax, esp;"
										".att_syntax prefix;"
										: "=a"(esp));
	return esp;
}
