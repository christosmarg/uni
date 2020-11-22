.data
        numstr1: .asciiz "Number 1: "
        numstr2: .asciiz "Number 2: "
        resstr:  .asciiz "Result\n"
        addstr:  .asciiz "Addition: "
        
.text
.globl main

main:
        li      $v0, 4          
        la      $a0, numstr1    # print first input message
        syscall

        li      $v0, 5          # read first word
        syscall
        move    $t0, $v0        # store input in t0
        
        li      $v0, 4          
        la      $a0, numstr2    # print second input message
        syscall
        
        li      $v0, 5          # read second word
        syscall
        move    $t1, $v0        # store input in t1
        
        li      $v0, 4
        la      $a0, resstr
        syscall
        
        la      $a0, addstr     # don't load 4 to v0, it's already there
        syscall
        
        li      $v0, 1
        add     $t2, $t0, $t1   # add two inputs
        la      $a0, 0($t2)     # load sum and prin it
        syscall
        
        li      $v0, 10         # exit
        syscall
