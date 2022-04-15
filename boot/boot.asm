[org 0x7c00] ; we are at bootloader
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp ; stack

call load_kernel

call switch_to_x32

jmp $

%include "boot/x32/gdt.asm"
%include "boot/x32/stdio.asm"
%include "boot/x32/switch.asm"
%include "boot/x16/disk.asm"
%include "boot/x16/stdio.asm"

[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET
    mov dh, 32  ; 32 sectors
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_32:
    mov bx, MSG_X32_SWITCH
    call print32
    call KERNEL_OFFSET ; jump and load kernel

    jmp $

BOOT_DRIVE db 0
MSG_X32_SWITCH db "Ntarted DimaOS kernel in 32-bit mode!",0

; Magic bios stuff
times 510 -( $ - $$ ) db 0
dw 0xaa55