.MODEL SMALL
.STACK 100H
.DATA
STR1 DB "Number of Consonants: $" 
STR2 DB "Number of Digits: $"  

COUNT_CONC DB 0
COUNT_NUM DB 0  

ENDL DB 0AH, 0DH, "$"
.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

START:
    MOV AH, 1
    INT 21H
    
    CMP AL, 0DH
    JE END_LOOP
        
;================OPERATION OF NUMBERS=====================
    CMP AL, '0'
    JB GOTO_CHAR_CHECK   
    CMP AL, '9'
    JA GOTO_CHAR_CHECK
    INC COUNT_NUM
    JMP START

;=====================OPERATION OF CHAR===================
GOTO_CHAR_CHECK:
    CMP AL, 'A'
    JB START
    CMP AL, 'Z'
    JBE YES_CHAR
    CMP AL, 'a'
    JB START
    CMP AL, 'z'
    JBE YES_CHAR
    JMP START

;=====================YES CHAR CHECK CONSO=================
YES_CHAR:
    CMP AL,'A'
    JE START
    CMP AL,'E'
    JE START
    CMP AL,'I'
    JE START
    CMP AL,'O'
    JE START
    CMP AL,'U'
    JE START
    CMP AL,'a'
    JE START
    CMP AL,'e'
    JE START
    CMP AL,'i'
    JE START
    CMP AL,'o'
    JE START
    CMP AL,'u'
    JE START
    INC COUNT_CONC
    JMP START

END_LOOP:
    MOV AH, 9
    LEA DX, ENDL
    INT 21H  
    
    ;PRINTING MESSAGE STR1
    MOV AH, 9
    LEA DX, STR1
    INT 21H  

    MOV AL, COUNT_CONC
    ADD AL, '0'
    MOV DL, AL
    MOV AH, 2
    INT 21H
           
           
    MOV AH, 9
    LEA DX, ENDL
    INT 21H  
    
    ;PRINTING MESSAGE STR2
    MOV AH, 9
    LEA DX, STR2
    INT 21H  
       
    MOV AL, COUNT_NUM
    ADD AL, '0'
    MOV DL, AL
    MOV AH, 2
    INT 21H
   
   
MOV AH, 4CH
INT 21H
MAIN ENDP
END MAIN
