bits 32 


global start        


extern exit
import exit msvcrt.dll


segment data use32 class=data
    x dw 12, $-x
    a db 4
    b db -1
segment code use32 class=code
    start:
        mov ebp, 4
        lea eax, [ebp*5]
    
        ; exit(0)
        push    dword 0
        call    [exit]
