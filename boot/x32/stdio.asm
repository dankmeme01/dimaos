[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print32:
    pusha
    mov edx, VIDEO_MEMORY

    .p32loop:
        mov al, [ebx]
        mov ah, WHITE_ON_BLACK
        cmp al, 0
        je .donep32
        mov [edx], ax
        add ebx, 1
        add edx, 2

        jmp .p32loop
    
    .donep32:
        popa
        ret