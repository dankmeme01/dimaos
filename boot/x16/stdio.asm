
; mov the string into si!
print:
    pusha

print_char:
    mov al, [bx]
    cmp al, 0
    je print_done
    mov ah, 0x0e
    int 0x10
    add bx, 1
    jmp print_char

print_done:
    popa
    ret

println:
    pusha
    call print
    mov ah, 0x0e

    ; print crlf
    mov al, 0x0d
    int 0x10
    mov al, 0x0a
    int 0x10
    popa
    ret