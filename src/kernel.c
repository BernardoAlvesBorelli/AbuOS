#include "libc/stdio.h"
#include "video/video.h"
#include "multiboot.h"
#include "gdt.h"

void kmain(uint32_t magic, struct multiboot_info* mbi) {
    video_clear_screen();

    if (magic != 0x2BADB002) panic("Multiboot Magic invalido!");

    // Inicializa a GDT
    init_gdt();
    println("GDT inicializada.");

    if (mbi->flags & (1 << 0)) {
        puts("Memoria RAM detectada: ");
        // mem_upper está em KB. Convertendo para MB para ler melhor.
        puti((mbi->mem_upper / 1024) + 1); 
        println(" MB");
    }

    if (mbi->flags & (1 << 9)) {
        puts("Bootloader: ");
        println((const char*)mbi->boot_loader_name);
    }

    println("Sistema estavel e em modo protegido.");
}