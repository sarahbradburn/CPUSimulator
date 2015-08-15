#include "Reg.h"
#include <stdio.h> 
#include <stdlib.h>
#include "string.h"

struct reg* createReg(char *type, int value) {
	struct reg* newReg = (struct reg*) malloc (sizeof(struct reg));
	
	newReg->type = (char *) malloc(sizeof(char)*4);
	newReg->value = value;

	return newReg;
}


/*


struct node* createNode(void *obj)
{
	struct node* newNode = (struct node*) malloc (sizeof(struct node));
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->obj = obj;
	return newNode;
}

void freeNode (struct node *node , void (*freeObject)(void *))
{
	if (node == NULL) return;
	(*freeObject)(node->obj);
	free(node);
}


*/

