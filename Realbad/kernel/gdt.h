#ifndef REALBAD_GDT_H
#define REALBAD_GDT_H

#include <stdint.h>

#define GDT_CODE_SELECTOR 0x08
#define GDT_DATA_SELECTOR 0x10

void gdt_init(void);

#endif
