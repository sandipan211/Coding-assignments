#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h> /* for semget(2) semop(2) semctl(2) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define NO_SEM  1
#define P(s) semop(s, &Pop, 1);
#define V(s) semop(s, &Vop, 1);
#define nstuds 100
int shmid;
int *roll;
int attregister[nstuds] = {0};


struct sembuf Pop;
struct sembuf Vop;


typedef void (*sighandler_t)(int);
void attendance(int signum) 
{
        
    int i, choice;
    printf("\nATTENDANCE REPORT:");
    printf("\n---------------------------\n");
    for(i=0;i<nstuds;i++)
        printf("%d ", attregister[i]);
    
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
    int semid, status, i=0;


    union semun {
        int              val;    /* Value for SETVAL */
        struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
        unsigned short  *array;  /* Array for GETALL, SETALL */
        struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
    } setvalArg;

    setvalArg.val = 1;
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
    
    Pop.sem_num = 0;
    Pop.sem_op = -1;
    Pop.sem_flg = SEM_UNDO;

    Vop.sem_num = 0;
    Vop.sem_op = 1;
    Vop.sem_flg = SEM_UNDO;

    semid = semget(thiskey, NO_SEM, IPC_CREAT | 0777);
    if(semid == -1) {
        perror("semget() failed");
        exit(1);
    }

    // int semctl(int semid, int semnum, int cmd, ...);
    status = semctl(semid, 0, SETVAL, setvalArg);
    if(status == -1) {
        perror("semctl() failed");
        exit(1);
    }

    *roll = -1; 
    //    sighandler_t signal(int signum, sighandler_t handler);   
    handler = signal(SIGINT, attendance);

    while(1)
    {                                                           
        P(semid);
        if((*roll)!=-1)
        {
            attregister[i] = *roll;                      /*critical section for teacher process*/
            *roll = -1;
            i+=1;
        }

        V(semid);
    }

    
    return 0;

}