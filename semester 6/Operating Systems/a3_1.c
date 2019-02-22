#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[]) 
{
        int i;
        pid_t p;


        for(i=0;i<(argc-1);i++)
        {
                p = fork();
                if(p==0)
                {
                    char *myargv[4] = {argv[i+1], NULL};
                    if(execve(argv[i+1], myargv, NULL)==-1)
                        perror("Execution failed");    

                }
        }
        
        return 0;
}
