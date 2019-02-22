#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <signal.h>
#include <sys/wait.h>

#define prompt "mysh>"
#define bufsize 1024
#define max_sc 100
#define max_ssc 10
#define pathsize 1024


char* getsubsubcmd(char pstr[]);
int exec_cd(char pstr[]);
int exec_extcmd(char pstr[], char sscmd[]);
int decider(char comb[], int);
void ioredirect(char [], char [], char*);
void piped(char [], char [], char*);

int main()
{
	int i,ctr,j, nsubc, retstat=0;
    int loop=1;
   
	do
	{
    	char command[bufsize];
        char thisdir[pathsize];
    	char parsedstr[max_sc][20];
    	char sscmd[max_ssc];
        char combiners[100][3];
    	printf("\n\n%s ",prompt);
    	
        fgets(command,bufsize,stdin);
    	command[strcspn(command,"\n")]= '\0';  // very important!!!....removes the trailing \n of fgets

        for(i=0;i<100;i++)
            bzero(combiners[i], 3);

        int ncombiners = 0, run = 1;
    	j=0; ctr=0, nsubc=0;

        for(i=0;i<=(strlen(command));i++)
        {
            // if space or NULL found, assign NULL into parsedstr
            if(command[i]==';'||command[i]=='\0'||command[i]=='&'||command[i]=='|'||command[i]=='>'||command[i]=='<')
            {
            	if(command[i]=='&'||command[i]=='|')
            		{
                        
                        if(command[i]=='&')
                        {
                            strcpy(combiners[ncombiners++],"&&");
                            i++;
                        }
                        else if((command[i]=='|')&&(command[i+1]=='|'))
                        {
                            strcpy(combiners[ncombiners++],"||");
                            i++;
                        }
                        else
                            strcpy(combiners[ncombiners++],"|");
                            
                    }
                else if(command[i]==';')
                        strcpy(combiners[ncombiners++],";");
                else if(command[i]=='>')
                        strcpy(combiners[ncombiners++],">");
                else if(command[i]=='<')
                        strcpy(combiners[ncombiners++],"<");

                parsedstr[ctr][j]='\0';
                ctr++;  //for next word
                j=0;    //for next word, init index to 0
                nsubc++;
            }
            else
            {
                parsedstr[ctr][j]=command[i];
                j++;
            }
        }

        for(i=0;i<nsubc;i++)
        {
            printf("\ncombiners %d = %s", i, combiners[i]);
        	strcpy(sscmd, getsubsubcmd(parsedstr[i]));
            if((strcmp(combiners[i],">")==0)||(strcmp(combiners[i],"<")==0))
            {   
                ioredirect(parsedstr[i], parsedstr[i+1],combiners[i]);
                i++;
            	
            }

            else if(strcmp(combiners[i],"|")==0)
            {
                piped(parsedstr[i], parsedstr[i+1],combiners[i]);
                i++;
                printf("\nback!");
            }

            else 
            {
                    if(strcmp(sscmd,"cd")==0)
                        {
                             if(run==1)
                                 retstat = exec_cd(parsedstr[i]);
                             run = decider(combiners[i], retstat);
                             
                                         
                         }
                     else if(strcmp(sscmd,"pwd")==0)         
                         {
                             if(run==1)
                                 {
                                     if(getcwd(thisdir, sizeof(thisdir))!=NULL)
                                         {
                                             retstat = 0;
                                             printf("\n%s\n",thisdir);
                                         }
                                     else
                                         retstat = 1;
                                 }
                             
                             run = decider(combiners[i], retstat);

                         }
                     else if((strcmp(sscmd,"clear")==0)&&(run==1)) 
                         printf("\033[2J\033[1;1H");             /* 033 is the octal of ESC, 2J is for clearing the entire 
                                                                 console/terminal screen (and moves cursor to upper left on
                                                                  DOS ANSI.SYS),1;1H moves the cursor to row 1 and column 1
                                                                 */

                     else if((strcmp(sscmd,"exit")==0)&&(run==1))
                             exit(0);                             // kill(getppid(), SIGKILL); : use to close terminal
                  
                     else
                     {
                        if(run==1)
                            retstat = exec_extcmd(parsedstr[i],sscmd);
                        run = decider(combiners[i], retstat);
                     }   
            }
        }

	} while(1);

}


char* getsubsubcmd(char pstr[])
{
	static char subsubcmd[max_ssc];
	int i;
	for(i=0;i<=(strlen(pstr));i++)
	{
		if(pstr[i]!=' ')
			subsubcmd[i] = pstr[i];
		else 
			break;
	}
	subsubcmd[i] = '\0';
	return subsubcmd;
}

int exec_cd(char pstr[])
{
	char path[pathsize];
	int len,i,j=0,flag=0;
    printf("pstr = %s", pstr);
    bzero(path,pathsize);
	for(i=0;pstr[i]!='\0';i++)
	{
        if(flag==1)
            { path[j] = pstr[i];
              j = j+1;
            }
        if(pstr[i]==' ')
            flag=1;
	}
    path[j] = '\0';

    char cwd[pathsize];
    getcwd(cwd,sizeof(cwd));
	int check, cwdctr = 0;
	for(i=0;cwd[i]!='\0';i++)
	{
		if(cwd[i]=='/')
			cwdctr++;
	}
    if((path[0] != '/')&&(path[0]!='.'))
    {// true for the dir in cwd
        strcat(cwd,"/");
        strcat(cwd,path);
        check = chdir(cwd);
        if(check==-1)
            {
                printf("\nInvalid path!");
                return 1;
            }
    }
    else if(path[0]=='.')
    {
    	int diff, ctr = 1;

    	for(i=0;path[i]!='\0';i++)
    	{
    		if(path[i]=='/')
    			ctr++;
    	}
        printf("cwdct = %d, ctr = %d\n",cwdctr,ctr );
        if(ctr>=cwdctr)
            {
                check = chdir("/");
                if(check==-1)
                    {
                        printf("\nInvalid path!");
                        return 1;
                    }
            }
    	else
        {
          diff = cwdctr-ctr+1;
          bzero(path, pathsize);
    	  for(i=0;cwd[i]!='\0';i++)
    	  {
    	    	if(cwd[i]=='/')
                    diff = diff-1;
                if(diff==0)
                    break;
                else
                    path[i] = cwd[i];
    	  }
          
          check = chdir(path);
          if(check==-1)
              {
                  printf("\nInvalid path!");
                  return 1;
              }
        }
    }
    else
    {//true for dir w.r.t. /
        check = chdir(path);
        if(check==-1)
            {
                printf("\nInvalid path1!");
                return 1;
            }
    }

    return 0;
}


int exec_extcmd(char pstr[], char sscmd[])
{
    int i,status, j=0;
    pid_t p1, pwait;
    char *tokens[100];
    int n;

    tokens[0] = strtok(pstr," ");
    for(n=1;tokens[n-1]!=NULL;n++)                              // get all tokens for subcommand
    {
        tokens[n] = strtok(NULL," ");
        printf("%s\n", tokens[n-1]);
    }

    p1 = fork();
    if(p1==0)
    {  if(execvp(sscmd,tokens)==-1)
       {
           perror("execvp() failed");
           return 1;
       }
    }

      pwait = wait(&status);    
    

    
    // if(strcmp(sscmd,"ls")==0)
    // {
    //     p1 = fork();
    //     if(p1==0)
    //     {  if(execve("/bin/ls",tokens,NULL)==-1)
    //         {
    //             perror("execve() failed for ls");
    //             return 1;
    //         }
    //     }
    //     pwait = wait(&status);

    //     int success;
    //     FILE *fp = popen("echo $?", "r");

    //     fscanf(fp, "%d", &success);
    //     printf("sucess = %d\n", success);
    //     if(success!=0)
    //         i = 1;
    //     else
    //         i = 0;
    //     printf("i = %d\n", i);
    //     pclose(fp);
    //     return i;




    return 0;
}


int decider(char combiners[], int retstat)
{
    if(strcmp(combiners,";")==0)
        return 1;
    else if(strcmp(combiners,"||")==0)
        {
            if(retstat==1)
                return 1;
            else 
                return 0;
        }
        
    else if(strcmp(combiners,"&&")==0)
        {
            if(retstat==0)
                return 1;
            else 
                return 0;
        }
}



void ioredirect(char pstr1[], char pstr2[], char* sym)
{
    char *tokens[100];
    int fd, n, status;
    pid_t p, pwait;

    tokens[0] = strtok(pstr1," ");
    for(n=1;tokens[n-1]!=NULL;n++)                              // get all tokens for subcommand
    {
        tokens[n] = strtok(NULL," ");
    }

    if(strcmp(sym, ">")==0)
    {

        p = fork();
        if(p==0)
        {  
            fd = open(pstr2, O_RDWR|O_CREAT,S_IRWXU);
            dup2(fd, 1);
            if(execvp(tokens[0],tokens)==-1)
           {
               perror("execvp() failed");
               return;
           }
        }
        else
          pwait = wait(&status);   

    }

    else
    {
        p = fork();
        if(p==0)
        {  
            fd = open(pstr2, O_RDONLY,S_IRWXU);
            dup2(fd, 0);
            if(execvp(tokens[0],tokens)==-1)
           {
               perror("execvp() failed");
               return;
           }
        }
        else
          pwait = wait(&status);   
    }


}

void piped(char pstr1[], char pstr2[], char* sym)
{
    pid_t p1, p2, p1wait, p2wait;
    int pipefd[2];
    char *tokens1[100], *tokens2[100];
    int n, status1, status2, save_stdin, save_stdout;

    tokens1[0] = strtok(pstr1," ");
    for(n=1;tokens1[n-1]!=NULL;n++)                              // get all tokens for subcommand
    {
        tokens1[n] = strtok(NULL," ");
    }

    tokens2[0] = strtok(pstr2," ");
    for(n=1;tokens2[n-1]!=NULL;n++)                              // get all tokens for subcommand
    {
        tokens2[n] = strtok(NULL," ");
    }


    pipe(pipefd);
    save_stdin = dup(0);
    save_stdout = dup(1);

    p1 = fork();
    if(p1==0)
    {
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        if(execvp(tokens1[0],tokens1)==-1)
        {
            perror("execvp() failed");
            return;
        }

        
        exit(0);
    }

    p1wait = wait(&status1);
    printf("\nhere");

    p2 = fork();
    if(p2==0)
    {
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        if(execvp(tokens2[0],tokens2)==-1)
        {
            perror("execvp() failed");
            return;
        }

        
        exit(0);
    }

    
    
    p2wait = wait(&status2);
    printf("\nhere");
    dup2(save_stdin, 0);
    dup2(save_stdout, 1);
    close(save_stdin);
    close(save_stdout);
    // else
    // {
    //     dup2(pipefd[0], 0);
    //     if(execvp(tokens2[0],tokens2)==-1)
    //     {
    //         perror("execvp() failed");
    //         return;
    //     }

    //     close(pipefd[0]);
    //     close(pipefd[1]);
    //     pwait = wait(&status);
    // }
        
    // dup2(save_stdin, 0);
    // dup2(save_stdout, 1);
    // close(save_stdin);
    // close(save_stdout);
    return;
}