nasm -fobj lab11_ex8.asm
nasm -fobj algoritm.asm

alink lab11_ex8.obj algoritm.obj -oPE -subsys console -entry start