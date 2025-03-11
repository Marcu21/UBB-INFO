bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, fprintf, scanf
import exit msvcrt.dll  
import fopen msvcrt.dll  
import fread msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "7div2.txt", 0  
    mod_acces db "a", 0  
    descriptor_fis dd -1 
    format db "%d", 0
    a dd 0
    b dd 0
    text1 db "Cat = %d", 0x0A, 0
    text2 db "rest = %d", 0

; our code starts here
segment code use32 class=code
    start:
        push dword a
        push dword format 
        call [scanf]
        push dword b
        push dword format 
        call [scanf]
        
        push dword mod_acces     
        push dword nume_fisier
        call [fopen]
        add esp, 4*2                

        mov [descriptor_fis], eax   
        
        cmp eax, 0
        je final
        
        mov eax, [a]
        mov ebx, [b]
        xor edx, edx
        div ebx
        
        push edx
        push eax
        
        
        push dword text1
        push dword [descriptor_fis]
        call [fprintf]
        add esp, 4*2
        
        pop eax
        
        push dword text2
        push dword [descriptor_fis]
        call [fprintf]
        add esp, 4*2
        
        push dword [descriptor_fis]
        call [fclose]
        add esp, 4
    final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
