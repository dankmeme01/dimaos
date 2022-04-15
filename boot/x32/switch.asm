[bits 16]
switch_to_x32:
    cli ; clear interrupts
    lgdt [gdt_descriptor]

    ; set the first bit of cr0 to 1 to enable 32bit mode
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:init_32

[bits 32]
init_32:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call BEGIN_32