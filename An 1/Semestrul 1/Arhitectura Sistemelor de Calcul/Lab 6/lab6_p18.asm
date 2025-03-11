bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;1234ABCDh, 12565678h, 12AB4344h.
    sir dd 12AB5678h, 1256ABCDh, 12344344h
    len equ $-sir
    sir2 times len dw 0
    sir3 times len dw 0
; our code starts here
segment code use32 class=code
    start:
        mov esi, sir
        mov edi, sir2
        mov ecx, len / 4
        jecxz final
    repeta:
        lodsd
        rol eax, 16
        stosw
    loop repeta
    
        mov ecx, len/4
        dec ecx                    
        mov esi, 0                 
    loop_1:
        mov ax, [sir2+esi]             
        
        mov ebx, esi
        inc ebx                    
        loop_2:
            mov dx, [sir2+ebx]       
            
            cmp ax, dx
            jb no_swap
            
            mov [sir2+ebx], ax
            mov [sir2+esi], dx
            mov ax, dx
            
        no_swap:
            inc ebx                
            cmp ebx, len/4
            jb loop_2              

    next:
        inc esi                    
        loop loop_1
    
   
    
    
    final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
