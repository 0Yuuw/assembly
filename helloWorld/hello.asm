section .data
hello db 'Hello, World!',0xa
len equ $ - hello

section .text
global _start

_start:
mov rdx, len
mov rsi, hello
mov rdi, 1
mov rax, 1
syscall
mov rax, 60
xor rdi, rdi
syscall
