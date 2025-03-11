bits 32  
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll          
segment data use32 class=data
    format db "numar %d, in baza 8 %o, caracter %c", 0x0A, 0
segment code use32 public code
global algoritm

algoritm:
     mov eax, [esp+4]
     push eax
     push eax
     push eax
     push dword format
     call [printf]
     add esp, 4*4
     ret
