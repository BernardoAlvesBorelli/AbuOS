#include "libc/stdio.h"
#include "video/video.h"
#include "multiboot.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "keyboard.h"

void kmain(uint32_t magic, struct multiboot_info* mbi) {
    video_clear_screen();
    
    if (magic != 0x2BADB002) panic("Multiboot Magic invalido!");

    init_gdt();
    init_idt();
    init_timer(100); 

    println("GDT, IDT e Timer (100Hz) configurados.");
    
    // Usa o mbi para evitar o warning
    if (mbi->flags & (1 << 9)) {
        puts("Bootloader: ");
        println((const char*)mbi->boot_loader_name);
    }

    println("Sistema pronto (IRQ Segura).");

    static uint32_t last_tick = 0;

    while(1) {
        // 1. Processa Teclado (Contexto de Kernel, não de IRQ)
        char c = keyboard_getchar();
        if (c > 0) {
            video_putchar(c, VIDEO_COLOR_WHITE_ON_BLACK);
        }

        // 2. Lógica do Spinner
        uint32_t current_tick = get_ticks();
        if (current_tick != last_tick) {
            static char *spinner = "/-\\|";
            unsigned short* video_mem = (unsigned short*)0xB8000;
            // Protegemos a escrita direta do spinner
            __asm__ volatile("cli");
            video_mem[79] = (unsigned short)spinner[current_tick % 4] | (0x0A << 8);
            __asm__ volatile("sti");
            last_tick = current_tick;
        }

        __asm__ volatile("hlt");
    }
}