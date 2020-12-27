.eqv SYS_PRINT_STRING   4
.eqv SYS_READ_WORD      5
.eqv SYS_EXIT           10

.data
        inputmsg:   .asciiz "Number: "
        ismultstr:  .asciiz "Multiple of 4\n"
        isnmultstr: .asciiz "Not a multiple of 4\n"

.text
.globl main

main:
        li      $v0, SYS_PRINT_STRING
        la      $a0, inputmsg
        syscall
        
        li      $v0, SYS_READ_WORD
        syscall
        
        # get 2 lowest bits
        andi    $t0, $v0, 3
        beq     $t0, 0, ismult
        
        li      $v0, SYS_PRINT_STRING
        la      $a0, isnmultstr
        syscall
        j       exit
        
ismult:
        li      $v0, SYS_PRINT_STRING
        la      $a0, ismultstr
        syscall

exit:
        li      $v0, SYS_EXIT
        syscall
