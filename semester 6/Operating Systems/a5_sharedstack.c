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
#include <string.h>
#define MAX_STACK 10
#define stksize 100

int datasize;
typedef struct {
	key_t stackKey;
	int data_size;
	int stack_size;
	int stack_top;
	int numele;
	bool notfree;
}stackdesc;



int main()
{
	key_t sdesc_key, stk_key;
	int choice, shmid, stkid, data, quit = 0;
	int type;
	//    key_t ftok(const char *pathname, int proj_id);
    sdesc_key = ftok("/home/sandipan/Academics/semester_6/Operating_systems/teacher.c", 1);
    shmid = shmget(sdesc_key, MAX_STACK*sizeof(stackdesc), IPC_CREAT|0777);
	if(shmid==-1)
	    {
	        perror("shmget() failed");
	        return -1;
	    }

	// stk_key = ftok("/home/sandipan/Academics/semester_6/Operating_systems/student.c", 1);
    do
	{
    	printf("\n\nMENU:\n");
		printf("\n1. Create new stack or access existing stack\n2. Push element\n3. Pop element\n4. Remove stack\n5. Display a stack\n6. Show info of a stack\n7. Show info of all stacks\n8. Exit");
		printf("\nNOTE: Always enter a non-zero key.");
		printf("\n\nEnter your choice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter a key: ");
					scanf("%d",&stk_key); 
					printf("\nEnter type of data (1 for int/2 for char/3 for double): ");
					scanf("%d",&type);
					if(type==1)
						datasize = 4;
					else if(type==2)
						datasize = 1;
					else
						datasize = 8;
					stkid = shstackget(stk_key, datasize, stksize, shmid);
					printf("stkid = %d\n", stkid);
					break;

			case 2: printf("\nEnter a key: ");
					scanf("%d",&stk_key);
					shstackpush(stk_key, stksize, shmid);
					break;

			case 3: printf("\nEnter a key: ");
					scanf("%d",&stk_key);
					shstackpop(stk_key, stksize, shmid);
					break;

			case 4: printf("\nEnter a key: ");
					scanf("%d",&stk_key);
					shstackrm(stk_key, stksize, shmid);
					break;

			case 5: printf("\nEnter a key: ");
					scanf("%d",&stk_key);
					shstackdisp(stk_key, stksize, shmid);
					break;

			case 6: printf("\nEnter a key: ");
					scanf("%d",&stk_key);
					infostack(stk_key, shmid);
					break;

			case 7: info_all_stacks(shmid);
					break;

			case 8: quit = 1;
					break;
		}
			
	}while(quit!=1);
    
shmctl(shmid, IPC_RMID, 0);
return 0;
}


