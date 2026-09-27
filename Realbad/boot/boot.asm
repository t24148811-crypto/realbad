; Multiboot2 entry for Realbad OS (i386, 32-bit protected mode from GRUB).

MULTIBOOT2_MAGIC        equ 0xE85250D6
MULTIBOOT2_ARCH_I386    equ 0
MULTIBOOT2_HEADER_LEN   equ header_end - header_start
MULTIBOOT2_CHECKSUM     equ -(MULTIBOOT2_MAGIC + MULTIBOOT2_ARCH_I386 + MULTIBOOT2_HEADER_LEN)

section .multiboot_header
align 8
header_start:
    dd MULTIBOOT2_MAGIC
    dd MULTIBOOT2_ARCH_I386
    dd MULTIBOOT2_HEADER_LEN
    dd MULTIBOOT2_CHECKSUM

    ; Information request tag (optional): none for now.
    ; End tag
    dw 0
    dw 0
    dd 8
header_end:

section .text
bits 32
global _start
extern kernel_main

_start:
    cli
    mov esp, stack_top
    xor ebp, ebp

    ; cdecl: kernel_main(magic, multiboot_info)
    push ebx
    push eax
    call kernel_main

    cli
.hang:
    hlt
    jmp .hang

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:
