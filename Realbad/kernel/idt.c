#include "idt.h"
#include "gdt.h"
#include "isr.h"
#include "string.h"

struct idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

extern void idt_load(uint32_t idtr_ptr);

static struct idt_entry idt[256];
static struct idt_ptr   idtr;

void idt_set_gate(uint8_t num, uint32_t handler, uint16_t selector, uint8_t flags)
{
    idt[num].base_low  = (uint16_t)(handler & 0xFFFF);
    idt[num].base_high = (uint16_t)((handler >> 16) & 0xFFFF);
    idt[num].selector  = selector;
    idt[num].always0   = 0;
    idt[num].flags     = flags;
}

void idt_init(void)
{
    memset(idt, 0, sizeof(idt));

    idtr.limit = (uint16_t)(sizeof(idt) - 1);
    idtr.base  = (uint32_t)&idt;

    isr_install();

    idt_load((uint32_t)&idtr);
}
