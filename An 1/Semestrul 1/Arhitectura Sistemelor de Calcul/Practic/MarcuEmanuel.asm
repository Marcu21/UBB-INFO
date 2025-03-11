bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, fopen, fclose, fread, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "input.txt", 0
    mod_acces db "r", 0
    descriptor_fisier dd -1
    caracter dd 0
    numar dd 0
    format_string db "%s", 0
    format_caracter db "%c", 0
    format_numar db "%d", 0
    len equ 100
    text times len db 0
    contor dd 0
    mesaj_negativ db "Numarul de aparitii al caracterului %c citit nu este egal cu numarul %d citit.", 0
    mesaj_afirmativ db "Numarul de aparitii al caracterului %c citit este egal cu numarul %d citit.", 0
; our code starts here
segment code use32 class=code
    start:
        std
        push dword nume_fisier
        push dword format_string
        call [scanf]
        add esp, 4*2
        std
        push dword caracter
        push dword format_caracter
        call [scanf]
        add esp, 4*2
        std
        push dword numar
        push dword format_numar
        call [scanf]
        add esp, 4*2
        
        
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        mov [descriptor_fisier], eax
        cmp eax, 0
        je final
        
        push dword [descriptor_fisier]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4*4
        
        mov ecx, len
        mov esi, text
        repeta:
            mov eax, 0
            mov al, byte [esi]
            cmp eax, [caracter]
            jne nu
            inc dword [contor]
            nu:
            inc esi
            loop repeta
        
        ;push dword [contor]
        ;push dword format_numar
        ;call [printf]
        ;add esp, 4*2
        
        mov eax, dword [contor]
        mov ebx, dword [numar]
        cmp eax, ebx
        jne negativ
        
        ;push dword [numar]
        ;push dword [caracter]
        ;mov eax, dword [contor]
        ;cmp eax, ebx
        ;je aici
        ;push dword mesaj_negativ
        ;aici:
        ;push dword mesaj_afirmativ
        ;call [printf]
        ;add esp, 4*3
        
        push dword [numar]
        push dword [caracter]
        push dword mesaj_afirmativ
        call [printf]
        add esp, 4*3
        jmp final
        
        negativ:
        push dword [numar]
        push dword [caracter]
        push dword mesaj_negativ
        call [printf]
        add esp, 4*3
    final:
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
