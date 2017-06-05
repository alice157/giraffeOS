#include <stdint.h>
#include <stddef.h>
#pragma once


/* PD Entry
 * 31-12 	-> Address of table, last 12 bits cut off (4096 aligned!)
 * 11-9		-> OS Available
 * 8			-> Ignored
 * 7			-> Page size, 0->4KiB, 1->4MiB (PSE must be enabled)
 * 6			-> Must be 0
 * 5			-> Accessed bit, not MMU-managed
 * 4			-> Cache disabled
 * 3			-> 0->Writethrough caching, 1->Writeback caching
 * 2			-> 1->All can access, 0->Supervisor only
 * 1			-> 0->Read only, 1->RW, depends on WP bit in CR0
 * 0			-> Present (in memory)
 */

/* PT Entry
 * 31-12	-> Address of page, last 12 bits cut off (4096 aligned!)
 * 11-9		-> OS Available
 * 8			-> Global bit, avoid flushing in TLB (page pinning, set global bit in CR4)
 * 7			-> Must be 0
 * 6			-> Dirty bit, not MMU managed
 * 5			-> Accessed bit
 * 4			-> Cache disabled
 * 3			-> Write-through caching, see PD
 * 2			-> User/Supervisor, see PD
 * 1			-> RW, see PD
 * 0			-> Present
 */
// directory MUST be page aligned (4096 bytes!)
void kpage_directory_init(uint32_t * directory);
void kpage_table_init(uint32_t * table, size_t base_addr);
void kload_page_directory(uint32_t * directory);
void kenable_paging(void);
