.eqv SYS_PRINT_STRING   4
.eqv SYS_READ_WORD      5
.eqv SYS_EXIT           10

.data
        inputmsg: .asciiz "Number: "
        evenstr:  .asciiz "Even number\n"
        oddstr:   .asciiz "Odd number\n"

.text
.globl main

main:
        li      $v0, SYS_PRINT_STRING
        la      $a0, inputmsg
        syscall
        
        li      $v0, SYS_READ_WORD
        syscall

        # Get the LSB
        andi    $t0, $v0, 1
        beq     $t0, 1, odd
        
        li      $v0, SYS_PRINT_STRING
        la      $a0, evenstr
        syscall
        j       exit
        
odd:
        li      $v0, SYS_PRINT_STRING
        la      $a0, oddstr
        syscall

exit:
        li      $v0, SYS_EXIT
        syscall
