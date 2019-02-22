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

void *send_msg(void *t);
int a = 0;
/*

struct sockaddr             // holds socket info
{
  unsigned short sa_family;
  char sa_data[14];
};  


struct in_addr             //holds 32-bit netid/hostid
{ unsigned long s_addr;
};


struct sockaddr_in        // reference to socket's elements
{
  short int sin_family;
  unsigned short int sin_port; //16-bit port num
  struct in_addr sin_addr;   //32-bit ip addr
  unsigned char sin_zero[8]; //not used
};

struct hostent          // keeps info related to host
{
   char *h_name; 
   char **h_aliases; 
   int h_addrtype;  
   int h_length;    
   char **h_addr_list
	
#define h_addr  h_addr_list[0]
};


struct servent           //keep information related to service and associated ports
{
   char  *s_name; 
   char  **s_aliases; 
   int   s_port;  
   char  *s_proto;
};

*/
int main(int argc, char *argv[])
{
   int ret,clientsock, portno, msgsize;
   struct sockaddr_in serv_addr;
   char buffer[1024];

   pthread_t tid;
   void *st;
 //  struct hostent *server;

  /* if(argc<3) 
    {
       fprintf(stderr, "usage %s hostname port\n", argv[0]);
       exit(0);
    }
    */
   portno = 5000;
   
   clientsock = socket(AF_INET, SOCK_STREAM, 0);
   if(clientsock<0)
    {  printf("Error opening socket!");
       exit(1);
    }
   // server = gethostbyname(argv[1]);
   
   // if (server == 0) {
   //    printf("Error- no such host!");
   //    exit(0);
   // }
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);

   //Connect to server
   if(connect(clientsock, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0)
   { printf("Error connecting!\n");
     exit(1);
   }

  int rc;


   if ((rc = (pthread_create (&tid, NULL, send_msg, (void *) &clientsock))) < 0)
        {
          printf("Error creating thread!\n");
          exit(1);
        }
   
   
    if ((msgsize = recv(clientsock, buffer, sizeof(buffer), 0))<0) 
        {
           printf("ERROR reading from socket\n");
           return 1;
        }


   for(;;)
   {
      printf("SERVER: %s\n",buffer);

      if(strcmp(buffer, "quit\n")==0)
        {
          printf("Chat closed!\n");
          break;
        }

      bzero(buffer, 1024);

      if (recv(clientsock, buffer, sizeof(buffer), 0)<0) 
        {
          printf("ERROR reading from socket\n");
          
        }
      if(strcmp(buffer, "Goodbye, client!")==0)
        {
          printf("Chat closed!\n");
          break;
        }
            
    }
      // ret = (int)st;      
   pthread_join(tid, NULL);
   close(clientsock);
   return 0;
}



void *send_msg(void *c)
{
  int csock = *(int *)c;
  char buffer[1024];
  int msgsize;

  fgets(buffer, 1024, stdin);
  printf("\n");
  
  if((msgsize = send(csock, buffer, sizeof(buffer), 0))<0) 
  {
     printf("Error writing to socket!\n");
  }


  while(msgsize>0)
  {
    if(strcmp(buffer, "quit\n")==0)
    {
     printf("Disconnected from server\n");
     //close(csock);
     // exit(1);
     break;
    }

    fgets(buffer, 1024, stdin);
    printf("\n");

    if((msgsize = send(csock, buffer, sizeof(buffer), 0))<0) 
    {
     printf("Error writing to socket!\n");
    }

  }

  
  //pthread_exit(0);
}

