.eqv SYS_EXIT           10
.eqv SYS_PRINT_CHAR     11
.eqv OUTLOOP_ITER       5
.eqv INLOOP_ITER        4

.text
.globl main

main:
        # init outer loop counter
        li      $t0, 0
        
outloop:
        # exit if t0 == 5
        beq     $t0, OUTLOOP_ITER, exit
        addi    $t0, $t0, 1

        # init inner loop counter
        li      $t1, 0

        # print newline
        li      $v0, SYS_PRINT_CHAR
        li      $a0, 0xa
        syscall
        j       inloop
        
        j       outloop 
        
inloop:
        # break inner loop if t1 == 4
        beq     $t1, INLOOP_ITER, outloop
        addi    $t1, $t1, 1
        
        li      $v0, SYS_PRINT_CHAR
        li      $a0, '*'
        syscall
        
        j       inloop
        
exit:
        li      $v0, SYS_EXIT
        syscall
