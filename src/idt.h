#ifndef IDT_H
#define IDT_H

#include "libc/stdint.h"

struct idt_entry {
    uint16_t base_low;
    uint16_t sel;        // Segmento de código (GDT)
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// Registradores passados para o tratador C quando ocorre uma exceção
struct regs {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // pusha
    uint32_t int_no, err_code;    // empurrados manualmente no asm
    uint32_t eip, cs, eflags, useresp, ss; // empurrados pelo processador
};

void init_idt();

#endif