.model small
.stack 100h
.data
;-------------initialize---------------

sum db 0

endl db 0ah, 0dh, "$"
;---------------------
.code
main proc
;--------------connect data------------
mov ax, @data
mov ds, ax
;----------------------------------------
    mov al,0;
    mov bl,0;
        
;============== operation 1 ===============

input_sum_loop: 
        
        mov ah, 1
        int 21h
        sub al, '0'
        add al, sum
        mov sum, al
        
        add bl, 1
        
        ;checking condition
        cmp bl, 3
        JL input_sum_loop
;=======================================

    mov ah, 9
    lea dx, endl
    int 21h   
    
;=================operation 2====================
        xor cx, cx
        mov cl, 8 
        
print_binary:
        rol sum,1
        mov ah, 2
            jc print_1
        ;zero printing....
        mov dl, '0'
        int 21h
            jmp condition
          
    print_1:
    mov dl, '1'
    int 21h

condition:
    loop print_binary
            
    
    
mov ah, 4ch
int 21h
main endp
end main
