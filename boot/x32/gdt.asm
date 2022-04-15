gdt_start:

gdt_null:
    dd 0x0 ; dd is define dword, aka 4 bytes
    dd 0x0 ; null descriptor

gdt_code: ; code segment descriptor
    dw 0xffff ; limit (bits 0-15)
    dw 0x0 ; base (bits 0-15)
    db 0x0 ; base (bits 16-23)
    db 10011010b ; flags 1, type flags
    db 11001111b ; flags 2, limit (bits 16-19)
    db 0x0 ; base (bits 24-31)

gdt_data: ; same as code segment except for type flags
    dw 0xffff ; limit (bits 0-15)
    dw 0x0 ; base (bits 0-15)
    db 0x0 ; base (bits 16-23)
    db 10010010b ; flags 1, type flags
    db 11001111b ; flags 2, limit (bits 16-19)
    db 0x0 ; base (bits 24-31)

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; length of gdt
    dd gdt_start ; start of gdt

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start