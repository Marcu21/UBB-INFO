bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a - byte, b - word, c - double word, d - qword - Interpretare fara semn
    a db 1
    b dw 3
    c dd 5
    d dq 10

; our code starts here
segment code use32 class=code
    start:
        ; ((a + b) + (a + c) + (b + c)) - d=(4+6+8)-10=8
        
        mov al, [a]
        mov ah, 0
        mov bx, [b]
        add bx, ax ;bx=a+b
        mov cx, word [c]
        mov dx, word [c+2]
        add cx, ax
        adc dx, 0
        push dx
        push cx
        pop eax ;eax=a+c 
        mov cx, 0
        push cx
        push bx
        pop ebx
        add eax, ebx ;eax=(a+b)+(a+c)
        push eax
        mov ax, [b]
        mov bx, 0
        push bx
        push ax
        pop eax
        mov cx, word [c]
        mov dx, word [c+2]
        push dx
        push cx
        pop ebx
        add eax, ebx
        pop ecx
        add eax, ecx ;eax=((a + b) + (a + c) + (b + c))
        mov ebx, 0 ;ebx:eax=((a + b) + (a + c) + (b + c))
        mov ecx, dword [d]
        mov edx, dword [d+4]
        sub eax, ecx
        sbb ebx, edx
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
