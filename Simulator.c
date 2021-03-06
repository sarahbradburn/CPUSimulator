#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Reg.h"  
#include <unistd.h>
#include <signal.h>


//Memory and register data structures
int * instructionMemory; 
struct reg* registers; 
int * memory; 

int programCounter = 0;
int sizeOfMemory = 10; 
int flag = 0;

//Declaring methods 
struct reg* createReg(char *type, int value);
void initializeRegisters();
void changeRegisterValue(struct reg* r, int value);
void printRegisters();
void printMemory();
void freeArrays();
void clockTick(int sig);


/** 
 * Storing machine code in instruction memory
 */
void initializeInstructionMemory() {
	instructionMemory = (int*) calloc(30, sizeof(int));

	//Program 1: Add two largest of 3 numbers
	instructionMemory[0] = 0x20100004; //initializes s0-s3
	instructionMemory[1] = 0x20110003;
	instructionMemory[2] = 0x20120005;
	instructionMemory[3] = 0x20130001;

	instructionMemory[4] = 0x0211402a;  //s0 = smallest
	instructionMemory[5] = 0x0212482a;
	instructionMemory[6] = 0x01095024;
	instructionMemory[7] = 0x126a0009;

	instructionMemory[8] = 0x0230402a;  //s1 = smallest
	instructionMemory[9] = 0x0232482a;
	instructionMemory[10] = 0x01095024;
	instructionMemory[11] = 0x126a0007;

	instructionMemory[12] = 0x0251402a;  //s2 = smallest
	instructionMemory[13] = 0x0250482a;
	instructionMemory[14] = 0x01095024;
	instructionMemory[15] = 0x126a0005;

	instructionMemory[16] = 0x02321820;  //set output
	instructionMemory[17] = 0x0810001f;

	instructionMemory[18] = 0x02121820;
	instructionMemory[19] = 0x0810001f;

	instructionMemory[20] = 0x02301820;
	instructionMemory[21] = 0x0810001f;

	instructionMemory[22] = 0x0000000c;  //end

/*	
	//Program 2: tests add, addi, subtract, and sw
	instructionMemory[0] = 0x20080003;
	instructionMemory[1] = 0x20090004;
	instructionMemory[2] = 0x01095020;
	instructionMemory[3] = 0x01285822;
	instructionMemory[4] = 0xac0a0000;
	instructionMemory[5] = 0x0000000c;
*/
}


int main() {
	printf("Start Computer \n");

	//initialize all data structures
	initializeInstructionMemory();
	memory = (int*) calloc(sizeOfMemory, sizeof(int));
	initializeRegisters();

	//Alarm as clock
	signal(SIGALRM, clockTick);		
	alarm(1);
	while(flag == 0) {
		pause();
	}
	
	freeArrays();
	printf("\nThe End\n\n");	
	return 0;
}


/**
 * Executes one instruction
 */
void clockTick(int sig) {
	//Uses bit manipulation to isolate all values
	int instruction = (instructionMemory[programCounter] >> 26) & 0x3f; //000111111
	int field1 = instructionMemory[programCounter] >> 21 & 0x01f;    //00000011111;
	int field2 = (instructionMemory[programCounter] >> 16) & 0x01f;  //0000000000011111;
	int field3 = (instructionMemory[programCounter] >> 11) & 0x01f;  //000000000000000011111;
	int field5 = instructionMemory[programCounter] & 0x03f;   	     //00000000000000000000000000111111; 
	int addressField = instructionMemory[programCounter] & 0x0000ffff; //00000000000000001111111111111111;
	int jType = instructionMemory[programCounter] & 0x03ffffff ; //00000011111111111111111111111111
	
	//Print Summary 
	printf("\nProgram Counter: %d op: %d  field1: %d  field2: %d field3 Register: %d address: %d\n", programCounter, instruction, registers[field1].value, registers[field2].value, field3, addressField);

	switch(instruction) { 
		//add or subtract			
		case 0: 	
			switch(field5) {
				//add					
				case 32:;
					int sum = registers[field1].value + registers[field2].value;
					changeRegisterValue(&registers[field3], sum); 			
					programCounter++;
					break;
				//subtract 
				case 34:;
					int difference = registers[field1].value - registers[field2].value;
					changeRegisterValue(&registers[field3], difference); 			
					programCounter++;
					break;
				//slt 
				case 42:;
					int lessThan = 0;
					if(registers[field1].value < registers[field2].value) {
						lessThan = 1;
					}
					changeRegisterValue(&registers[field3], lessThan); 
					programCounter++;
					break;
				//and 
				case 36:;
					int andValue = 0;
					if(registers[field1].value == 1 && registers[field2].value == 1) {
						andValue = 1;
					}
					changeRegisterValue(&registers[field3], andValue); 
					programCounter++;
					break;
				//end
				case 12:;
					flag = 1;  //call exit 
					break;		
			} 
			break;		
		//addi									
		case 8:;
			int sum = registers[field1].value + addressField; 
			changeRegisterValue(&registers[field2], sum);
			programCounter++;
			break;	
		//sw		
		case 43:;	
			int address1 = registers[field1].value + addressField;
			memory[address1] = registers[field2].value;
			programCounter++;
			break;
		//j
		case 2:;
			int moveTo = (jType-(4194304/4))-9;  //this could be off by 1
			programCounter = moveTo;				
			break;
		//beq
		case 4:;
			if(registers[field1].value == registers[field2].value) {
				programCounter = programCounter + addressField;
			} else {
				programCounter++;
			}
			break;
		//illegal operation 
		default:;
			flag = 1;
			break;				
	}
	printf("REGISTERS\n");
	printRegisters();
	printf("MEMORY\n");
	printMemory();	
	printf("\n");

	//Call next alarm
	alarm(1);
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
 *	Changes value of a register that's passed in
 */
void changeRegisterValue(struct reg* r, int value) { 
	r->value = value; 
} 


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
	int i; 	
	for(i = 0; i < sizeOfMemory; i++) {
		printf("%d 0x%08x \n", i, memory[i]);
	}
} 


/**
 * Free data structures
 */
void freeArrays() {
	free(instructionMemory);
	free(registers);
	free(memory);
}
