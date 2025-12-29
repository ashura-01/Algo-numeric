;;QUESTION TAKE INPUT OF A LOWERCASE AND SHOW OUTPUT

.MODEL SMALL
.STACK 100H
.DATA
;-----------------------
STR1 DB "ENTER A UPPER CHAR TO MAKE IT LOWER: $" 
STR2 DB "THE LOWERCASE LETTER IS: $"
ENDL DB 0AH, 0DH, "$"
CHAR DB ?

;------------------------
.CODE
MAIN PROC
;--------------CONNECT DATA----------------
    MOV AX, @DATA
    MOV DS, AX
;------------------------------------------ 

    
   ;STR1 OUPUT
    MOV AH, 9
    LEA DX, STR1
    INT 21H  

   ;INPUT TAKING
    MOV AH, 1
    INT 21H 

;--------------------PROCESS------------------------
ADD AL,20H 
MOV CHAR, AL
;---------------------------------------------------  

    ;NEW LINE PRITING
    MOV AH, 9
    LEA DX, ENDL
    INT 21H
    
    ;PRINTING STR2
    MOV AH, 9
    LEA DX, STR2
    INT 21H
    
    ;PRINTING RESULT
    MOV AH, 2
    MOV DL, CHAR
    INT 21H    
    




MOV AH, 4CH
INT 21H
MAIN ENDP
END MAIN