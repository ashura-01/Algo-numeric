.MODEL SMALL
.STACK 100H
.DATA
;----------------------------------- 

gcdmsg db 0ah, 0dh, "GCD is: $" 

num1 dw 56
num2 dw 42
remainder dw ?

ENDL DB 0AH, 0DH, "$"
;-----------------------------------
.CODE
MAIN PROC
;--------------CONNECT DATA------------------
MOV AX,@DATA
MOV DS,AX
;-------------------------------------------- 

looping:    
        mov ax, num1
        mov bx, num2
        xor dx, dx
        div bx
        mov remainder, dx
        
        cmp remainder,0
        je print_result  
        
        mov ax, num2
        mov num1, ax
        mov ax, remainder
        mov num2, ax
        
        jmp looping  

print_result:
           mov ah, 9
           lea dx, gcdmsg
           int 21h
           
           mov ax, num2
           push ax
           call outdec
           pop ax   
;--------------------------------------------    
MOV AH, 4CH
INT 21H
MAIN ENDP 
    INCLUDE OUTDEC.ASM
    INCLUDE INDEC.ASm
END MAIN