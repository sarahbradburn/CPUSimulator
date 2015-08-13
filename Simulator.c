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

void initializeRegisters() {
	//malloc for array
	registers = (int *)malloc(sizeof(reg)*32);
	

	registers[0] = "r0"; 
	registers[1] = "at";
	registers[2] = "v0";
	registers[3] = "v1";
	registers[4] = "a0";
	registers[5] = "a1";
	registers[6] = "a2";
	registers[7] = "a3";

	//temporary registers
	int i = 8; 	
	for(i; i < 18; i++) {
		registers[i] = "t" + (i-8);
	}
	
	//memory registers
	int j = 18; 	
	for(i; i < 27; i++) {
		registers[j] = "t" + (j-18);
	}

	registers[27] = "k0"; 
	registers[28] = "k1";
	registers[29] = "gp";
	registers[30] = "sp";
	registers[31] = "ra";
}


char* registersToString() {
	int i = 0; 	
	for(i; i < sizeOf(registers); i++) {

	}
} 

int main() {
	printf("Start Computer");
	
	//initialize instruction array (manually) 
	

	//initialize memory array 


	//initialize registers
	initializeRegisters(); 
	
	//start loop for clock, time driven simulation
	int clock = 0; 
	while(clock < 600) {

		//switch statement for different instructions


		//advance clock for instruction memory 
		clock++;
	}


	//End simulation


	return 0;
}
