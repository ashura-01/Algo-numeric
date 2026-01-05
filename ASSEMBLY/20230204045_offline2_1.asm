.MODEL SMALL
.STACK 100H
.DATA
;-----------------initialization------------------ 
CHAR1 DB ?
CHAR2 DB ? 

STR1 DB "ENTER CHAR: $"
STR2 DB "THE RESULT: $"

ENDL DB 0AH, 0DH, "$"
;-----------------------------------
.CODE
MAIN PROC
;--------------CONNECT DATA------------------
 MOV AX, @DATA
 MOV DS, AX

;-------------------------------------------- 
    ;STR1 OUTPUT
    MOV AH, 9
    LEA DX, STR1
    INT 21H  
    
INPUT_CHAR1:
    ;INPUT TAKING
    MOV AH,1
    INT 21H 
    CMP AL, 'A'
    JB INPUT_CHAR1
    CMP AL, 'Z'
    JA INPUT_CHAR1
    
    MOV CHAR1, AL 
;------------------------------    
    ;NEW LINE PRITING
    MOV AH, 9
    LEA DX, ENDL
    INT 21H   
    ;STR1 OUTPUT
    MOV AH, 9
    LEA DX, STR1
    INT 21H 
;--------------------------------

INPUT_CHAR2:        
    ;INPUT TAKING
    MOV AH,1
    INT 21H 
    CMP AL, 'A'
    JB INPUT_CHAR1
    CMP AL, 'Z'
    JA INPUT_CHAR1
 
    MOV CHAR2, AL 
    
    ;NEW LINE PRITING
    MOV AH, 9
    LEA DX, ENDL
    INT 21H
    
     ;STR1 OUTPUT
    MOV AH, 9
    LEA DX, STR2
    INT 21H
    
;================OPERATION=================
            MOV AL, CHAR1
            MOV BL, CHAR2
            
   ;--------CONDITIONAL  2--------
            CMP AL,BL
            JGE PRINT_AL_FIRST
            
         ;PRINTING SMALLER
            MOV AH,2
            MOV DL, BL 
            INT 21H
            
            MOV AH,2 
            MOV DL, CHAR1
            INT 21H
            JMP EXIT
                               
                               
            PRINT_AL_FIRST:   ;PRINTING BIGGER
            MOV AH, 2  
            MOV DL, AL
            INT 21H 
            MOV AH,2   
            MOV DL, CHAR2
            INT 21H
             

;==========================================

   
     EXIT:

MOV AH, 4CH
INT 21H
MAIN ENDP
END MAIN