#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int m, n, i, j, shmid, status, avg, sum, num_ele;
	pid_t pid;

	printf("\n Enter no.of rows for matrix A: ");
	scanf("%d", &m);

	printf("\n Enter no.of columns for matrix A: ");
	scanf("%d", &n);

	int matA[m][n];
	printf("\nEnter the elements of matrix A:\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
			scanf("%d",&matA[i][j]);
	}



	int matB[m][n];
	shmid = shmget(IPC_PRIVATE, m*n*sizeof(int), IPC_CREAT|0777);

	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			
			pid = fork();
			if(pid==0)
			{
				
			    num_ele = 1;
			    sum = 0;
				int *p;
				p = (int*) shmat(shmid, NULL, 0);
				sum += matA[i][j];
				if(j>0)									//element exists at the left
				{
					num_ele += 1;
					sum += matA[i][j-1];
				}                       

				if(j<n-1)								//element exists at the right
				{
					num_ele += 1;
					sum += matA[i][j+1];
				}                       
					
				if(i<m-1)								//element exists below
				{
					num_ele += 1;
					sum += matA[i+1][j];
					if(j>0)
					{
						num_ele += 1;
						sum += matA[i+1][j-1];
					}

					if(j<n-1)
					{
						num_ele += 1;
						sum += matA[i+1][j+1];
					}
				}

				if(i>0)								//element exists above
				{
					num_ele += 1;
					sum += matA[i-1][j];
					if(j>0)
					{
						num_ele += 1;
						sum += matA[i-1][j-1];
					}

					if(j<n-1)
					{
						num_ele += 1;
						sum += matA[i-1][j+1];
					}
				}

				avg = sum/num_ele;
				*(p+i*n+j) = avg;
				shmdt(p);
				exit(0);

			}

			else
				wait(&status);
		}

	}

	int *ptr;
	ptr = (int*) shmat(shmid, NULL, 0);
	printf("\nMatrix B:\n");
	for(i=0;i<m;i++)
	{
		printf("\n");
		for(j=0;j<n;j++)
		{
			matB[i][j] = *(ptr+i*n+j);
			printf("%d ", matB[i][j]);
		}
	}
	shmdt(ptr);
	printf("\n");
	shmctl(shmid, IPC_RMID, 0);

    return 0;

}