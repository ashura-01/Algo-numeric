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

    ;PRINTING STRING1
    MOV AH, 9
    LEA DX, STR1
    INT 21H  
    
    ;TAKING INPUTS
    MOV AH, 1
    INT 21H 
    SUB AL, '0'
    MOV NUM1,AL
                
    ;PRINTING NEWLINE
    MOV AH, 9
    LEA DX, ENDL
    INT 21H  
    
    ;PRINTING STRING1
    MOV AH, 9
    LEA DX, STR1
    INT 21H
            
    ;TAKING INPUT
    MOV AH, 1
    INT 21H
    SUB AL, '0'
    MOV NUM2, AL
    
;================OPERATION=================
MOV BL, NUM1
ADD BL, NUM2
;==========================================

    ;PRINTING NEWLINE
    MOV AH, 9
    LEA DX, ENDL
    INT 21H
    
    ;PRINTING STR2
    MOV AH, 9
    LEA DX, STR2
    INT 21H
    
    ;PRINTING RESULT
    ADD BL,'0'
    MOV AH, 2
    MOV DL, BL
    INT 21H
     
    
 

MOV AH, 4CH
INT 21H
MAIN ENDP
END MAIN