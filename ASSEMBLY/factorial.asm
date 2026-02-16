.MODEL SMALL
.STACK 100H
.DATA
;----------------------------------- 

gcdmsg db 0ah, 0dh, "GCD is: $" 

num dw 5

result dw ?

ENDL DB 0AH, 0DH, "$"
;-----------------------------------
.CODE
MAIN PROC
;--------------CONNECT DATA------------------
MOV AX,@DATA
MOV DS,AX
;-------------------------------------------- 
    mov cx, num
    mov ax, 1
looping: 
    mul cx 
    mov result, ax
    loop looping 
    
mov ax, result
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