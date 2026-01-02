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