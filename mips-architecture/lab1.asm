.data
        str: .asciiz "Hello world\n"
        num: .word   256

.text
.globl main

main:
        li      $v0, 4          # 4 - print string
        la      $a0, str        # load address of str
        syscall
        
        la      $t0, num        # load address of num
        lw      $s1, 0($t0)     # load (t0 + 0) to s1
        addi    $t2, $s1, 8     # add s1 + 8 to t2
        sw      $t2, 0($t0)     # store t2 to address of (t0 + 0)
        
        li      $v0, 10         # exit
        syscall
