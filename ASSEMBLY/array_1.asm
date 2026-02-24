.model small
.stack 100h
.data
;------------------- 
arr db 1,2,3,4,5,6,7 
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
    add al, [si]
    inc si
    loop looping    
    
add al, '0'    
mov ah, 2
int 21h
  
;===========================
mov ah, 4ch
int 21h
main endp
end main