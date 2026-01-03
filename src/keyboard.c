#include "keyboard.h"
#include "libc/io.h"

static unsigned char kbd_us[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0, '*',
    0, ' ', 0
};

#define KBD_BUFFER_SIZE 256
static volatile char key_buffer[KBD_BUFFER_SIZE];
static volatile uint32_t head = 0;
static volatile uint32_t tail = 0;

void keyboard_handler() {
    uint8_t scancode = inb(0x60);
    
    if (!(scancode & 0x80)) { // Make code
        char c = kbd_us[scancode];
        if (c > 0) {
            uint32_t next = (head + 1) % KBD_BUFFER_SIZE;
            if (next != tail) { // Só insere se o buffer não estiver cheio
                key_buffer[head] = c;
                head = next;
            }
        }
    }
}

char keyboard_getchar() {
    if (head == tail) return 0; // Vazio
    
    char c = key_buffer[tail];
    tail = (tail + 1) % KBD_BUFFER_SIZE;
    return c;
}