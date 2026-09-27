#include <stdint.h>
#include "vga.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "timer.h"
#include "keyboard.h"
#include "io.h"
#include "shell.h"

#define MULTIBOOT2_BOOTLOADER_MAGIC 0x36D76289

void kernel_main(uint32_t magic, void *multiboot_info)
{
    (void)multiboot_info;

    vga_init();
    gdt_init();
    idt_init();
    pic_remap(0x20, 0x28);
    timer_init(100);
    keyboard_init();
    sti();

    vga_set_color(vga_entry_color(VGA_WHITE, VGA_BLUE));
    vga_write(" Realbad OS ");
    vga_set_color(vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK));
    vga_write("\n\n");

    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        vga_set_color(vga_entry_color(VGA_LIGHT_RED, VGA_BLACK));
        vga_write("error: not booted by Multiboot2 (bad magic)\n");
        vga_set_color(vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK));
        for (;;) {
            hlt();
        }
    }

    vga_write("boot: Multiboot2 OK\n");
    vga_write("gdt / idt / pic / pit / kbd ready\n\n");

    shell_run();
}
