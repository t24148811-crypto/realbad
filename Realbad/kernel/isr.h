#ifndef REALBAD_ISR_H
#define REALBAD_ISR_H

#include <stdint.h>

struct registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

typedef void (*irq_handler_t)(struct registers *regs);

void isr_install(void);
void irq_install_handler(uint8_t irq, irq_handler_t handler);

void isr_handler(struct registers *regs);
void irq_handler(struct registers *regs);

#endif
