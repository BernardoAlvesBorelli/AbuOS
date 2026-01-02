#ifndef VIDEO_H
#define VIDEO_H

#include "libc/stdint.h" // <--- ADICIONE ISSO

#define VIDEO_COLOR_WHITE_ON_BLACK 0x0F
#define VIDEO_COLOR_GREEN_ON_BLACK 0x0A
#define VIDEO_COLOR_RED_ON_BLACK   0x0C

void video_clear_screen();
void video_putchar(char c, unsigned char color);
void video_print(const char* str, unsigned char color);
void video_puti(int n, unsigned char color);
void video_puth(uint32_t n, unsigned char color);

#endif