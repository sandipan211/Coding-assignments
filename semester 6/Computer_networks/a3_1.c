#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[]) 
{
        int i, n;
        pid_t p;
        printf("Enter the no.of child processes: \n");
        scanf("%d", &n);
        

        for(i=0;i<n;i++)
        {
                p = fork();
                if(p==0)
                {
                    char *myargv[30] = {argv[i+1], NULL};
                    if(execve(argv[i+1], myargv[i], NULL)==-1)
                        perror("Execution failed");    

                }
        }
  return 0;
}
