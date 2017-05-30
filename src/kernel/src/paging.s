.section .data

.section .text
.global create_page_table
create_page_table:
	movl 8, %ecx
top:
	movl $1024, %eax
	movl $0x02, %(ecx)
	dec %eax
	inc %ecx
	cmp $0, %eax
	jnz top
