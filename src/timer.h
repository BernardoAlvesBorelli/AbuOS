#ifndef TIMER_H
#define TIMER_H
#include "libc/stdint.h"

void init_timer(uint32_t frequency);
uint32_t get_ticks();
void timer_handler(); // Chamada pelo idt.c

#endif