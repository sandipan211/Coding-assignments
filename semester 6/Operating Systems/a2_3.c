#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int fact(int);

int main()

{ 
	pid_t child;
	int i, n, fac;
	printf("Enter the value of n: ");
	scanf("%d", &n);
	int a[n];

	printf("\nEnter %d numbers: ", n);
	for(i=0;i<n;i++)
	{
		scanf("%d", &a[i]);
	}




    for(i=0;i<n;i++)
    {
    	child = fork();
	    if(child==0)
	    {
	       printf("Process created!\n");
           fac = fact(a[i]);
           printf("Factorial of %d computed by child : %d\n\n", a[i], fac);
		   exit(0);
	    }
    }
	

    return 0;



}

int fact (int num)
{
	int f, i;
	if (num==0)
		return 1;
	else
	{
		f = 1;
		for(i=2;i<=num;i++)
		{
			f = f*i;
		}
	}
	

	return f;
}