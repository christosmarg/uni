.eqv SYS_PRINT_STRING   4
.eqv SYS_READ_WORD      5
.eqv SYS_EXIT           10

.data
        inputmsg: .asciiz "Number: "
        posstr:   .asciiz "Positive\n"
        negstr:   .asciiz "Negative\n"

.text
.globl main

main:
        li      $v0, SYS_PRINT_STRING
        la      $a0, inputmsg
        syscall
        
        li      $v0, SYS_READ_WORD
        syscall
        
        # Right shift number 31 bits so that the MSB falls
        # on the LSB's position. Since we're using 2's
        # complement, if the MSB is 1 the number is negative
        # and if it's 0 it's positive. After the right shift
        # `t0` will either be 0 or 1
        
        srl     $t0, $v0, 31
        beq     $t0, 0, positive
        
        li      $v0, SYS_PRINT_STRING
        la      $a0, negstr
        syscall
        
        j       exit
        
positive:
        li      $v0, SYS_PRINT_STRING
        la      $a0, posstr
        syscall

exit:
        li      $v0, SYS_EXIT
        syscall
