.MODEL SMALL
.STACK 100H
.DATA
;----------------------------------- 
STR1 DB "INPUT A NUMBER: $"
STR2 DB "THE RESULT IS: $" 
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
    ;input a number
    CALL INDEC
    PUSH AX
    
    ;printing newline
    mov ah, 9
    lea dx, endl
    int 21h
    
    ;output the number
    POP AX
    CALL OUTDEC
    
MOV AH, 4CH
INT 21H
MAIN ENDP 
    INCLUDE OUTDEC.ASM
    INCLUDE INDEC.ASm
END MAIN