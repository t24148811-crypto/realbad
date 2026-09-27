#include <stdint.h>
#include "keyboard.h"
#include "io.h"
#include "isr.h"
#include "pic.h"

#define KBD_DATA_PORT   0x60
#define KBD_BUFFER_SIZE 256

static volatile char kbd_buf[KBD_BUFFER_SIZE];
static volatile uint8_t kbd_head;
static volatile uint8_t kbd_tail;
static int shift_down;
static int extended;

static const char keymap[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};

static const char keymap_shift[128] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
    0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*', 0, ' '
};

static void kbd_push(char c)
{
    uint8_t next = (uint8_t)((kbd_head + 1) % KBD_BUFFER_SIZE);
    if (next != kbd_tail) {
        kbd_buf[kbd_head] = c;
        kbd_head = next;
    }
}

static void keyboard_callback(struct registers *regs)
{
    uint8_t sc;
    (void)regs;

    sc = inb(KBD_DATA_PORT);

    if (sc == 0xE0) {
        extended = 1;
        return;
    }

    if (extended) {
        extended = 0;
        return;
    }

    if (sc == 0x2A || sc == 0x36) {
        shift_down = 1;
        return;
    }
    if (sc == 0xAA || sc == 0xB6) {
        shift_down = 0;
        return;
    }

    if (sc & 0x80) {
        return;
    }

    if (sc < 128) {
        char c = shift_down ? keymap_shift[sc] : keymap[sc];
        if (c) {
            kbd_push(c);
        }
    }
}

void keyboard_init(void)
{
    kbd_head = 0;
    kbd_tail = 0;
    shift_down = 0;
    extended = 0;
    irq_install_handler(1, keyboard_callback);
    pic_unmask(1);
}

char keyboard_getchar(void)
{
    while (kbd_head == kbd_tail) {
        hlt();
    }

    char c = kbd_buf[kbd_tail];
    kbd_tail = (uint8_t)((kbd_tail + 1) % KBD_BUFFER_SIZE);
    return c;
}
