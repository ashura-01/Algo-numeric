.MODEL SMALL
.STACK 100H
.DATA
ENDL DB 0AH,0DH,"$"
RESULT DB "Result: $"

.CODE
MAIN PROC
    MOV AX,@DATA
    MOV DS,AX

    ; -------- SHL Example --------
    MOV AL,2          ; AL = 2
    SHL AL,1          ; AL = 4 
    ADD AL,'0'

   mov ah, 2 
   mov dl,al
   int 21h
   

    ; Exit
    MOV AH,4CH
    INT 21H
MAIN ENDP
END MAIN
