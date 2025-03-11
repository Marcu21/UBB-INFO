bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a-doubleword; b,c,d-byte; x-qword Interpretare fara semn
    a dw 100
    b db 3
    c db 12
    d db 2
    x dq 13
    

; our code starts here
segment code use32 class=code
    start:
        ; a-(7+x)/(b*b-c/d+2)=100-(7+13)/(3*3-12/2+2)=100-20/5=100-4=96
        mov al, [b]
        imul al 
        mov bl, al 
        mov al, [c]
        mov cl, [d]
        idiv cl
        sub bl, al
        add bl, 2
        mov eax, dword [x]
        mov edx, dword [x+4]
        add eax, 7 ;edx:eax=7+x
        idiv bl 
        mov ebx, eax
        mov ecx, edx
        mov ax, word [a]
        mov dx, word [a+2]
        push dx
        push ax
        pop eax
        cdq
        sub eax, ebx
        sbb edx, ecx ; edx:eax=a-(7+x)/(b*b-c/d+2)
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
