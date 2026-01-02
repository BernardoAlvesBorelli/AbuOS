#ifndef VIDEO_H
#define VIDEO_H

// Cores padrão VGA
#define VIDEO_COLOR_WHITE_ON_BLACK 0x0F
#define VIDEO_COLOR_GREEN_ON_BLACK 0x0A

void video_clear_screen();
void video_putchar(char c, unsigned char color);
void video_print(const char* str, unsigned char color);

#endif