#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


struct reg* createReg(char *type, int value) {
	struct reg* newReg = (struct reg*) malloc (sizeof(struct reg));
	
#if 0
	newReg->type = (char *) malloc(sizeof(char));
	strcpy(
#else
	newReg->type = strdup(type);
#endif
	newReg->value = value;

	return newReg;
}




int * instructionMemory; 
struct reg* registers; 
int * memory; 

int programCounter;
int sizeOfMemory = 100; 

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


	registers[8] = *createReg("t0", 0);
	registers[9] = *createReg("t1", 0);
	registers[10] = *createReg("t2", 0);
	registers[11] = *createReg("t3", 0);
	registers[12] = *createReg("t4", 0);
	registers[13] = *createReg("t5", 0);
	registers[14] = *createReg("t6", 0);
	registers[15] = *createReg("t7", 0);
	registers[16] = *createReg("t8", 0);
	registers[17] = *createReg("t9", 0);


	registers[18] = *createReg("s0", 0);
	registers[19] = *createReg("s1", 0);
	registers[20] = *createReg("s2", 0);
	registers[21] = *createReg("s3", 0);
	registers[22] = *createReg("s4", 0);
	registers[23] = *createReg("s5", 0);
	registers[24] = *createReg("s6", 0);
	registers[25] = *createReg("s7", 0);
	registers[26] = *createReg("s8", 0);
/*
	//temporary registers
	int i; 	
	for(i = 8; i < 18; i++) {
		
		registers[i] = *createReg("t" + (i-8), 0);
	}
	
	//memory registers
	int j; 	
	for(j = 18; j < 27; j++) {
		char * letter = "s";
		char * number = (char *) malloc(sizeof(char)*3); 
		sprintf(number, "%d", j);

		registers[i] = *createReg(strcat(letter, number), 0);
	}

*/
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
	printf("\n");
} 

void printMemory() { 

	printf("Memory \n");
	int i; 	

	//curently, all values are blank
	for(i = 0; i < 100; i++) {
		printf("%d %d \n", i, memory[i]);

	}
} 

void initializeInstructionMemory() {
	instructionMemory = (int*) calloc(50, sizeof(int));
	instructionMemory[0] = 0x20080003;  //addi $t0, $zero, 3 
	instructionMemory[1] = 0x20090004;  //addi $t1, $zero, 4 
	instructionMemory[2] = 0x01095020;  //add $t2, $t0, $t1 
	instructionMemory[3] = 0x0000000c;  //end
}

void printInstructionMemory() { 

	printf("Memory \n");
	int i; 	

	//curently, all values are blank
	for(i = 0; i < 100; i++) {
		printf("%d %d \n", i, memory[i]);

	}
}

int main() {
	printf("Start Computer \n");
		int test = 8; 
		int shifted = test>>2;  			
		printf("%d %d \n", test, shifted);
	
	//initialize instruction array (manually) 
	//instructionMemory = (int*) calloc(sizeof(int)*50);
	initializeInstructionMemory();
	
	//initialize memory array 
	//memory = (int*) calloc(sizeof(int)*sizeOfMemory);
	memory = (int*) calloc(sizeOfMemory, sizeof(int));
	
	//initialize registers
	initializeRegisters(); 
	printRegisters();
	printMemory();	

	
	//start loop for clock, time driven simulation
	while(programCounter < 4) {
		
		int instruction = instructionMemory[programCounter] >> 26;
		int field1 = instructionMemory[programCounter] >> 21 & 0x01f;    //00000011111;
		int field2 = (instructionMemory[programCounter] >> 16) & 0x01f;  //0000000000011111;
		int field3 = (instructionMemory[programCounter] >> 11) & 0x01f;  //000000000000000011111;
		int field4 = (instructionMemory[programCounter] >> 6) & 0x01f;   //00000000000000000000011111;
		int field5 = instructionMemory[programCounter] & 0x01f;   	     //00000000000000000000000000111111;
		int addressField = instructionMemory[programCounter] & 0x0000ffff; //00000000000000001111111111111111;
		printf("%d feild1: %d adress: %d \n", instruction, field1, addressField);
		//switch statement for different instructions
		switch(instruction) { 
			//add or subtract			
			case 0: 	
				switch(field5) {
					//add					
					case 32:				
					
					//subtract
					case 34:
				
				} 
				 
			//addi									
			case 8: 	
			//lw
			case 35:
			//sw		
			case 43:							
		}

		//advance clock for instruction memory 
		programCounter++;
	}


	//End simulation


	return 0;
}
