#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <stdbool.h>
#include "sharedstack.h"

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
}setvalArg;


typedef struct {
	key_t stackKey;
	int data_size;
	int stack_size;
	int stack_top;
	int numele;
	bool notfree;
	
}stackdesc;

struct sembuf Pop;
struct sembuf Vop;


int shstackget(key_t key,int dsize, int ssize, int descid)
{
	int i,j,stackid, shmid;
	stackdesc *info;
	
	info = (stackdesc*)shmat(descid, NULL, 0);
	for(i=0;i<MAX_STACK;i++)
	{
		if(info[i].stackKey==key)
		{
			stackid = i;
			printf("\nStack already exists with ");
			shmdt(info);
			return stackid;
		}
	}
		
	if(i==MAX_STACK)							//cannot find key of stack
	{
		for(j=0;j<MAX_STACK;j++)
		{
			if(info[j].notfree==false)	
			{
				
			    info[j].stackKey = key;
			    info[j].notfree = true;
			    info[j].data_size = dsize;
			    info[j].stack_size = ssize;
			    info[j].stack_top = -1;
			    info[j].numele = 0;
			    
			    Pop.sem_num = 0;
    			Pop.sem_op = -1;
    			Pop.sem_flg = SEM_UNDO;

    			Vop.sem_num = 0;
  				Vop.sem_op = 1;
  				Vop.sem_flg = SEM_UNDO;

				setvalArg.val = 1;

			    shmdt(info);
			    printf("Stack created!\n");
			    return j;
			    
			}	
		}
		
		if(j==MAX_STACK)
		{
			shmdt(info);
			return -2;									// no free stack available to create
		}
			
	}
	
}

void shstackpush(key_t key, int ssize, int descid)
{
	int i, j, shmid, semid, status;
	stackdesc *info;
	int *ibase;
	double *dbase;
	char *cbase;

	info = (stackdesc*)shmat(descid, NULL, 0);
	for(i=0;i<MAX_STACK;i++)
	{
		if(info[i].stackKey==key)
			break;
	}	
	if(i==MAX_STACK)
	{
		printf("No stack associated with the given key!\n");
		shmdt(info);
		return;
	}
	else
	{
		shmid = shmget(key, info[i].data_size*ssize, IPC_CREAT|0777);
		if(shmid==-1)
		    {
		        perror("shmget() failed");
		        shmdt(info);
		        return;
		    }

		semid = semget(key, NO_SEM, IPC_CREAT|0777);
		if(semid == -1) {
		    perror("semget() failed");
		    exit(1);
		}
		ibase = (int*)shmat(shmid,NULL,0);   
	    dbase = (double*)shmat(shmid,NULL,0);   
	    cbase = (char*)shmat(shmid,NULL,0);

	    setvalArg.val = 1;
	    status = semctl(semid, 0, SETVAL, setvalArg);
	    if(status == -1) {
	        perror("semctl() failed");
	        exit(1);
	    }
		printf("\nEnter ");
		if(info[i].data_size==1)
		{
			semop(semid, &Pop, 1);
			info[i].stack_top++;
	    	info[i].numele++;
			fflush(stdin);
			char data;
			printf("character data:");
			scanf(" %c",&data);				//space inside type specifier works as flush
			printf("\n");
			*(cbase+info[i].stack_top) = data;
			//printf("%c",*(base+info[i].stack_top));
			

			for(j=info[i].stack_top;j>=0;j--)
	    	    printf("%c ",*(cbase+j));
	    	semop(semid, &Vop, 1);
		}
		else if (info[i].data_size==4)
		{
			semop(semid, &Pop, 1);
			info[i].stack_top++;
	    	info[i].numele++;
			int data;
			printf("integer data: ");
			scanf("%d",&data);
			*(ibase+info[i].stack_top) = data;
			for(j=info[i].stack_top;j>=0;j--)
	    	    printf("%d ",*(ibase+j));
	    	semop(semid, &Vop, 1);
		}

		else if (info[i].data_size==8)
		{
			semop(semid, &Pop, 1);
			info[i].stack_top++;
	    	info[i].numele++;
			double d_data;
			printf("double data: ");
			scanf("%lf",&d_data);
			*(dbase+info[i].stack_top) = d_data;
			
			for(j=info[i].stack_top;j>=0;j--)
			{
				printf("%f ",*(dbase+j));
			}
			semop(semid, &Vop, 1);
		}
	    	       

		shmdt(cbase);
	    shmdt(ibase);
	    shmdt(dbase);
	}

	shmdt(info);
	


}

void shstackpop(key_t key, int ssize, int descid)
{
	int i, j, shmid, semid, status;
	stackdesc *info;
	int *ibase;
	double *dbase;
	char *cbase;
	info = (stackdesc*)shmat(descid, NULL, 0);
	for(i=0;i<MAX_STACK;i++)
	{
		if(info[i].stackKey==key)
			{	
				break;
			}
	}	
	if(i==MAX_STACK)
	{
		printf("No stack associated with the given key!\n");
		shmdt(info);
		return;
	}
	else
	{
		shmid = shmget(key, info[i].data_size*ssize, IPC_CREAT|0777);
		if(shmid==-1)
		    {
		        perror("shmget() failed");
		        shmdt(info);
		        return;
		    }

		 semid = semget(key, NO_SEM, IPC_CREAT|0777);
		 if(semid == -1) {
		     perror("semget() failed");
		     exit(1);
		 }
	
	    if((info[i].stack_top)==-1)
	    {
	    	printf("\nStack empty! Cannot pop anything!");
	    	shmdt(info);
	    	return;
	    }

	    printf("\nPopped element: ");
	    ibase = (int*)shmat(shmid,NULL,0);
   	    dbase = (double*)shmat(shmid,NULL,0);
   	    cbase = (char*)shmat(shmid,NULL,0);


   	    setvalArg.val = 1;
   	    status = semctl(semid, 0, SETVAL, setvalArg);
   	    if(status == -1) {
   	        perror("semctl() failed");
   	        exit(1);
   	    }

	    if(info[i].data_size==1)
		{
			semop(semid, &Pop, 1);
			char data;
			data = *(cbase+info[i].stack_top);
			printf("%c",data);
			info[i].stack_top--;
	    	info[i].numele--;
	    	semop(semid, &Vop, 1);
		}
		else if (info[i].data_size==4)
		{
			semop(semid, &Pop, 1);
			int data;
			data = *(ibase+info[i].stack_top);
			printf("%d",data);
			info[i].stack_top--;
	    	info[i].numele--;
	    	semop(semid, &Vop, 1);
		}

		else if (info[i].data_size==8)
		{
			semop(semid, &Pop, 1);
			double data;
			data = *(dbase+info[i].stack_top);
			printf("%f",data);
			info[i].stack_top--;
	    	info[i].numele--;
	    	semop(semid, &Vop, 1);
		}
	    

	    shmdt(cbase);
   	    shmdt(ibase);
   	    shmdt(dbase);
	}

	shmdt(info);


}

void shstackrm(key_t key, int ssize, int descid)
{
	int i, j, shmid, semid, status;
	stackdesc *info;
	
	info = (stackdesc*)shmat(descid, NULL, 0);
	for(i=0;i<MAX_STACK;i++)
	{
		if(info[i].stackKey==key)
			{	
				break;
			}
	}	


	if(i==MAX_STACK)
	{
		printf("No stack associated with the given key!\n");
		shmdt(info);
		return;
	}


	else
	{

				shmid = shmget(key, info[i].data_size*ssize, IPC_CREAT|0777);
				if(shmid==-1)
				    {
				        perror("shmget() failed");
				        return;
				    }

				semid = semget(key, NO_SEM, IPC_CREAT|0777);
				if(semid == -1) {
				    perror("semget() failed");
				    exit(1);
				}

				setvalArg.val = 1;
				status = semctl(semid, 0, SETVAL, setvalArg);
				if(status == -1) {
				    perror("semctl() failed");
				    exit(1);
				}

				semop(semid, &Pop, 1);
			    info[i].stackKey = 0;
			    info[i].notfree = false;
			    info[i].data_size = 0;
			    info[i].stack_size = 0;
			    info[i].stack_top = -1;
			    info[i].numele = 0;
			    shmdt(info);

			    shmctl(shmid, IPC_RMID, 0);
			    printf("\nStack removed!\n");
			    semop(semid, &Vop, 1);
		
		}
}

void shstackdisp(key_t key, int ssize, int descid)
{
	int i, j, shmid;
	stackdesc *info;
	int *ibase;
	double *dbase;
	char *cbase;

	info = (stackdesc*)shmat(descid, NULL, 0);
	for(i=0;i<MAX_STACK;i++)
	{
		if(info[i].stackKey==key)
			{	
				break;
			}
	}	


	if(i==MAX_STACK)
	{
		printf("No stack associated with the given key!\n");
		shmdt(info);
		return;
	}
	else
	{
		shmid = shmget(key, info[i].data_size*ssize, IPC_CREAT|0777);
		if(shmid==-1)
		    {
		        perror("shmget() failed");
		        shmdt(info);
		        return;
		    }
		ibase = (int*)shmat(shmid,NULL,0); 
		cbase = (char*)shmat(shmid,NULL,0); 
		dbase = (double*)shmat(shmid,NULL,0); 

		printf("\nCurrent stack:\n");
		if(info[i].stack_top==-1)
			printf("\nNULL");
		else
		{
			if(info[i].data_size==1)
			{
				for(j=info[i].stack_top;j>=0;j--)
					printf("%c\n",*(cbase+j));
			}

			else if(info[i].data_size==4)
			{
				for(j=info[i].stack_top;j>=0;j--)
					printf("%d\n",*(ibase+j));
			}

			else if(info[i].data_size==8)
			{
				for(j=info[i].stack_top;j>=0;j--)
					printf("%f\n",*(dbase+j));
			}

		}

		shmdt(ibase);
		shmdt(dbase);
		shmdt(cbase);

	}
	shmdt(info);
}

void infostack(key_t key, int descid)
{
	int i, j;
	stackdesc *info;

	info = (stackdesc*)shmat(descid, NULL, 0);
	for(i=0;i<MAX_STACK;i++)
	{
		if(info[i].stackKey==key)
			{	
				break;
			}
	}	

	if(i==MAX_STACK)
	{
		printf("No stack associated with the given key!\n");
		shmdt(info);
		return;
	}
	else
	{
		printf("\nInfo of the stack with given key:\n");
		printf("\n Key: %d",info[i].stackKey);
		printf("\n Data size: %d",info[i].data_size);
		printf("\n Stack size: %d",info[i].stack_size);
		printf("\n Stack top: %d",info[i].stack_top );
		printf("\n No. of elements in stack: %d",info[i].numele);
	}

	shmdt(info);

}

void info_all_stacks(int descid)
{
	int i;
	stackdesc *info;

	info = (stackdesc*)shmat(descid, NULL, 0);
	printf("\n Info about all the existing stacks:\n");
	for(i=0;i<MAX_STACK;i++)
	{
		if(info[i].stackKey!=0)
		{
			printf("\n\nStack id: %d\n",i);
			printf("\n Key: %d",info[i].stackKey);
			printf("\n Data size: %d",info[i].data_size);
			printf("\n Stack size: %d",info[i].stack_size);
			printf("\n Stack top: %d",info[i].stack_top );
			printf("\n No. of elements in stack: %d",info[i].numele);
		}
		
	}	


	shmdt(info);

}