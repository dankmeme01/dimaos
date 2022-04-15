disk_load:
    push dx
    mov ah, 0x02 ; BIOS read sector
    mov al, dh ; read DH sectors
    mov ch, 0x00 ; cylinder 0
    mov dh, 0x00 ; head 0
    mov cl, 0x02 ; read after sector 2
    int 0x13 ; bios interrupt

    jc disk_error
    pop dx
    cmp dh, al
    jne disk_error
    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call println
    jmp $

DISK_ERROR_MSG:
    db 'Disk read error!',0