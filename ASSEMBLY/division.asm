.MODEL SMALL
.STACK 100H
.DATA
;----------------------------------- 
STR1 DB "INPUT A NUMBER: $"
STR2 DB 0AH, 0DH,"THE RESULT IS: $" 
NUM1 DB ?
NUM2 DB ?  

ENDL DB 0AH, 0DH, "$"
;-----------------------------------
.CODE
MAIN PROC
;--------------CONNECT DATA------------------
MOV AX,@DATA
MOV DS,AX
;-------------------------------------------- 
    mov ax, 15
    cwd
    mov bx, 7
    div bx 
    
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