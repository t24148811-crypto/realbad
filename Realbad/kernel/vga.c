#include "vga.h"
#include "io.h"

static uint16_t *const vga_buffer = (uint16_t *)VGA_MEMORY;
static size_t vga_row;
static size_t vga_col;
static uint8_t vga_color;

static inline uint16_t vga_entry(unsigned char ch, uint8_t color)
{
    return (uint16_t)ch | ((uint16_t)color << 8);
}

static void vga_put_at(char c, size_t x, size_t y)
{
    vga_buffer[y * VGA_WIDTH + x] = vga_entry((unsigned char)c, vga_color);
}

static void vga_update_cursor(void)
{
    uint16_t pos = (uint16_t)(vga_row * VGA_WIDTH + vga_col);
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

static void vga_scroll(void)
{
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[(y - 1) * VGA_WIDTH + x] = vga_buffer[y * VGA_WIDTH + x];
        }
    }

    for (size_t x = 0; x < VGA_WIDTH; x++) {
        vga_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(' ', vga_color);
    }

    vga_row = VGA_HEIGHT - 1;
}

void vga_init(void)
{
    vga_row = 0;
    vga_col = 0;
    vga_color = vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK);
    vga_clear();
}

void vga_set_color(uint8_t color)
{
    vga_color = color;
}

void vga_clear(void)
{
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[y * VGA_WIDTH + x] = vga_entry(' ', vga_color);
        }
    }
    vga_row = 0;
    vga_col = 0;
    vga_update_cursor();
}

void vga_putc(char c)
{
    if (c == '\n') {
        vga_col = 0;
        if (++vga_row == VGA_HEIGHT) {
            vga_scroll();
        }
        vga_update_cursor();
        return;
    }

    if (c == '\r') {
        vga_col = 0;
        vga_update_cursor();
        return;
    }

    if (c == '\t') {
        size_t next = (vga_col + 4) & ~(size_t)3;
        if (next >= VGA_WIDTH) {
            vga_putc('\n');
        } else {
            while (vga_col < next) {
                vga_put_at(' ', vga_col, vga_row);
                vga_col++;
            }
        }
        vga_update_cursor();
        return;
    }

    vga_put_at(c, vga_col, vga_row);
    if (++vga_col == VGA_WIDTH) {
        vga_col = 0;
        if (++vga_row == VGA_HEIGHT) {
            vga_scroll();
        }
    }
    vga_update_cursor();
}

void vga_backspace(void)
{
    if (vga_col > 0) {
        vga_col--;
    } else if (vga_row > 0) {
        vga_row--;
        vga_col = VGA_WIDTH - 1;
    } else {
        return;
    }

    vga_put_at(' ', vga_col, vga_row);
    vga_update_cursor();
}

void vga_write_n(const char *s, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        vga_putc(s[i]);
    }
}

void vga_write(const char *s)
{
    while (*s) {
        vga_putc(*s++);
    }
}
