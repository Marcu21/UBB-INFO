bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a,b-byte; c-word; e-doubleword; x-qword Interpetare fara semn
    a db 1
    b db 1
    c dw 2
    e dd 10
    x dq 5
    

; our code starts here
segment code use32 class=code
    start:
        ; (a-b+c*128)/(a+b)+e-x=(1-1+2*128)/(1+1)+10-5=133
        mov al, [a]
        mov bl, [b]
        sub al, bl ;al=a-b
        mov bl, al ;bl=a-b
        mov ax, [c]
        mov cx, 128
        mul cx ;ax=c*128 
        mov bh,0
        add ax, bx ;ax=(a-b+c*128)
        mov bl, [a]
        mov cl, [b]
        add bl, cl ;bl=a+b
        div bl ;al=(a-b+c*128)/(a+b)
        mov ah, 0
        mov dx, 0
        mov bx, word [e]
        mov cx, word [e+2]
        push dx
        push ax
        pop eax
        push cx
        push bx
        pop ebx
        add eax, ebx ;eax=(a-b+c*128)/(a+b)+e
        mov edx, 0
        mov ebx, dword [x]
        mov ecx, dword [x+4]
        sub eax, ebx
        sbb edx, ecx 
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
