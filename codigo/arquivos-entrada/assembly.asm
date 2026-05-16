    addi x5, x5, 9
    addi x7, x7, 782
    addi x3, x3, 1
    sll x2, x7, x3
    xor x4, x2, x3
    add x6, x5, x7
    sw x2, 0(x1)
    lw x8, 0(x1)
    bne x5, x0, ROTULO
FIM:
    add x9, x9, x9
ROTULO:
    addi x31, x31, 666