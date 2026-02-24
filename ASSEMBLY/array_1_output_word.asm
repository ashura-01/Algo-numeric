.model small
.stack 100h
.data
;------------------- 
arr dw 1,2,3,4,5,6,7 
endl db 0ah, 0dh, "$"
;-------------------

.code
main proc
;===========================
;--------db connect---------
    mov ax, @data
    mov ds, ax  
;--------------------------- 

lea si, arr
mov cx, 7
xor ax, ax

looping: 
    xor ax, ax
    mov al, [si]
     
    push ax
    call outdec
    pop ax
   
    add si, 2
       
    mov ah, 9
    lea dx, endl
    int 21h 
    
    loop looping    
       
;===========================
mov ah, 4ch
int 21h
main endp
INCLUDE INDEC.ASM
INCLUDE OUTDEC.ASM
end main