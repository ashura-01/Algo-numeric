.model small
.stack 100h
.data
str1 db "Enter a number (0-3): $"
resultMsg db 0Dh,0Ah,"Square is: $"

.code
main proc
mov ax, @data
mov ds, ax

    ; print message
    mov ah, 9
    lea dx, str1
    int 21h

    ; input
    mov ah, 1
    int 21h
    sub al, '0'

    mov bl, al

    ; square
    mov al, bl
    mul bl          

    ; save result BEFORE printing message
    mov bx, ax

    ; print result message
    mov ah, 9
    lea dx, resultMsg
    int 21h

    ; restore result
    mov ax, bx

    ; convert to ASCII (0–9 safe)
    add al, '0'
    mov dl, al
    mov ah, 2
    int 21h

   
mov ah, 4Ch
int 21h
main endp
end main
