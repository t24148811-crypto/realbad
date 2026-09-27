CC      := i686-elf-gcc
AS      := nasm
LD      := i686-elf-gcc

CFLAGS  := -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Ikernel
ASFLAGS := -f elf32
LDFLAGS := -T kernel/linker.ld -ffreestanding -O2 -nostdlib -lgcc

KERNEL  := kernel.bin
ISO     := realbad.iso
ISODIR  := isodir

OBJS    := \
	boot/boot.o \
	kernel/kernel.o \
	kernel/vga.o \
	kernel/gdt.o \
	kernel/gdt_flush.o \
	kernel/idt.o \
	kernel/idt_load.o \
	kernel/isr.o \
	kernel/isr_stub.o \
	kernel/pic.o \
	kernel/timer.o \
	kernel/keyboard.o \
	kernel/string.o \
	kernel/shell.o

.PHONY: all iso run clean

all: $(ISO)

boot/boot.o: boot/boot.asm
	$(AS) $(ASFLAGS) $< -o $@

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel/%.o: kernel/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(KERNEL): $(OBJS) kernel/linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(ISO): $(KERNEL) grub.cfg
	mkdir -p $(ISODIR)/boot/grub
	cp $(KERNEL) $(ISODIR)/boot/realbad.bin
	cp grub.cfg $(ISODIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) $(ISODIR)

iso: $(ISO)

run: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

clean:
	rm -f $(OBJS) $(KERNEL) $(ISO)
	rm -rf $(ISODIR)
