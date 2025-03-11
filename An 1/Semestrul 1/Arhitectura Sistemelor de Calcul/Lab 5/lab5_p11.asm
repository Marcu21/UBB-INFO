bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se da un sir de octeti S. Sa se obtina sirul D1 ce contine toate numerele pare din S si sirul D2 ce contine toate numerele impare din S.
    ;S: 1, 5, 3, 8, 2, 9
    ;D1: 8, 2
    ;D2: 1, 5, 3, 9
    s db 1, 5, 3, 8, 2, 9
    len equ $-s
    d1 times len db 0 ; 00 00 00 00 00 00
    d2 times len db 0 ; 00 00 00 00 00 00

; our code starts here
segment code use32 class=code
    start:
        mov esi, 0
        mov edi, 0
        mov ebx, 0
        mov ecx, len
        jecxz final
    
    repeta:
        mov al, [s+esi]
        test al, 01h
        jz e_par
        mov [d2+ebx], al
        inc ebx
        jmp contor
    e_par:
        mov [d1+edi], al
        inc edi
    contor:
        inc esi
        loop repeta
    final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
