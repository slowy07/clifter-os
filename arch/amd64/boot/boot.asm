MAGIC equ 0x1badb002
FLAGS equ (1<<0 | 1<<1)
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .text
extern kernelMain
extern callConstructors
global loader

loader:
    xor rbp, rbp
    add rbp, 1

wait_debugger:
    test rbp, rbp
    jz wait_debugger

    mov rsp, kernel_stack
    call callConstructors
    mov rdi, rax
    mov rsi, rbx
    call kernelMain

_stop:
    cli
    hlt
    jmp _stop

section .bss
reb 2*1024*1024
kernel_stack:
