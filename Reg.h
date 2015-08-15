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



/*

#ifndef __NODE_H
#define __NODE_H

#include <stdio.h>
#include <stdlib.h>

struct node {
	void *obj;
	struct node *next;
	struct node *prev;
};

struct node* createNode (void *obj);
void freeNode(struct node *node, void (*freeObject)(void *));

#endif 


*/ 

