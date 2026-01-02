#include "video/video.h"

void kmain() {
    video_clear_screen();
    
    video_print("Kernel de 32 bits carregado com sucesso!\n", VIDEO_COLOR_GREEN_ON_BLACK);
    video_print("Driver de video VGA: OK\n", VIDEO_COLOR_WHITE_ON_BLACK);
    video_print("Hello, World!", VIDEO_COLOR_WHITE_ON_BLACK);
}