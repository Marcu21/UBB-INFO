; Codul de mai jos va deschide un fisier numit "ana.txt" din directorul curent si va citi un text de maxim 100 de caractere din acel fisier.
; Programul va folosi functia fopen pentru deschiderea fisierului, functia fread pentru citirea din fisier si functia fclose pentru inchiderea fisierului deschis.
; Deoarece in apelul functiei fopen programul foloseste modul de acces "r", daca un fisier cu numele dat nu exista in directorul curent, apelul functiei fopen nu va reusi (eroare). Detalii despre modurile de acces sunt prezentate in sectiunea "Suport teoretic".

bits 32 

global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf
import exit msvcrt.dll  
import fopen msvcrt.dll  
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "ana.txt", 0  ; numele fisierului care va fi deschis
    mod_acces db "r", 0          ; modul de deschidere a fisierului - 
    format db "%d", 0                             ; r - pentru scriere. fisierul trebuie sa existe 
    descriptor_fis dd -1         ; variabila in care vom salva descriptorul fisierului - necesar pentru a putea face referire la fisier
    len equ 100                  ; numarul maxim de elemente citite din fisier.                            
    text times len db 0          ; sirul in care se va citi textul din fisier  
    caractere_speciale db "~!@#$%^&*()-=_+{}[];'\,./:|<>?"
    len2 equ $-caractere_speciale
    numar db 0
; our code starts here
segment code use32 class=code
    start:
        push dword mod_acces     
        push dword nume_fisier
        call [fopen]
        add esp, 4*2                
        mov [descriptor_fis], eax   
        cmp eax, 0
        je final
        push dword [descriptor_fis]
        push dword len
        push dword 1
        push dword text        
        call [fread]
        add esp, 4*4                  
        mov esi, 0
        mov ecx, eax
        jecxz finalbucla
    repeta:
        mov edi, 0
        push ecx
        mov ecx, len2
    repeta2:
        mov eax, [text+esi]
        mov edx, [caractere_speciale+edi]
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
   
   finalbucla:
        mov eax, 0
        mov al, [numar]
        push eax
        push dword format
        call [printf]
        add esp, 4*2
        push dword [descriptor_fis]
        call [fclose]
        add esp, 4
      final:
        ; exit(0)
        push    dword 0      
        call    [exit]       