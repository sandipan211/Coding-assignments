#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

int main()
{
	int m, n, i, j, k, shmid, status, avg, sum, num_ele, diff, pass = 0, flag = 0;
	pid_t pid;
	long bigsum;

	printf("\n Enter the value of 'd': ");
	scanf("%d",&diff);

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

	shmid = shmget(IPC_PRIVATE, m*n*sizeof(int), IPC_CREAT|0777);
	while(1)
	{
		int matB[m][n];
		flag = 0;

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
					//	pid_t wait(int *status);
					wait(&status);
			}

		}

		
		int *ptr;
		pass++;
		//	void *shmat(int shmid, const void *shmaddr, int shmflg);
		ptr = (int*) shmat(shmid, NULL, 0);
		printf("\nMatrix B at pass %d:\n", pass);
		for(i=0;i<m;i++)
		{
			printf("\n");
			for(j=0;j<n;j++)
			{
				matB[i][j] = *(ptr+i*n+j);
				printf("%d ", matB[i][j]);
			}
		}

		//	int shmdt(const void *shmaddr);
		shmdt(ptr);
		printf("\n");

		
		
		int r=0,c=0;
		while((r<m)&&(c<n))
		{
			for(i=r;i<m;i++)
			{
				for(j=0;j<n;j++)
				{
					if(!((i==r)&&(j==c)))
					{
						if(abs(matB[r][c]-matB[i][j])<diff)
						{
							printf("\n Element difference at position [%d][%d] and [%d][%d] less than 'd'\n",r,c,i,j);
							flag = 1;
							break;
						}
					}
				}
				if(flag==1)
					break;
			}

			if(flag==1)
				break;
			c++;
			if(c==n)
			{
				r++;
				c = 0;
			}
		}

		if(flag!=1)
		{
			for(i=0;i<m;i++)
			{
				for(j=0;j<n;j++)
					matA[i][j] = matB[i][j];
			}
		}

		else
			break;
	}


	//	int shmctl(int shmid, int cmd, struct shmid_ds *buf);
	shmctl(shmid, IPC_RMID, 0);

    return 0;

}