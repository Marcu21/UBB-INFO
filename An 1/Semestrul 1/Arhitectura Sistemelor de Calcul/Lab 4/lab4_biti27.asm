bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
;Se da quadwordul A. 
; 1) Sa se obtina numarul intreg N reprezentat de bitii 35-37 ai lui A.
; 2) Sa se obtina apoi in B dublucuvantul rezultat prin rotirea spre dreapta a dublucuvantului inferior al lui A cu N pozitii. 
; 3) Sa se obtina octetul C astfel bitii 0-3 ai lui C sunt bitii 8-11 ai lui B

segment data use32 class=data
    a dq 0111_0111_1101_0011_0001_1110_1011_0001_0111_1110_0010_0100_1110_1000_0011_1011b ; = 8634278658273765435
    b dd 0                                      ;31
    c db 0
    n db 0
    

; our code starts here
segment code use32 class=code
    start:
        ;1
        mov eax, [a]
        mov edx, [a+4]; edx=0111_0111_1101_0011_0001_1110_1011_0001
        and edx,            0000_0000_0000_0000_0000_0000_0011_1000b
        shr edx, 3 ; edx=   0000_0000_0000_0000_0000_0000_0011_0b
        mov [n], dl; 
        
        
        ;2 
        ;eax = 0111_1110_0010_0100_1110_1000_0011_1011
        ;ror => 11101101111110001001001110100000
      
        mov cl, dl
        ror eax, cl
        mov [b], eax
        
        ;3
        ;eax=1110_1101_1111_1000_1001_0011_1010_0000b
        and ah, 0000_1111b
        mov [c], ah
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
        