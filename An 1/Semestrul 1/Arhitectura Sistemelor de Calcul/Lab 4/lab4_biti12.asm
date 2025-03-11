bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
;Se dau doua cuvinte A si B. Sa se obtina dublucuvantul C:
; 1) bitii 0-6 ai lui C au valoarea 0
; 2) bitii 7-9 ai lui C coincid cu bitii 0-2 ai lui A
; 3) bitii 10-15 ai lui C coincid cu bitii 8-13 ai lui B
; 4) bitii 16-31 ai lui C au valoarea 1

segment data use32 class=data
    a dw   1010_0001_1101_1101b  ;= 41437
    b dw   0101_1011_1010_0000b  ;= 23456
    c dd 0

    
; our code starts here
segment code use32 class=code
    start:
        ;1             00_0000b 
        
        ;2  
        ;a) mov ax, a  ax=1010_0001_1101_1101  
        ;b) ax= 0000_0000_0000_0101b
        mov ax, [a]
        shl ax,13 ;ax= 1010_0000_0000_0000b
        shr ax,6  ;ax=0000_0010_1000_0000b
        ;AND ax, 0000_0000_0000_0111b ; ax=0000_0000_0000_0101b
        ;shl ax, 7 ; ax=0000_0010_1000_0000b
        
        ;3
        ; b = 0101_1011_1010_0000b 
        mov bx, [b] ; bx=0101_1011_1010_0000b
        and bx, 0011_1111_0000_0000b ; => bx= 0001_1011_0000_0000b
        shl bx, 2 ;bx= 0110110000000000b
        or ax, bx ;ax= 0110_1110_1000_0000
         
        ;4
        mov dx, 1111_1111_1111_1111b
        push dx
        push ax
        pop eax
        mov [c], eax
        
        
        
        
        
        
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program