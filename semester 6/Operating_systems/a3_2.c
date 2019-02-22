#include <stdio.h>
#include <unistd.h>              //for fork()
#include <stdlib.h>              //for exit()
#include <sys/types.h>           // for wait()
#include <sys/wait.h>            // for wait()
#include <errno.h>               //for perror()

int main(int argc, char *argv[]) 
{
        int i, status;
        pid_t pid, p1;

        for(i=0;i<(argc-1);i++)
        {
                //pid_t fork(void);
                p1 = fork();
                if(p1==0)
                {
                    char *myargv[30] = {argv[i+1], NULL};
                    //int execve(const char *filename, char *const argv[],char *const envp[]);
                    if(execve(argv[i+1], myargv, NULL)==-1)
                        {
                            perror("Execution failed");                          
                            exit(0);
                        }
                    
                        


                }

               // pid_t wait(int *status);
                pid = wait(&status);

                if(WIFEXITED(status))
                    printf("\n Child %d exited normally", pid);
                else if(WIFSIGNALED(status))
                    printf("\n Child %d exited abnormally", pid);
        }
  

        return 0;
}
