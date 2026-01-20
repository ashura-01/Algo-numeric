.MODEL SMALL
.STACK 100H
.CODE
MAIN PROC
    ; 1) NEG AX, AX = 8000h
    MOV AX, 8000h
    NEG AX         

    ; 2) ADD AX,BX, 7FFFh + 0001h
    MOV AX, 7FFFH
    MOV BX, 0001H
    ADD AX, BX      

    ; 3) INC AX, AX = FFFFh
    MOV AX, 0FFFFH
    INC AX          

    MOV AH,4CH
    INT 21H
    
MAIN ENDP
END MAIN
