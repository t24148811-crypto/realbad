#ifndef REALBAD_PIC_H
#define REALBAD_PIC_H

#include <stdint.h>

#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1
#define PIC_EOI      0x20

void pic_remap(uint8_t offset1, uint8_t offset2);
void pic_send_eoi(uint8_t irq);
void pic_mask(uint8_t irq);
void pic_unmask(uint8_t irq);

#endif
