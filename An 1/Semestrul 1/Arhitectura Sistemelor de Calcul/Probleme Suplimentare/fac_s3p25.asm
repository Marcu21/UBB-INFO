bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a-word; b-byte; c-doubleword; x-qword   Interpretare fara semn
    a dw 2
    b db 1
    x dq 5
    c dd 3
; our code starts here
segment code use32 class=code
    start:
        ; (a*a+b+x)/(b+b)+c*c=10/2+9=5+9=14
        mov ax, [a]
        mov bx, [a]
        imul bx ;ax=a*a
        mov bl, [b]
        mov bh, 0
        add ax, bx ;ax=a*a+b
        mov ebx, dword [x]
        mov ecx, dword [x+4]
        mov dx, 0
        push dx
        push ax
        pop eax
        add eax, ebx
        adc ecx, 0 ;ecx:eax=(a*a+b+x)
        mov edx, ecx; edx:eax=(a*a+b+x)
        mov bl, [b]
        add bl, byte [b]
        mov bh, 0
        mov cx, 0
        push cx
        push bx
        pop ebx
        div ebx ; eax=(a*a+b+x)/(b+b)
        push eax
        mov ax, word [c]
        mov dx, word [c+2]
        push dx
        push ax
        pop eax
        mul eax ;edx:eax=c*c
        pop ebx
        add eax, ebx
        adc edx, 0
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
