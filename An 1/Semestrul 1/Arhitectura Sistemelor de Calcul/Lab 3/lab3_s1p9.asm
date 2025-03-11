bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        ;a - byte, b - word, c - double word, d - qword - Interpretare fara semn
        a db 1
        b dw 3
        c dd 5
        d dq 10

; our code starts here
segment code use32 class=code
    start:
        ; (d+d-b)+(c-a)+d =(10+10-3)+(5-1)+10=17+4+10=31
        mov eax, dword [d]
        mov edx, dword [d+4]
        add eax, dword [d]
        adc edx, dword [d+4]
        mov bx, [b]
        mov cx, 0
        push cx
        push bx
        pop ebx
        sub eax, ebx ;edx:eax=(d+d-b)
        sbb edx, 0        
        mov bx, word [c]
        mov cx, word [c+2]
        push edx
        push eax
        mov al, [a]
        mov ah, 0
        mov dx, 0
        push dx
        push ax
        push cx
        push bx
        pop ebx
        pop ecx
        sub ebx, ecx
        pop eax
        pop edx
        add eax, ebx
        adc edx, 0
        add eax, dword [d]
        adc edx, dword [d+4]
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
