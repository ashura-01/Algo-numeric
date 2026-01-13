.MODEL SMALL
.STACK 100H
.DATA
NEW_LINE DB 0AH, 0DH, '$'
INPUT DB 5      ; <-- Assume value here (example: 5 = 00000101)

.CODE
MAIN PROC
    ; Initialize data segment
    MOV AX, @DATA
    MOV DS, AX

    ; Prepare loop counter for 8 bits
    XOR CX, CX
    MOV CL, 8

    ; Print new line before output
    LEA DX, NEW_LINE
    MOV AH, 9
    INT 21H

PrintBinary:
    ROL INPUT, 1        ; Rotate left 1 bit, MSB goes into CF
    MOV AH, 2
    JC PRINT_1          ; If CF = 1, print '1'
    MOV DL, '0'
    INT 21H
    JMP CONDITION

PRINT_1:
    MOV DL, '1'
    INT 21H

CONDITION:
    LOOP PrintBinary    ; Repeat 8 times

    ; End program
    MOV AH, 4CH
    INT 21H

MAIN ENDP
END MAIN
