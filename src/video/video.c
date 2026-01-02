#include "video.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000

static int cursor_x = 0;
static int cursor_y = 0;

void video_clear_screen() {
    unsigned short* buffer = (unsigned short*)VGA_ADDRESS;
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        buffer[i] = (unsigned short)' ' | (VIDEO_COLOR_WHITE_ON_BLACK << 8);
    }
    cursor_x = 0;
    cursor_y = 0;
}

void video_putchar(char c, unsigned char color) {
    unsigned short* buffer = (unsigned short*)VGA_ADDRESS;

    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        int index = (cursor_y * VGA_WIDTH) + cursor_x;
        buffer[index] = (unsigned short)c | (color << 8);
        cursor_x++;
    }

    // Scroll simples (se chegar no fim da tela, volta pro topo)
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= VGA_HEIGHT) {
        video_clear_screen(); // Limpa ao estourar a tela para simplificar
    }
}

void video_print(const char* str, unsigned char color) {
    for (int i = 0; str[i] != '\0'; i++) {
        video_putchar(str[i], color);
    }
}