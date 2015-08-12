#include "Register.h"

struct reg* createReg(char *type, int value) {
	struct reg* newReg = (struct node*) malloc (sizeOf(struct reg));
	
	newReg->type = (char *) malloc(sizeof(char)*(strlen(type)+1));
	newReg->value = value;
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

