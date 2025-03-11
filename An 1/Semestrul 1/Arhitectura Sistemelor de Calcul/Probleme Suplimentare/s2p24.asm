bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; (a-b-b-c)+(a-c-c-d)
    ; (24-4-4-10)+(24-10-10-3) => 6+1=7
    a db 24
    b db 4
    c db 10
    d db 3

; our code starts here
segment code use32 class=code
    start:
        mov al, [a]
        sub al, [b]
        sub al, [b]
        sub al, [c]
        mov bl, [a]
        sub bl, [c]
        sub bl, [c]
        sub bl, [d]
        add al, bl
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
