#ifndef REALBAD_TIMER_H
#define REALBAD_TIMER_H

#include <stdint.h>

void timer_init(uint32_t hz);
uint32_t timer_ticks(void);

#endif
