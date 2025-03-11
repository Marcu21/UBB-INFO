bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se da un sir de octeti S. Sa se determine maximul elementelor de pe pozitiile pare si minimul elementelor de pe pozitiile impare din S.
    ; S: 1, 4, 2, 3, 8, 4, 9, 5
    ; max_poz_pare: 9
    ; min_poz_impare: 3
    s db 1, 4, 2, 3, 8, 4, 9, 5
    len equ $-s
    max_poz_pare db 0
    min_poz_impare db 127
; our code starts here
segment code use32 class=code
    start:
        mov esi, 0
        mov ecx, len
        jecxz final
    repeta:
        test esi, 01h
        jz e_par
        mov al, [s+esi]
        cmp al, [min_poz_impare]
        jl min
        jmp contor
    e_par:
        mov al, [s+esi]
        cmp al, [max_poz_pare]
        ja max
    min:
        mov [min_poz_impare], al
        jmp contor
    max:
        mov [max_poz_pare], al
    contor:
        inc esi
        loop repeta
    final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
