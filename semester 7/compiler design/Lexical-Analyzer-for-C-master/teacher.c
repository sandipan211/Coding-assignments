#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define nstuds 100
int shmid;
int *roll;
int attregister[nstuds] = {0};

typedef void (*sighandler_t)(int);
void attendance(int signum) 
{

    int i, choice;
    printf("\nATTENDANCE REPORT:");
    printf("\n---------------------------\n");
    
    for(i=0;attregister[i]!=0;i++)
        printf("Roll no. %d: PRESENT\n", attregister[i]);
    
    printf("Close the attendance register? [1 for yes / 0 for no]: ");
    scanf("%d",&choice);
    printf("\n");

    if(choice==1)
    {
        shmdt(roll);
        shmctl(shmid, IPC_RMID, 0);
        kill(0, SIGKILL);
    }

}


int main()
{
    sighandler_t handler;
    key_t thiskey;
    int i=0;

    //    key_t ftok(const char *pathname, int proj_id);
    thiskey = ftok("/home/sandipan/Academics/semester_6/Operating_systems/teacher.c", 1);
    shmid = shmget(thiskey, sizeof(int), IPC_CREAT|0777);
    if(shmid==-1)
    {
        perror("shmget() failed");
        return -1;
    }

    //    void *shmat(int shmid, const void *shmaddr, int shmflg);
    roll = (int*)shmat(shmid, NULL, 0);
    *roll = -1;
        //    sighandler_t signal(int signum, sighandler_t handler);


    handler = signal(SIGINT, attendance);

    while(1)
    {
        if((*roll)!=-1)
        {
            attregister[i] = *roll;
            *roll = -1;
            i+=1;
        }
    }

    
    return 0;

}