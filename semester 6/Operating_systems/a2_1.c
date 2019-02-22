#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()

{ 
	pid_t child;
	int i;

    for(i=1;i<=3;i++)
    {
    	child = fork();
	    if(child==0)
	    {
		   printf("Process created!\n");
		   exit(0);
	    }
    }
	

    return 0;



}