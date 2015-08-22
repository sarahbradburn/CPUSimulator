.text				#needed to start program(I think) 
.globl main

main: 	addi $t0, $zero, 3			#3
		addi $t1, $zero, 4				#4
		add $t2, $t0, $t1    			#adds 3 and 4
		sub $t3, $t1, $t0
		sw $t2, 0($zero)

	li $v0, 10						#needed to end program
	syscall
