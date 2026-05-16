addi x1, x0, 0
addi x2, x0, 5
addi x3, x0, 0
addi x4, x0, 1
addi x5, x0, 12
sw x2, 0(x1)
sw x3, 4(x1)
sw x4, 8(x1)
sw x5, 12(x1)
lw x6, 0(x1)
lw x7, 4(x1)
lw x8, 8(x1)
add x9, x6, x7
sw x9, 16(x1)
xor x10, x8, x9
sw x10, 20(x1)
sll x11, x10, x4
sw x11, 24(x1)
addi x1, x1, 28
addi x12, x0, 4
loop: 
lw x13, 0(x1)
add x13, x13, x4
sw x13, 4(x1)
addi x1, x1, -4
bne x1, x0, loop