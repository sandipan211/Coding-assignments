#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int m, n, r, i, j, k, shmid, status;
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
			scanf("%d", &matA[i][j]);
	}

	printf("\n Enter no.of rows for matrix B: ");
	scanf("%d", &n);

	printf("\n Enter no.of columns for matrix B: ");
	scanf("%d", &r);

	int matB[n][r];
	printf("\nEnter the elements of matrix B:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<r;j++)
			scanf("%d", &matB[i][j]);
	}


	int matC[m][r];
	shmid = shmget(IPC_PRIVATE, m*r*sizeof(int), IPC_CREAT|0777);
// 
	for(i=0;i<m;i++)
	{
		for(j=0;j<r;j++)
		{
			int sum = 0;
			pid = fork();
			if(pid==0)
			{
				int *ptr;
				ptr = (int*) shmat(shmid, NULL, 0);
				for(k=0;k<n;k++)
					sum += matA[i][k]*matB[k][j];

				*(ptr+i*r+j) = sum;
				shmdt(ptr);
				exit(0);
			}

			else
			{
				wait(&status);
				
			}
		}
	}

	int *p;
	p = (int*) shmat(shmid, NULL, 0);
	printf("\nMatrix C = A*B:\n");

	for(i=0;i<m;i++)
	{
		printf("\n");
		for(j=0;j<r;j++)
		{
			matC[i][j] = *(p+i*r+j);
			printf("%d ", matC[i][j]);
		}
	}
	shmdt(p);
	printf("\n");
	shmctl(shmid, IPC_RMID, 0);

	return 0;



}