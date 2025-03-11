bits 32 
global start

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    sir dd 1234A678h, 12345678h, 1AC3B47Dh, 0FEDC9876h
    ; 78 a6 23 12       
    ; esi :
    ; sir_nou = A6 78 ... 
    len_sir equ ($-$$)/4
    
    sir_nou times len_sir db 0
    format db "%x", 0
    
    sum db 0
    d_format db "%d", 0 
    
    sir_rank times len_sir db 0
    poz db 0
    cnt db 1
    
    s_format db "%s", 0

segment code use32 class=code
    start:
        mov edi, sir_nou
        mov esi, sir 
        mov ecx, len_sir
        repeta:
            xor bl, bl ;bl - maximul (A6)
            mov dl, 5
            repeta2:
                dec dl 
                cmp dl, 0 
                je exit_repeta2
                lodsb
                cmp bl, al ;bl-al
                ja sari
                mov bl, al
                sari:
                
            jmp repeta2
                 
            exit_repeta2:
            mov al, bl 
            stosb  
        
        loop repeta
        
        mov ecx, len_sir
        mov edi, sir_nou
        repeta1:
            lodsb
            add byte[sum], al
            movzx eax, al 
            push ecx 
            push dword eax 
            push dword format
            call [printf]
            add esp, 4*2
            pop ecx 
            
        loop repeta1
        
        mov al, [sum] 
        movsx eax, al
        push dword eax
        push dword d_format
        call [printf]
        add esp, 4*2
        
        xor edi, edi
        xor esi, esi 
        mov esi, sir_nou
        mov edi, sir_rank
        mov ecx, len_sir
        mov bl, 0
        repeta3:
        mov esi, sir_nou
        mov bl, 0
        push ecx
        mov ecx, len_sir
            repeta4:
            lodsb
            mov edi, sir_rank
            add edi, esi
            sub edi, sir_nou
            cmp edi, 0
            jne nu_compara
            cmp al, bl
            jb nu_compara
            mov bl, al
            mov edx, esi
            sub edx, sir_nou
            mov byte [poz], dl
            nu_compara:
            
            loop repeta4
            cmp bl, 0
            je peste
            mov edx, 0
            mov dl, byte [cnt]
            add dl, '0'
            mov edi, sir_rank
            mov al, byte [poz]
            movzx eax, al
            add edi, eax
            mov al, dl
            stosb
            inc byte [cnt]
            peste:
        pop ecx
        loop repeta3
        
        mov ecx, len_sir
        mov esi, sir_rank
        repeta5:
        lodsb 
        movzx eax, al
        push eax
        push dword s_format
        call [printf]
        add esp, 4*2
        loop repeta5
        
    
    
    push dword 0
    call [exit]
    
    
    
    
    
    
    
    
    
    
    
    
    