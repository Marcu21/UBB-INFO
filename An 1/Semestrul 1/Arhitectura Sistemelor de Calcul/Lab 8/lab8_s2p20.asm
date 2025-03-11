bits 32 

global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, fprintf
import exit msvcrt.dll  
import fopen msvcrt.dll  
import fread msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "andrei.txt", 0  
    mod_acces db "a", 0          
                                
    descriptor_fis dd -1                                  
    text db "Ana are nu", 0
    len equ $-text

; our code starts here
segment code use32 class=code
    start:
        push dword mod_acces     
        push dword nume_fisier
        call [fopen]
        add esp, 4*2                ; eliberam parametrii de pe stiva

        mov [descriptor_fis], eax   ; salvam valoarea returnata de fopen in variabila descriptor_fis
        
        ; verificam daca functia fopen a creat cu succes fisierul (daca EAX != 0)
        cmp eax, 0
        je final
        
        mov esi, 0
        mov ecx, len
        cld
        jecxz finalbucla
        
     repeta:
        test esi, 1
        jz par
        inc esi
        loop repeta
        
     par:
        mov eax, esi
        add al, '0'
        mov [text+esi], al
        inc esi
        loop repeta
        
     finalbucla:
        push dword text
        push dword [descriptor_fis]
        call [fprintf]
        add esp, 4*2
        
        push dword [descriptor_fis]
        call [fclose]
        add esp, 4
        
     final:
        
        ; exit(0)
        push    dword 0      
        call    [exit]  