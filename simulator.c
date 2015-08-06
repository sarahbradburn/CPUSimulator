#include <stdio.h>
#include <stdlib.h>


int memoryArray[100] = {0}; 
int registerArray[32] = {0};	//should I have seperate arrays 
				//for t, s, ect? I think so. 


int main() {
	printf("hello world");

	
	int clock = 0; 
		
	//time driven
	while(clock < 600) {
		clock++;
	}


	return 0;
}
