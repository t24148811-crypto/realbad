#ifndef REALBAD_VGA_H
#define REALBAD_VGA_H

#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

enum vga_color {
    VGA_BLACK         = 0,
    VGA_BLUE          = 1,
    VGA_GREEN         = 2,
    VGA_CYAN          = 3,
    VGA_RED           = 4,
    VGA_MAGENTA       = 5,
    VGA_BROWN         = 6,
    VGA_LIGHT_GREY    = 7,
    VGA_DARK_GREY     = 8,
    VGA_LIGHT_BLUE    = 9,
    VGA_LIGHT_GREEN   = 10,
    VGA_LIGHT_CYAN    = 11,
    VGA_LIGHT_RED     = 12,
    VGA_LIGHT_MAGENTA = 13,
    VGA_YELLOW        = 14,
    VGA_WHITE         = 15
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return (uint8_t)(fg | (bg << 4));
}

void vga_init(void);
void vga_set_color(uint8_t color);
void vga_clear(void);
void vga_putc(char c);
void vga_write(const char *s);
void vga_write_n(const char *s, size_t n);
void vga_backspace(void);

#endif
