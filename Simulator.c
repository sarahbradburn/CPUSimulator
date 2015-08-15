#include <stdio.h>
#include <stdlib.h>
#include "Reg.h"  //or should this be .h? 

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
struct reg* registers; 
int * memory; 

int programCounter;
int sizeOfMemory; 

void initializeRegisters() {
	//malloc for array
	//registers = (int *) malloc(sizeof(struct reg)*32);
	registers = (struct reg *) malloc(sizeof(struct reg)*32);

	//registers[0]->type = "r0";
	registers[0] = *createReg("r0", 0);
	registers[1] = *createReg("at", 0);
	registers[2] = *createReg("v0", 0);
	registers[3] = *createReg("v1", 0);
	registers[4] = *createReg("a0", 0);
	registers[5] = *createReg("a1", 0);
	registers[6] = *createReg("a2", 0);
	registers[7] = *createReg("a3", 0);


	//temporary registers

	int i; 	
	for(i = 8; i < 18; i++) {
		
		registers[i] = *createReg("t" + (i-8), 0);
	}
	
	//memory registers
	int j; 	
	for(j = 18; j < 27; j++) {
		registers[i] = *createReg("s" + (i-18), 0);
	}


	registers[27] = *createReg("k0", 0);
	registers[28] = *createReg("k1", 0);
	registers[29] = *createReg("gp", 0);
	registers[30] = *createReg("sp", 0);
	registers[31] = *createReg("ra", 0);

}


void printRegisters() {
	int i; 	

	//curently, all values are blank
	for(i = 0; i < 32; i++) {
		printf("%s %d \n", registers[i].type, registers[i].value);

	}
} 

int main() {
	printf("Start Computer \n");
	
	//initialize instruction array (manually) 
	//instructionMemory = (int*) calloc(sizeof(int)*50);
	instructionMemory = (int*) calloc(50, sizeof(int));
	
	//initialize memory array 
	//memory = (int*) calloc(sizeof(int)*sizeOfMemory);
	memory = (int*) calloc(sizeOfMemory, sizeof(int));
	
	//initialize registers
	initializeRegisters(); 
	printRegisters();
	
	//start loop for clock, time driven simulation
	while(programCounter < 600) {

		//switch statement for different instructions


		//advance clock for instruction memory 
		programCounter++;
	}


	//End simulation


	return 0;
}
