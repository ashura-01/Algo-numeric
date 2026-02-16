.MODEL SMALL
.STACK 100H
.DATA
;----------------------------------- 
STR1 DB "INPUT A NUMBER: $"   

outhour DB 0AH, 0DH,"THE RESULT IS(hour): $" 
outmin DB 0AH, 0DH,"THE RESULT IS(min): $" 
outsec DB 0AH, 0DH,"THE RESULT IS(sec): $" 

sec Dw ?
hours Dw ?  
min Dw ?
remainder dw ? 
sec_res dw ?

ENDL DB 0AH, 0DH, "$"
;-----------------------------------
.CODE
MAIN PROC
;--------------CONNECT DATA------------------
MOV AX,@DATA
MOV DS,AX
;-------------------------------------------- 

;user input prompt
    mov ah, 9
    lea dx, str1
    int 21h 
    
;inputing the number
    call indec
    mov sec, ax 

;calculating hours
    mov ax, sec
    mov bx, 3600
    div bx  
    mov hours, ax
    mov remainder, dx  
    
;user output prompt
    mov ah, 9
    lea dx, outhour
    int 21h 
    
;division output program 
    mov ax, hours    
    push ax
    call outdec
    pop ax
    
;calculating min
    mov ax, remainder
    mov bx, 60 
    XOR DX, DX 
    div bx
    mov min, ax
    mov sec_res, dx     
    
;user output program 
    mov ah, 9
    lea dx,outmin
    int 21h

;division output program for minute
    mov ax, min
    push ax
    call outdec    
    pop ax
    
;user output program 
    mov ah, 9
    lea dx,outsec
    int 21h  
    
    mov ax, sec_res
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