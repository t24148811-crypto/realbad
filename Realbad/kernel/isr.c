#include "isr.h"
#include "idt.h"
#include "gdt.h"
#include "pic.h"
#include "vga.h"

#define IDT_INTERRUPT_GATE 0x8E

extern void isr0(void);  extern void isr1(void);  extern void isr2(void);  extern void isr3(void);
extern void isr4(void);  extern void isr5(void);  extern void isr6(void);  extern void isr7(void);
extern void isr8(void);  extern void isr9(void);  extern void isr10(void); extern void isr11(void);
extern void isr12(void); extern void isr13(void); extern void isr14(void); extern void isr15(void);
extern void isr16(void); extern void isr17(void); extern void isr18(void); extern void isr19(void);
extern void isr20(void); extern void isr21(void); extern void isr22(void); extern void isr23(void);
extern void isr24(void); extern void isr25(void); extern void isr26(void); extern void isr27(void);
extern void isr28(void); extern void isr29(void); extern void isr30(void); extern void isr31(void);

extern void irq0(void);  extern void irq1(void);  extern void irq2(void);  extern void irq3(void);
extern void irq4(void);  extern void irq5(void);  extern void irq6(void);  extern void irq7(void);
extern void irq8(void);  extern void irq9(void);  extern void irq10(void); extern void irq11(void);
extern void irq12(void); extern void irq13(void); extern void irq14(void); extern void irq15(void);

static irq_handler_t irq_handlers[16];

static const char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating-Point",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point",
    "Virtualization",
    "Control Protection",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection",
    "VMM Communication",
    "Security",
    "Reserved"
};

void isr_install(void)
{
    idt_set_gate(0,  (uint32_t)isr0,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(1,  (uint32_t)isr1,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(2,  (uint32_t)isr2,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(3,  (uint32_t)isr3,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(4,  (uint32_t)isr4,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(5,  (uint32_t)isr5,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(6,  (uint32_t)isr6,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(7,  (uint32_t)isr7,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(8,  (uint32_t)isr8,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(9,  (uint32_t)isr9,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(10, (uint32_t)isr10, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(11, (uint32_t)isr11, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(12, (uint32_t)isr12, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(13, (uint32_t)isr13, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(14, (uint32_t)isr14, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(15, (uint32_t)isr15, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(16, (uint32_t)isr16, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(17, (uint32_t)isr17, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(18, (uint32_t)isr18, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(19, (uint32_t)isr19, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(20, (uint32_t)isr20, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(21, (uint32_t)isr21, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(22, (uint32_t)isr22, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(23, (uint32_t)isr23, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(24, (uint32_t)isr24, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(25, (uint32_t)isr25, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(26, (uint32_t)isr26, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(27, (uint32_t)isr27, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(28, (uint32_t)isr28, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(29, (uint32_t)isr29, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(30, (uint32_t)isr30, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(31, (uint32_t)isr31, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);

    idt_set_gate(32, (uint32_t)irq0,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(33, (uint32_t)irq1,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(34, (uint32_t)irq2,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(35, (uint32_t)irq3,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(36, (uint32_t)irq4,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(37, (uint32_t)irq5,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(38, (uint32_t)irq6,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(39, (uint32_t)irq7,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(40, (uint32_t)irq8,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(41, (uint32_t)irq9,  GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(42, (uint32_t)irq10, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(43, (uint32_t)irq11, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(44, (uint32_t)irq12, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(45, (uint32_t)irq13, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(46, (uint32_t)irq14, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    idt_set_gate(47, (uint32_t)irq15, GDT_CODE_SELECTOR, IDT_INTERRUPT_GATE);

    for (int i = 0; i < 16; i++) {
        irq_handlers[i] = 0;
    }
}

void irq_install_handler(uint8_t irq, irq_handler_t handler)
{
    if (irq < 16) {
        irq_handlers[irq] = handler;
    }
}

void isr_handler(struct registers *regs)
{
    vga_set_color(vga_entry_color(VGA_LIGHT_RED, VGA_BLACK));
    vga_write("\nCPU exception: ");
    if (regs->int_no < 32) {
        vga_write(exception_messages[regs->int_no]);
    }
    vga_write("\n");
    vga_set_color(vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK));

    for (;;) {
        __asm__ volatile ("cli; hlt");
    }
}

void irq_handler(struct registers *regs)
{
    uint8_t irq = (uint8_t)(regs->int_no - 32);

    if (irq < 16 && irq_handlers[irq]) {
        irq_handlers[irq](regs);
    }

    pic_send_eoi(irq);
}
