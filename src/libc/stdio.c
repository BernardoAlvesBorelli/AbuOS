#include "stdio.h"
#include "video/video.h"

void puts(const char* str) {
    video_print(str, VIDEO_COLOR_WHITE_ON_BLACK);
}

void println(const char* str) {
    puts(str);
    video_putchar('\n', VIDEO_COLOR_WHITE_ON_BLACK);
}

void puti(int n) {
    video_puti(n, VIDEO_COLOR_WHITE_ON_BLACK);
}

void panic(const char* message) {
    video_clear_screen();
    video_print("!!! KERNEL PANIC !!!\n", VIDEO_COLOR_RED_ON_BLACK);
    video_print("Erro: ", VIDEO_COLOR_RED_ON_BLACK);
    video_print(message, VIDEO_COLOR_WHITE_ON_BLACK);
    
    // Para o processador
    while(1) {
        __asm__("cli; hlt"); 
    }
}