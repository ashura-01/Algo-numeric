

;================================
 
 
;       20230204045


;================================ 


.MODEL SMALL
.STACK 100H

.DATA
    
    PATTERNS DB 3Fh, 06h, 5Bh, 4Fh, 66h, 6Dh, 7Dh, 07h, 7Fh, 6Fh
    
    COUNTER DW 999
    
    HUNDREDS DB ?
    TENS     DB ?
    UNITS    DB ?

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

COUNT_LOOP:

    MOV AX, COUNTER
    MOV CX, 10
    
    ; Get Units
    XOR DX, DX      
    DIV CX          
    MOV UNITS, DL   
    
;--------- Get Tens & Hundreds-----

    XOR DX, DX      
    DIV CX  
            
    MOV TENS, DL    
    MOV HUNDREDS, AL

    LEA BX, PATTERNS    
    
;--------- Hundreds 2030h------------
    MOV AL, HUNDREDS
    XLAT                
    MOV DX, 2030h
    OUT DX, AL
    
;--------- Tens 2031h ---------
    MOV AL, TENS
    XLAT
    MOV DX, 2031h
    OUT DX, AL
    
;--------- Units 2032h --------------
    MOV AL, UNITS
    XLAT
    MOV DX, 2032h
    OUT DX, AL

    ; --------  Delay --------
    MOV CX, 20h
DELAY:
    DEC CX
    JNZ DELAY
    ; ------------------------------ 
    

    SUB COUNTER, 2         
    
    CMP COUNTER, 301     
    JGE COUNT_LOOP      

    MOV AH, 4CH
    INT 21H

MAIN ENDP
END MAIN