bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; 3*[20*(b-a+2)-10*c]+2*(d-3)
    ;a,b,c - byte, d - word
    ;3*[20*(20-4+2)-10*3]+2*(280-3)=1544
    a db 4
    b db 20
    c db 3
    d dw 280

; our code starts here
segment code use32 class=code
    start:
        mov ax, 20
        mov bl, [b]
        sub bl, [a]
        add bl, 2
        mul bl ; ax=20*(b-a+2)
        mov cx, ax 
        mov ax, 10
        mov bl, [c]
        mul bl ;ax=10*c
        sub cx, ax ;cx=20*(b-a+2)-10*c
        mov ax, 3
        mul cx ;ax=3*[20*(b-a+2)-10*c]
        mov cx, ax 
        mov ax, 2
        mov bx, [d]
        sub bx, 3
        mul bx 
        add ax, cx 
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
