#include <stdio.h>
#include <stdlib.h>

//Instruction set 
//lw sw
//add sub 
//AND OR slt (as necessary) 
//beq j


//Where will I initialize? 
int memoryArray[100] = {0}; 
int registerArray[32] = {0};	//should be array of structs

int main() {
	printf("hello world");

	
	int clock = 0; 
		
	//time driven
	while(clock < 600) {
		clock++;
	}


	return 0;
}
