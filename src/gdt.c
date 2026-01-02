#include "gdt.h"

struct gdt_entry gdt[3];
struct gdt_ptr gp;

// Função escrita em Assembly (dentro do boot.asm) para carregar a GDT
extern void gdt_flush(uint32_t);

void set_gdt_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access      = access;
}

void init_gdt() {
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base  = (uint32_t)&gdt;

    set_gdt_gate(0, 0, 0, 0, 0);                // Null segment
    set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment (Kernel)
    set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment (Kernel)

    gdt_flush((uint32_t)&gp);
}