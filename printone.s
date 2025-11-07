.global printone
printone:
addi a7, x0, 64 # syscall write
addi a0, x0, 1 # stdout
mv a1, a0 # buffer (argumento de C)
addi a2, x0, 1 # 1 byte
ecall
ret