bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    format db "numar %d, in baza 8 %o, caracter %c", 0x0A, 0
    numar db 31
; our code starts here
segment code use32 class=code
    start:
            inc byte [numar]
            mov ecx, [numar]
            mov edx, [numar]
            mov ebx, [numar]
            push ebx
            push edx
            push ecx
            push dword format
            call [printf]
            add esp, 4*4
            cmp byte [numar], 126
            jb start
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program