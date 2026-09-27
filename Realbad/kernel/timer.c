#include "timer.h"
#include "io.h"
#include "isr.h"
#include "pic.h"

#define PIT_CHANNEL0 0x40
#define PIT_COMMAND  0x43
#define PIT_HZ       1193182u

static volatile uint32_t ticks;

static void timer_callback(struct registers *regs)
{
    (void)regs;
    ticks++;
}

void timer_init(uint32_t hz)
{
    uint32_t divisor;
    uint8_t lo, hi;

    if (hz == 0) {
        hz = 100;
    }

    ticks = 0;
    irq_install_handler(0, timer_callback);

    divisor = PIT_HZ / hz;
    if (divisor == 0) {
        divisor = 1;
    }

    outb(PIT_COMMAND, 0x36);
    lo = (uint8_t)(divisor & 0xFF);
    hi = (uint8_t)((divisor >> 8) & 0xFF);
    outb(PIT_CHANNEL0, lo);
    outb(PIT_CHANNEL0, hi);

    pic_unmask(0);
}

uint32_t timer_ticks(void)
{
    return ticks;
}
