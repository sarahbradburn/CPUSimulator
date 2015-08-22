.text				#needed to start program(I think) 
.globl main

main: 	addi $s0, $zero, 4		
		addi $s1, $zero, 3			
		addi $s2, $zero, 5
		addi $s3, $zero, 1

		slt $t0, $s0, $s1
		slt $t1, $s0, $s2
		and $t2, $t0, $t1		#s0 was smallest
		beq $s3, $t2, L0

		slt $t0, $s1, $s0
		slt $t1, $s1, $s2
		and $t2, $t0, $t1		#s1 was smallest
		beq $s3, $t2, L1

		slt $t0, $s2, $s1
		slt $t1, $s2, $s0
		and $t2, $t0, $t1		#s2 was smallest
		beq $s3, $t2, L2

L0:		add $v1, $s1, $s2
		j End
L1:		add $v1, $s0, $s2
		j End
L2:		add $v1, $s1, $s0
		j End

End:	li $v0, 10						
		syscall
