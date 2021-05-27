.eqv SYS_EXIT           10
.eqv SYS_PRINT_CHAR     11
.eqv LOOP_ITER          5

.text
.globl main

main:
        # init loop counter
        li      $t0, 0
        
loop:
        # exit if t0 == 5
        beq     $t0, LOOP_ITER, exit
        addi    $t0, $t0, 1
        
        li      $v0, SYS_PRINT_CHAR
        li      $a0, '*'
        syscall

        j       loop
        
        li      $a0, 0xa
        syscall
        
exit:
        li      $v0, SYS_EXIT
        syscall
