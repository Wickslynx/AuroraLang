section .data
section .bss
section .text
global _start
_start:
strlen:
    mov rdx, 0
strlen_loop:
    cmp byte [rsi + rdx], 0
    je strlen_done
    inc rdx
    jmp strlen_loop
strlen_done:
    ret
print:
    mov rsi, rdi
    call strlen
    mov rax, 1
    mov rdi, 1
    syscall
    ret
    mov rax, 60
    xor rdi, rdi
    syscall
