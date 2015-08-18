#ifndef __REG_H
#define __REG_H

#include <stdio.h> 
#include <stdlib.h>

struct reg { 
	char *type; 	
	int value; 
};
	

struct reg* createReg(char *type, int value);
//Should I have a free reg? 

#endif
