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
    b db 2
    c dw 2
    e dd 10
    x dq 105
    

; our code starts here
segment code use32 class=code
    start:
        ; (a-b+c*128)/(a+b)+e-x=(1-2+2*128)/(1+2)+10-5=85+10-5=-10
        mov al, [a]
        mov bl, [b]
        sub al, bl ;al=a-b
        mov bl, al ;bl=a-b
        mov ax, [c]
        mov cx, 128
        imul cx ;ax=c*128 
        mov bx,ax
        mov al, bl
        cbw
        add ax, bx ;ax=(a-b+c*128)
        mov bl, [a]
        mov cl, [b]
        add bl, cl ;bl=a+b
        idiv bl ;al=(a-b+c*128)/(a+b)
        cbw
        cwd ;dx:ax=(a-b+c*128)/(a+b)
        mov bx, word [e]
        mov cx, word [e+2]
        push dx
        push ax
        pop eax
        push cx
        push bx
        pop ebx
        add eax, ebx ;eax=(a-b+c*128)/(a+b)+e
        cdq
        mov ebx, dword [x]
        mov ecx, dword [x+4]
        sub eax, ebx
        sbb edx, ecx 
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
