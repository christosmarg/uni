.eqv SYS_PRINT_WORD     1
.eqv SYS_EXIT           10
.eqv SYS_READ_CHAR      12

.macro isnotdigit(%ch, %lbl)
        # the character must be 0x30 <= c <= 0x39
        # for it to be a digit, otherwise, stop 
        blt     %ch, 0x30, %lbl
        bgt     %ch, 0x39, %lbl
.end_macro

.data
        # max word can be 10 digits long but à
        # we add + 1 byte in case there is '\n' 
        str: .space 11

.text
.globl main

main:
        # init strlen/iterations counter
        li      $t1, 0
        
getdigit:
        li      $v0, SYS_READ_CHAR
        syscall
        # copy $v0 to $t0
        addu    $t0, $v0, $zero
        isnotdigit($t0, atoi)
        # we don't read more than 10 digits
        beq     $t1, 10, atoi
        # save the digit in memory so that we can 
        # retrieve it later
        sb      $t0, str($t1)
        addi    $t1, $t1, 1
        j       getdigit
        
atoi:
        li      $t0, 0
        # init sum
        li      $t3, 0

atoiloop:
        lb      $t2, str($t0)
        # $t1 is the strlen of str so loop as
        # long as $t0 < $t1
        beq     $t0, $t1, exit
        # in case we hit '\n' or '\0'
        isnotdigit($t2, exit)
        
        # get decimal value
        addi    $t2, $t2, -0x30
        mul     $t3, $t3, 10
        add     $t3, $t3, $t2
        addi    $t0, $t0, 1
        j       atoiloop

exit:
        li      $v0, SYS_PRINT_WORD
        la      $a0, 0($t3)
        syscall
        
        li      $v0, SYS_EXIT
        syscall
