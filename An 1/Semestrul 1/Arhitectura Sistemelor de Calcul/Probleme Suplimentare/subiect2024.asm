bits 32
global start
extern exit,printf
import exit msvcrt.dll
import printf msvcrt.dll
segment data use32 class=data
;s1 dq 1234567809ABCDEFh, 2345678912345678h, 4141abcdefabcdefh ; EF CD AB 09 78 56 34 12
s1 dq 0FABCDEF123456789h, 23456789123456FFh, 4141abcdefabcdefh ; 89 67 45 23 F1 DE BC FA
len equ ($-s1)/8
s2 times len dd 0
format db "%x", 0
segment code use32 class=code
start:
    mov ecx, len
    mov esi, s1
    mov edi, s2
    repeta:
        mov ax, [esi+4] ;DE F1
        mov dx, [esi+6] ;FA BC
        cmp dx, ax
        jl sari
        mov eax, [esi+4]
        stosd
        sari:
        add esi, 8
    loop repeta
    mov ecx, len
    mov esi, s2
    repeta2:
    push ecx
    lodsd
    push eax
    push dword format
    call [printf]
    pop ecx
    loop repeta

push dword 0
call [exit]