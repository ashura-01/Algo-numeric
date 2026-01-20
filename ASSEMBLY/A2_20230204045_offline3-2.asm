.MODEL SMALL
.STACK 100H
.DATA
;-----------------initialization------------------ 
prompt      db "Enter expression: $"       
endl        db 0AH,0DH,"$"                  
correctMsg  db "Correct Expression$"        
tooLeftMsg  db "Too many left brackets$"    
tooRightMsg db "Too many right brackets$"   
contMsg     db "Continue? Y/N capital please: $"            
yesChar     db 'Y'                           
;-----------------------------------------------

.CODE
MAIN PROC
;--------------CONNECT DATA------------------ 
mov ax,@data
mov ds,ax

;-------------------------------------------- 
startProg:
;------------- prompt ----------------- 
    
    mov ah, 9
    lea dx, endl
    int 21h
    mov ah,9
    lea dx,prompt
    int 21h

    xor cx,cx          

;--- reading character started from here ----- 
inputLoop:
    mov ah,1           
    int 21h
    cmp al,0DH         
    je checkEnd

    cmp al,'('
    je pushOpen        ; if ( push  stack

    cmp al,')'
    je popCheck        ; if ) pop  stack or error

    jmp inputLoop      ; ignore other characters 

;--- push  onto stack ---
pushOpen:
    push ax            
    inc cx             
    jmp inputLoop

;--- pop  stack if  matches ---
popCheck:
    cmp cx,0           
    je tooManyRight
    pop dx             ; pop matching 
    dec cx             ; decrement count
    jmp inputLoop

;--- error: too many right brackets ---
tooManyRight:
    mov ah,9
    lea dx,tooRightMsg
    int 21h
    jmp askContinue

;--- after Enter, check if expression correct ---
checkEnd:
    cmp cx,0
    je correct         ; if CX=0, expression is correct
    mov ah,9
    lea dx,tooLeftMsg
    int 21h
    jmp askContinue

;--- correct expression ---
correct:
    mov ah,9
    lea dx,correctMsg
    int 21h

;--- ask user to continue ---
askContinue:
    mov ah,2
    mov dl,0DH
    int 21h
    mov dl,0AH
    int 21h 
    
;----- newline for better output------
    mov ah, 9
    lea dx, endl
    int 21h  
    mov ah,9
    lea dx,contMsg
    int 21h  
   
; read yes no here
    mov ah,1
    int 21h           
    cmp al,'Y'  
    je startProg      ; if 'Y', restart program

;--- exit program ---
exitProg:
    mov ah,4CH
    int 21h
MAIN ENDP
END MAIN
