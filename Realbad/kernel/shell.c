#include "shell.h"
#include "vga.h"
#include "keyboard.h"
#include "string.h"
#include "io.h"

#define SHELL_LINE_MAX 128
#define KBD_STATUS 0x64
#define KBD_PULSE_RESET 0xFE

static void skip_spaces(char **s)
{
    while (**s == ' ' || **s == '\t') {
        (*s)++;
    }
}

static void reboot(void)
{
    vga_write("rebooting...\n");

    cli();
    while (inb(KBD_STATUS) & 0x02) {
    }
    outb(KBD_STATUS, KBD_PULSE_RESET);

    for (;;) {
        hlt();
    }
}

static void cmd_help(void)
{
    vga_write("commands:\n");
    vga_write("  help     list commands\n");
    vga_write("  clear    clear screen\n");
    vga_write("  echo     print arguments\n");
    vga_write("  ver      print version\n");
    vga_write("  reboot   restart machine\n");
}

static void cmd_ver(void)
{
    vga_write("Realbad OS 0.1 (i386)\n");
}

static void shell_exec(char *line)
{
    char *args;

    skip_spaces(&line);
    if (*line == '\0') {
        return;
    }

    args = line;
    while (*args && *args != ' ' && *args != '\t') {
        args++;
    }
    if (*args) {
        *args++ = '\0';
        skip_spaces(&args);
    }

    if (strcmp(line, "help") == 0) {
        cmd_help();
    } else if (strcmp(line, "clear") == 0) {
        vga_clear();
    } else if (strcmp(line, "echo") == 0) {
        vga_write(args);
        vga_putc('\n');
    } else if (strcmp(line, "ver") == 0) {
        cmd_ver();
    } else if (strcmp(line, "reboot") == 0) {
        reboot();
    } else {
        vga_write("unknown command: ");
        vga_write(line);
        vga_write("\n");
    }
}

static void read_line(char *buf, size_t max)
{
    size_t i = 0;

    for (;;) {
        char c = keyboard_getchar();

        if (c == '\n') {
            vga_putc('\n');
            buf[i] = '\0';
            return;
        }

        if (c == '\b') {
            if (i > 0) {
                i--;
                vga_backspace();
            }
            continue;
        }

        if (c == '\t') {
            continue;
        }

        if (i + 1 < max && c >= 32) {
            buf[i++] = c;
            vga_putc(c);
        }
    }
}

void shell_run(void)
{
    char line[SHELL_LINE_MAX];

    vga_write("type 'help' for commands\n\n");

    for (;;) {
        vga_set_color(vga_entry_color(VGA_LIGHT_GREEN, VGA_BLACK));
        vga_write("realbad> ");
        vga_set_color(vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK));
        read_line(line, sizeof(line));
        shell_exec(line);
    }
}
