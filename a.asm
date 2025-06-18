global _start

section .text
_start:
	mov rax, 0x3c	; exit syscall
	mov rdi, 0
	syscall
