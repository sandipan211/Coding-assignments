#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()

{ 
	pid_t child;
	int i, n;
	printf("Enter the value of n: ");
	scanf("%d", &n);


    for(i=1;i<=n;i++)
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