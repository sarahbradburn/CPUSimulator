#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Reg.h"  

/*
CPU simulator instruction set 
	lw sw
	add sub addi
	AND OR slt (as necessary) 
	beq j
*/


//Memory and register data structures
int * instructionMemory; 
struct reg* registers; 
int * memory; 

int programCounter;
int sizeOfMemory = 100; 

//Declaring methods 
struct reg* createReg(char *type, int value);
void initializeRegisters();
void printRegisters();
void printMemory();


/** 
 * Storing machine code in instruction memory
 */
void initializeInstructionMemory() {
	instructionMemory = (int*) calloc(50, sizeof(int));
	instructionMemory[0] = 0x20080003;  //addi $t0, $zero, 3 
	instructionMemory[1] = 0x20090004;  //addi $t1, $zero, 4 
	instructionMemory[2] = 0x01095020;  //add $t2, $t0, $t1 
	instructionMemory[3] = 0x0000000c;  //end
}


int main() {
	printf("Start Computer \n");
	
	//initialize all data structures
	initializeInstructionMemory();
	memory = (int*) calloc(sizeOfMemory, sizeof(int));
	initializeRegisters();
	printRegisters();
	printMemory();	

	
	//start loop for clock, time driven simulation (will continue until stop instruction reached) 
	while(programCounter < 4) {
		
		//Uses bit manipulation to isolate all values
		int instruction = instructionMemory[programCounter] >> 26;
		int field1 = instructionMemory[programCounter] >> 21 & 0x01f;    //00000011111;
		int field2 = (instructionMemory[programCounter] >> 16) & 0x01f;  //0000000000011111;
		int field3 = (instructionMemory[programCounter] >> 11) & 0x01f;  //000000000000000011111;
		int field4 = (instructionMemory[programCounter] >> 6) & 0x01f;   //00000000000000000000011111;
		int field5 = instructionMemory[programCounter] & 0x03f;   	     //00000000000000000000000000111111; 
		int addressField = instructionMemory[programCounter] & 0x0000ffff; //00000000000000001111111111111111;
	
		//For debuging only! 
		printf("%d feild1: %d adress: %d \n", instruction, field1, addressField);

/*
	switch(instruction) { 
			//add or subtract			
			case 0: 	
				switch(field5) {
					//add					
					case 32:				
						break;
					//subtract
					case 34:
						break;
					//the stop instruction? 
				
				} 
				break;				 
			//addi									
			case 8: 
				break;	
			//lw
			case 35:
				break;
			//sw		
			case 43:	
				break;
			//add cases for the other instructions 						
			default: //ERROR
		}
		
	*/
	programCounter++; //advance clock for instruction memory (probaly in switch)
	}

	//End simulation
	return 0;

}





/**
 * Allocates for a single register with a type and stored numeric value
 */
struct reg* createReg(char *type, int value) {
	struct reg* newReg = (struct reg*) malloc (sizeof(struct reg));
	
	newReg->type = strdup(type);
	newReg->value = value;
	
	return newReg;
}


/** 
 *	TODO method that changes value of a register that's passed in
 */



/**
 * Initializes all 32 registers with a value 0.  
 * There has to be a better way to do this... think about it. 
 */
void initializeRegisters() {

	//allocate for array
	registers = (struct reg *) malloc(sizeof(struct reg)*32);

	//Register names in order given by SPIM
	char* const names[] = {"r0", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",  "t8", "t9","k0", "k1", "gp", "sp",  "s8", "ra"};

	int i; 
	for(i=0; i < 32; i++) {
		registers[i] = *createReg(names[i], 0);
	}
}


/**
 * Prints name and current value of each register
 */
void printRegisters() {
	int i; 	
	for(i = 0; i < 32; i++) {
		printf("%s 0x%08x \n", registers[i].type, registers[i].value);
	}
	printf("\n");
} 


/** 
 * Prints values of memory locations
 */ 
void printMemory() { 
	printf("Memory \n");
	int i; 	
	for(i = 0; i < 100; i++) {
		printf("%d 0x%08x \n", i, memory[i]);
	}
} 

