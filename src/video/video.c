#include "video.h"
#include "libc/io.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000

static int cursor_x = 0;
static int cursor_y = 0;
static volatile int vga_lock = 0;

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
    } else if (c == '\b') {
        if (cursor_x > 0) cursor_x--;
        // Opcional: limpar o caractere visualmente
        buffer[(cursor_y * VGA_WIDTH) + cursor_x] = (unsigned short)' ' | (color << 8);
    } else {
        buffer[(cursor_y * VGA_WIDTH) + cursor_x] = (unsigned short)c | (color << 8);
        cursor_x++;
    }

    if (cursor_x >= VGA_WIDTH) { cursor_x = 0; cursor_y++; }
    if (cursor_y >= VGA_HEIGHT) {
        // Por enquanto, apenas reseta o cursor em vez de scroll pesado
        cursor_x = 0;
        cursor_y = 0;
    }
}

void video_print(const char* str, unsigned char color) {
    for (int i = 0; str[i] != '\0'; i++) {
        video_putchar(str[i], color);
    }
}

void video_puti(int n, unsigned char color) {
    if (n == 0) { video_putchar('0', color); return; }
    if (n < 0) { video_putchar('-', color); n = -n; }
    char buffer[12];
    int i = 0;
    while (n > 0) { buffer[i++] = (n % 10) + '0'; n /= 10; }
    while (--i >= 0) { video_putchar(buffer[i], color); }
}

void video_puth(uint32_t n, unsigned char color) {
    char *chars = "0123456789ABCDEF";
    video_print("0x", color);
    for (int i = 28; i >= 0; i -= 4) {
        video_putchar(chars[(n >> i) & 0xF], color);
    }
}