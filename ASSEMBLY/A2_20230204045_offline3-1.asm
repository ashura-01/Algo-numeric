.MODEL SMALL
.STACK 100H
.DATA
;-----------------initialization------------------ 

string1 db "enter: $" 
string2 db "result: $"
ENDL DB 0AH, 0DH, "$"
;-----------------------------------
.CODE
MAIN PROC
;--------------CONNECT DATA------------------
mov ax, @data;
mov ds, ax;

;-------------------------------------------- 
    mov ah, 9;
    lea dx, string1
    int 21h
      
;================OPERATION================= 

    xor cx, cx
;--- reading character started from here ----- 

    while:
        mov ah, 1
        int 21h
        
        cmp al, 0dh
        je end_while
        
        push ax
        inc cx
        
        jmp while 
        
    end_while:

;========================================== 

  mov ah, 9
  lea dx, endl
  int 21h 
  lea dx, string2
  int 21h
    
        mov ah, 2       
    print_loop:
        pop dx         
        mov dl, dl       
        int 21h
        loop print_loop  ;


   
 

MOV AH, 4CH
INT 21H
MAIN ENDP
END MAIN