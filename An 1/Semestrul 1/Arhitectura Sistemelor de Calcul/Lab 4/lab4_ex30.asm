bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    A dw 1011_1001_0011_0010b
    B dd 0
    format db "%X", 0
; our code starts here
segment code use32 class=code
    start:
        mov ax, [A]
        xor ax, 0Ah
        shr ax, 1
        mov ebx, 0
        mov bl, al
        ror bx, 4
        mov ax, [A]
        shr ax, 7 ; 0000_0001_0111_0010b
        mov bl, al
        rol bx, 4 ; 0000_0111_0010_comp
        mov ecx, 0
        mov cx, 0
        mov ax, [A] ;1011_1001_0011_0010b
        shr ax, 3; 0001_0111_0010_0110
        xor ax, 1111_1111_1111_1111b
        mov ch, al
        shl ch, 2
        or cx, 0000_0011_1111_0000b
        mov word [B], cx ;1111_1111_1111_0000
        mov word [B+2], bx ;0000_0111_0010_comp
        ;0000_0111_0010_comp_1111_1111_1111_0000
        push dword [B]
        push dword format
        call [printf]
        add esp, 4*2
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
