bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a - byte, b - word, c - double word, d - qword - Interpretare cu semn
    a db -2
    b dw 3
    c dd 1
    d dq 4
    

; our code starts here
segment code use32 class=code
    start:
        ; a-d+b+b+c=-2-4+3+3+1=1
        mov al, [a]
        cbw;ax=a 
        cwd ;dx:ax=a
        push dx
        push ax
        pop eax
        cdq ;edx:eax=a 
        mov ebx, dword [d]
        mov ecx, dword [d+4]
        sub eax, ebx
        sbb edx, ebx ; edx:eax=a-d 
        push edx
        push eax
        mov ax, [b]
        mov bx, [b]
        add ax, bx ;ax=b+b
        cwd ; dx:ax=b+b
        mov bx, word [c]
        mov cx, word [c+2]
        push dx
        push ax
        pop eax
        push cx
        push bx
        pop ebx
        add eax, ebx
        cdq ; edx:eax=b+b+c
        pop ebx
        pop ecx ; ecx:ebx=a-d
        add eax, ebx
        adc edx, ecx
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
