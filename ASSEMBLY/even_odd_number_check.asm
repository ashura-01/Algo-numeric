.model small
.stack 100h
.data
;------------------- 
var dw ?
arr dw 7 dup (0) 
endl db 0ah, 0dh, "$"  

evenMSG db 0ah, 0dh, "the number is even!! $"
oddMSG db 0ah, 0dh, "the number is odd!! $"
;-------------------

.code
main proc
;--------db connect---------
    mov ax, @data
    mov ds, ax  
;---------------------------
 
    xor ax, ax
    call indec
    mov var, ax
    
    mov bx, var 
    xor dx, dx
    div bx
    
    cmp dx, 0
    je even
odd:              
    mov ah, 9
    lea dx, oddmsg    
    int 21h
even: 
    mov ah, 9
    lea dx, evenmsg
    int 21h
       
;===========================
mov ah, 4ch
int 21h
main endp
INCLUDE INDEC.ASM
INCLUDE OUTDEC.ASM
end main