#ifndef REALBAD_IDT_H
#define REALBAD_IDT_H

#include <stdint.h>

void idt_set_gate(uint8_t num, uint32_t handler, uint16_t selector, uint8_t flags);
void idt_init(void);

#endif
