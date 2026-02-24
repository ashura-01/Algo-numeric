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

;------------input-----------
mov si, 0
looping_input: 

    mov ah, 9
    lea dx, endl
    int 21h
    
    xor ax, ax
    call indec
    
    mov arr[si], ax
    
    add si, 2   
    loop looping_input
    
;++++++++ reverse ++++++++
mov si, 0
mov di, 12 
mov cx, 3

looping:
    mov ax,arr[si]
    mov bx, arr[di]
    mov arr[si], bx
    mov arr[di], ax
    
    sub di,2
    add si, 2 
    
    loop looping
    

;----------output-------------

xor ax, ax
mov si, 0
mov cx, 7
looping_output:
    mov ah, 9
    lea dx, endl
    int 21h
    
    xor ax, ax
    mov ax, arr[si] 
    push ax
    call outdec
    pop ax
    
    add si, 2
    loop looping_output
       
;===========================
mov ah, 4ch
int 21h
main endp
INCLUDE INDEC.ASM
INCLUDE OUTDEC.ASM
end main