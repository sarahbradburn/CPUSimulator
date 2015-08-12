#include <stdio.h>
#include <stdlib.h>
#include "Register.c"

//Instruction set 
//lw sw
//add sub 
//AND OR slt (as necessary) 
//beq j


//Where will I initialize? 
/*
int memoryArray[100] = {0}; 
int registerArray[32] = {0};	//should be array of structs
*/

int * instructionMemory; 
reg* registers; 
int * memory; 


char* registersToString() {
	int i = 0; 	
	for(i; i < sizeOf(reg); i++) {
		
	} 
} 


int main() {
	//initialize registers

	//initialize memory 
	printf("hello world");

	
	int clock = 0; 
		
	//time driven
	while(clock < 600) {
		clock++;
	}


	return 0;
}
