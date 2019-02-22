#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/sem.h>


#define NO_SEM  1
#define P(s) semop(s, &Pop, 1);
#define V(s) semop(s, &Vop, 1);


struct sembuf Pop;
struct sembuf Vop;

int main()
{
    key_t thiskey;
    int *roll;
    int rollnum, shmid, semid, status;
    srand(time(NULL));

    printf("\nEnter roll no.: ");
    scanf("%d",&rollnum);
    //    key_t ftok(const char *pathname, int proj_id);
    thiskey = ftok("/home/sandipan/Academics/semester_6/Operating_systems/teacher.c", 1);
    shmid = shmget(thiskey, sizeof(int), IPC_CREAT|0777);
    if(shmid==-1)
    {
        perror("shmget() failed");
        return -1;
    }
    Pop.sem_num = 0;
    Pop.sem_op = -1;
    Pop.sem_flg = SEM_UNDO;

    Vop.sem_num = 0;
    Vop.sem_op = 1;
    Vop.sem_flg = SEM_UNDO;

    semid = semget(thiskey, NO_SEM, IPC_CREAT|0777);
    if(semid == -1) {
        perror("semget() failed");
        exit(1);
    }


    //    void *shmat(int shmid, const void *shmaddr, int shmflg);
    roll = (int*)shmat(shmid, NULL, 0);

    if((*roll)==-1)
    {
        P(semid);
        *roll = rollnum;                      /*critical section for student*/
        V(semid);
    }

	//    int shmdt(const void *shmaddr);
    shmdt(roll);

    return 0;
}