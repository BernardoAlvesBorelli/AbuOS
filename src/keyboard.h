#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "libc/stdint.h"

void keyboard_handler(); // Chamada pelo idt.c
char keyboard_getchar(); // Chamada pelo kmain (Thread context)

#endif