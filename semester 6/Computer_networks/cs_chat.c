#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>


#define bufsize 100


void *send_msg(void *t);
void user_login(int socketfd);
int a = 0;
char name[bufsize];


int main(int argc, char *argv[])
{
   int clientsock, msgsize, check, rc;
   int portno=5000;
   struct sockaddr_in serv_addr;
   char buffer[bufsize];
   char byemsg[bufsize];
   char extrabuf[bufsize];
   pthread_t tid;
   void *st;

   

   clientsock = socket(AF_INET, SOCK_STREAM, 0);
   if(clientsock<0)
    {  printf("Error opening socket!");
       exit(1);
    }

   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);

   //Connect to server
   check = connect(clientsock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
   if(check<0)
   { printf("Error connecting!\n");
     exit(1);
   }

   user_login(clientsock);
   strcpy(byemsg, "Goodbye, ");
   strcat(byemsg, name);
  
   rc = pthread_create(&tid, NULL, send_msg, (void *) &clientsock);

   if (rc<0)
        {
          printf("Error creating thread!\n");
          exit(1);
        }
   
   


   // for(;;)
   // {
   //      if(a==-2)
   //        break;

       
        while(1)
          {
            
            
            bzero(buffer, bufsize);

            if (recv(clientsock, buffer, sizeof(buffer), 0)<0) 
              {
                printf("ERROR reading from socket\n");
                return 1;
              }

            printf("%s",buffer);

            if(strcmp(buffer, byemsg)==0)
              {
                printf("Chat closed!\n");
                break;
              }

            bzero(buffer, bufsize);
            
            check = recv(clientsock, buffer, sizeof(buffer), 0);
            if (check<0) 
              {
                printf("ERROR reading from socket\n");
                return 1;
              }

            printf("%s\n",buffer);
            if(strcmp(buffer, byemsg)==0)
              {
                printf("Chat closed!\n");
                break;
              }
            
            
     
          }  
     
   pthread_join(tid, NULL);
   close(clientsock);
   return 0;
}

void user_login(int socketfd)
{
  char welcome_msg[bufsize];

  printf("Enter username: ");
  fgets(name, bufsize, stdin);

  if(send(socketfd, name, sizeof(name), 0)<0) 
     printf("Error writing to socket!\n");
  if(recv(socketfd, welcome_msg, sizeof(welcome_msg), 0)<0)
    perror("no welcome msg!\n");
  else
    printf("%s\n\n", welcome_msg);

}






void *send_msg(void *c)
{
  int csock = *(int *)c;
  int check = 1;
  char buffer[bufsize];





  while(1)
  {
    
    
    bzero(buffer, bufsize);
    fgets(buffer, bufsize, stdin);
    if(send(csock, buffer, sizeof(buffer), 0)<0) 
       printf("Error writing to socket!\n");

    if(strcmp(buffer, "quit\n")==0)
     break;
    

    bzero(buffer, bufsize);
    fgets(buffer, bufsize, stdin);
    printf("\n");
    if(send(csock, buffer, sizeof(buffer), 0)<0) 
       printf("Error writing to socket!\n");

    if(strcmp(buffer, "quit\n")==0)
     break;

  }

  
  //pthread_exit(0);
}

