; Sintaxe Intel
bits 32

; Definições do Multiboot (Padrão para ser reconhecido pelo QEMU/GRUB)
MBOOT_PAGE_ALIGN    equ 1 << 0
MBOOT_MEM_INFO      equ 1 << 1
MBOOT_HEADER_MAGIC  equ 0x1BADB002
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

section .multiboot
    align 4
    dd MBOOT_HEADER_MAGIC
    dd MBOOT_HEADER_FLAGS
    dd MBOOT_CHECKSUM

section .bss
    align 16
    stack_bottom:
        resb 16384 ; Reserva 16 KB para a pilha
    stack_top:

section .text
    global _start
    extern kmain
    global gdt_flush

_start:
    mov esp, stack_top

    push ebx
    push eax

    call kmain

; Loop de segurança caso a kmain retorne
.hang:
    cli
    hlt
    jmp .hang

; Função de utilidade (chamada pelo C)
gdt_flush:
    mov eax, [esp + 4]
    lgdt [eax]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush
.flush:
    ret