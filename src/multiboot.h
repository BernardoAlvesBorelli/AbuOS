#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include "libc/stdint.h"

struct multiboot_info {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t syms[4];
    uint32_t mmap_length;
    uint32_t mmap_addr;
    uint32_t drives_length;
    uint32_t drives_addr;
    uint32_t config_table;
    uint32_t boot_loader_name; // Ponteiro para string (se flag bit 9 estiver setado)
    // ... existem outros campos, mas estes bastam por enquanto
} __attribute__((packed));

#endif