#include "libc/stdio.h"
#include "video/video.h"

void kmain() {
    video_clear_screen();

    println("Kernel 32-bit pronto.");
    
    puts("Inteiro comum: ");
    puti(123456);
    
    puts("\nNegativo: ");
    puti(-789);

    video_putchar('\n', VIDEO_COLOR_WHITE_ON_BLACK);
}