bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;Se da un sir de 3 dublucuvinte, fiecare dublucuvant continand 2 valori pe cuvant (despachetate, deci fiecare cifra hexa e precedata de un 0). 
    ;Sa se creeze un sir de octeti care sa contina acele valori (impachetate deci pe un singur octet), ordonate crescator in memorie, acestea fiind considerate numere cu semn.
    ;pentru sirul initial: 0702090Ah, 0B0C0304h, 05060108h
    ;se va obtine sirul:   72h, 9Ah, 0BCh,  34h, 56h, 18h
    ;ordonat crescator:    9Ah, 0BCh, 18h, 34h, 56h, 72h

    s1 dd 0702090Ah, 0B0C0304h, 05060108h
    len equ $-s1
    s2 times len db 0
     
; our code starts here
segment code use32 class=code
    start:
        mov ecx, len / 4
        jecxz final
        mov esi, s1
        mov edi, s2
    convert:
        lodsd
        rol eax, 16
        
        and al, 0Fh   

        mov bl, ah           
        and bl, 0Fh          
        rol bl, 4
        or al, bl
        stosb
        
        rol eax, 16
        and al, 0Fh   

        mov bl, ah           
        and bl, 0Fh          
        rol bl, 4
        or al, bl
        stosb
        
        
        loop convert

        mov ecx, len/2
        dec ecx                    
        mov esi, 0                 
    loop_1:
        mov al, [s2+esi]             
        
        mov ebx, esi
        inc ebx                    
        loop_2:
            mov dl, [s2+ebx]       
            
            cmp al, dl
            jb no_swap
            
            mov [s2+ebx], al
            mov [s2+esi], dl
            mov al, dl
            
        no_swap:
            inc ebx                
            cmp ebx, len/2 
            jb loop_2              

    next:
        inc esi                    
        loop loop_1
        
    
    final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
