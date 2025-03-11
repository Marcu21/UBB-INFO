bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fopen msvcrt.dll                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "ana.txt", 0
    mod_acces db "r", 0
    descriptor_fisier dd 0
    
    dimensiune dd 1
    count dd 100
    
    text resb 100
    lungime_sir dd 0
    numar db 0
    
    format_afisare db "%d", 0
    caractere_speciale db "~!@#$%^&*()-=_+{}[];'\,./:|<>?"
    len2 equ $-caractere_speciale
    
; our code starts here
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0
        je final ;nu s a putut deschide fisierul
        
        mov [descriptor_fisier], eax
        ;;;;;;;;din acest punct avem acces la continutul fisierului
        
        push dword [descriptor_fisier]
        push dword [count]
        push dword [dimensiune]
        push dword text
        call [fread]
        add esp, 4*4
        
        
        mov [lungime_sir], eax
        
        mov esi, text
        mov ecx, [lungime_sir]
        cld
        jecxz finalBucla
        
    repeta:
        mov edi, caractere_speciale
        push ecx
        mov ecx, [len2]
    repeta2:
        mov eax, [esi]
        mov edx, [edi]
        cmp eax, edx
        je egal
        inc edi
        loop repeta2
        inc esi
        pop ecx
        loop repeta
    egal:
        inc dword [numar]
        inc esi
        dec ecx
        jnz repeta
        
        
    finalBucla:
    
    
        mov eax, 0
        mov al, [numar]
        
        push eax
        push dword format_afisare
        call [printf]
        add esp, 4*2
        
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        
    final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
        
