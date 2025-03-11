bits 32
global start
extern exit, fopen, fread, fprintf, fclose, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
;se da fisierul input.txt din care se citeste o operatie de genu: 1/2 + 3*  7-  9
;pe prima linie afiseaza sirul initial_text
;pe a doua linie afiseaza lungimea sirului
;pe a 3 a linie numarul de spatii
;pe a 4 a linie sirul initial, dar toate operatiile sa fie cu plus

; 5 a linie rezultatul adunarii de pe linia 4
; 6 rezultatul adunarii de pe linia 4 fara spatii
segment data use32 class=data
    input_mode db "r", 0
    input_file_name db "input.txt", 0
    input_descriptor dd -1
   
    
    out_mode db "w", 0
    output_file_name db "output.txt", 0
    output_descriptor dd -1
    
    len equ 100
    text times (len+1) db 0
    initial_text resb 0 
    string_format db "%s", 13, 10, 0
    int_format db "%d", 13, 10, 0
    lungime dd 0
    spatii dd 0
    semne db "*/-", 0
    len2 equ $-semne
    text_plus times len db 0
    suma dd 0
    text_plus_fara_spatii times len db 0

segment code use32 class=code
    start:
        push dword input_mode
        push dword input_file_name
        call [fopen]
        add esp, 4*2
        
        mov [input_descriptor], eax
        cmp eax, 0
        je final     
        
        
        push dword [input_descriptor]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4*4
        mov esi, text
        
           
        push dword out_mode
        push dword output_file_name
        call [fopen]
        add esp, 4*2
        
        mov [output_descriptor], eax
        cmp eax, 0
        je final
        
        mov esi, text 
        mov edi, text_plus
        repeta:
            mov al, byte [esi]
            cmp al, 0
            je final1
            cmp al, ' '
            jne sari
            inc dword [spatii]
            sari:
            cmp al, '-'
            je plus
            cmp al, '*'
            je plus
            cmp al, '/'
            je plus
            jmp nu_plus
            plus:
                mov byte [edi], '+'
                jmp peste
            nu_plus:
                mov al, byte [esi]
                mov byte [edi], al
            peste:
            cmp al, '1'
            je adunare
            cmp al, '2'
            je adunare
            cmp al, '3'
            je adunare
            cmp al, '4'
            je adunare
            cmp al, '5'
            je adunare
            cmp al, '6'
            je adunare
            cmp al, '7'
            je adunare
            cmp al, '8'
            je adunare
            cmp al, '9'
            je adunare
            jmp fara_adunare
            adunare:
            mov eax, 0
            mov al, byte [esi]
            sub al, '0'
            add dword [suma], eax
            fara_adunare:
            pop ecx
            inc edi
            inc esi
            inc dword [lungime]
            
            
            jmp repeta
        mov esi, text_plus
        mov edi, text_plus_fara_spatii
        repeta1:
            mov al, byte [esi]
            cmp al, 0
            je final1
            cmp al, ' '
            je nu
            mov byte [edi], al
            inc edi
            nu:
            inc esi
            jmp repeta1
            
        final1:
        
            push dword text
            push dword string_format
            call [printf]
            add esp, 4*2
            
            push dword [lungime]
            push dword int_format
            call [printf]
            add esp, 4*2
            
            push dword [spatii]
            push dword int_format
            call [printf]
            add esp, 4*2
            
            push dword text_plus
            push dword string_format
            call [printf]
            add esp, 4*2
            
            push dword [suma]
            push dword int_format
            call [printf]
            add esp, 4*2
            
            ;push dword text_plus_fara_spatii
            ;push dword string_format
            ;call [printf]
            ;add esp, 4*2
            
            
            
            


        final:
            push dword [input_descriptor]
            call [fclose]
            add esp, 4
            
            push dword [output_descriptor]
            call [fclose]
            add esp, 4
            ; exit(0)
            push dword 0
            call [exit]