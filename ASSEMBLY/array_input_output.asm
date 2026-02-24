.model small
.stack 100h
.data
;------------------- 
arr dw 7 dup (0) 
endl db 0ah, 0dh, "$"
;-------------------

.code
main proc
;===========================
;--------db connect---------
    mov ax, @data
    mov ds, ax  
;---------------------------
mov cx, 7
mov si, 0 
;------------input-----------
loopingInput:
    mov ah, 9
    lea dx, endl
    int 21h 
    
    xor ax, ax
    
    call indec
    mov arr[si], ax
    add si, 2
    loop loopingInput

;----------output-------------
lea si, arr
mov cx, 7
xor ax, ax

loopingOutput: 
    xor ax, ax
    mov al, [si]
     
    push ax
    call outdec
    pop ax
   
    add si, 2
       
    mov ah, 9
    lea dx, endl
    int 21h 
    
    loop loopingOutput    
       
;===========================
mov ah, 4ch
int 21h
main endp
INCLUDE INDEC.ASM
INCLUDE OUTDEC.ASM
end main