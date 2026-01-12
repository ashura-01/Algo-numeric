.MODEL SMALL
.STACK 100H
.DATA
;-----------------initialization------------------

sum db 0 

ENDL DB 0AH, 0DH, "$"
;-----------------------------------
.CODE
MAIN PROC
;--------------CONNECT DATA------------------
     mov ax, @data;
     mov ds, ax;
;-------------------------------------------- 
     mov al, 0
     mov bl, 0
    
;================OPERATION=================  
read_loop:
           mov ah, 1
           int 21h
           
           sub al, '0'
           add al, sum 
           mov sum, al 
           
           add bl, 1 
            
           cmp bl, 3
           jl read_loop


;========================================== 
     mov ah, 9;
     lea dx, endl
     int 21h

     add sum, '0'
     mov ah,2
     mov dl, sum 
     int 21h
   
 

MOV AH, 4CH
INT 21H
MAIN ENDP
END MAIN