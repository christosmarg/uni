.eqv SYS_PRINT_WORD     1
.eqv SYS_PRINT_STRING   4
.eqv SYS_READ_WORD      5
.eqv SYS_EXIT           10

.data
        inputmsg:    .asciiz "Number (0-15): "
        bounderrstr: .asciiz "Number must be 0-15\n"
        binstr:      .asciiz "Binary: "

.text
.globl main

main:
        li      $v0, SYS_PRINT_STRING
        la      $a0, inputmsg
        syscall
        
        li      $v0, SYS_READ_WORD
        syscall
        move    $t0, $v0
        
        # Bounds check
        blt     $t0, 0, bounderr
        bgt     $t0, 15, bounderr
        
        # Init loop counter, We're right shifting in reverse
        # because otherwise the binary number is going to
        # show reversed. We assign 3 to `s0` because the range
        # 0-15 is 4 bits and we'll go from 3 to 0 (4 iterations).
        # We DON'T start with `s0 = 4` because the last bit
        # will be eaten. 
        # For example if the number is 3 then
        #
        # (0011 >> 3) & 1 = 0000 & 1 = 0
        # (0011 >> 2) & 1 = 0000 & 1 = 0
        # (0011 >> 1) & 1 = 0001 & 1 = 1
        # (0011 >> 0) & 1 = 0011 & 1 = 1
        #
        # So the result is 0011 which is the binary form of 3
        li      $s0, 3
        
binloop:
        srlv    $t1, $t0, $s0   # t1 = t0 >> s0
        andi    $t2, $t1, 1     # t2 = t1 & 1
        
        li      $v0, SYS_PRINT_WORD
        la      $a0, 0($t2)
        syscall
        
        beq     $s0, 0, exit
        addi    $s0, $s0, -1
        j       binloop
        
bounderr:
        li      $v0, SYS_PRINT_STRING
        la      $a0, bounderrstr
        syscall

exit:
        li      $v0, SYS_EXIT
        syscall
