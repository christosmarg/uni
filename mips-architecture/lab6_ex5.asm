.eqv SYS_PRINT_STRING   4
.eqv SYS_READ_WORD      5
.eqv SYS_EXIT           10
.eqv SYS_PRINT_CHAR     11

.data
        inputmsg:    .asciiz "Number (1-255): "
        bounderrstr: .asciiz "Number must be 1-255\n"
        resstr:      .asciiz "Hex: 0x"
        hex:         .ascii "0123456789abcdef"
        
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
        blt     $t0, 1, bounderr
        bgt     $t0, 255, bounderr
        
        li      $v0, SYS_PRINT_STRING
        la      $a0, resstr
        syscall
        
        # Get first 4 bits and shift them 4 bits right
        # so that `t2` can have their value. For example
        # if the number is 50 (00110010):
        #
        # (00110010 & 0xf0) >> 4 = 00110000 >> 4 = 00000011 = 3
        andi    $t1, $t0, 0xf0
        srl     $t2, $t1, 4
        
        # Print first portion (4 bits)
        li      $v0, SYS_PRINT_CHAR
        lb      $a0, hex($t2)
        syscall
        
        # Get last 4 bits. Using 50 as an example again
        # 00110010 & 0x0f = 00000010 = 2
        andi    $t1, $t0, 0x0f
        
        # Grint second portion (4 bits)
        lb      $a0, hex($t1)
        syscall
        
        j       exit
        
bounderr:
        li      $v0, SYS_PRINT_STRING
        la      $a0, bounderrstr
        syscall

exit:
        li      $v0, SYS_EXIT
        syscall
