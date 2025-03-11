bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    n dd 0
    m dd 0
    message db "suma = %Xh, diferenta = %Xh", 0
    format  db "%X", 0
    format2  db "%X", 0

; our code starts here
segment code use32 class=code
    start:
        push dword n
        push dword format 
        call [scanf]
        add esp, 4*2
        push dword m
        push dword format2
        call [scanf]
        add esp, 4*2
        mov eax, [n]
        mov ebx, [m]
        and eax, 0xFFFF
        and ebx, 0xFFFF
        add eax, ebx
        mov ecx, eax
        mov eax, [n]
        mov ebx, [m]
        shr eax, 16
        shr ebx, 16
        sub eax, ebx
        push eax
        push ecx
        push dword message
        call [printf]
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
