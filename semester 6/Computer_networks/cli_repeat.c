#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include<unistd.h>

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
   int clientsock, portno, msgsize;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   char buffer[256];

  /* if(argc<3) 
    {
       fprintf(stderr, "usage %s hostname port\n", argv[0]);
       exit(0);
    }
    */
   portno = 8080;
   
   clientsock = socket(AF_INET, SOCK_STREAM, 0);
   if(clientsock<0)
    {  printf("Error opening socket!");
       exit(1);
    }
   
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   //memcpy(&serv_addr.sin_addr, server->h_addr,server->h_length);
   serv_addr.sin_port = htons(portno);

   //Connect to server
   if(connect(clientsock, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0)
   { printf("Error connecting!");
     exit(1);
   }

   else
    printf("Connected to server!\n");
   //write message to server
 
    for(;;)
    {
      printf("\nCLIENT: ");
      fgets(buffer, 256, stdin);
    

      if((msgsize = send(clientsock, buffer, sizeof(buffer), 0))<0) 
      {
         printf("Error writing to socket!");
         exit(1);
      }

      if(strcmp(buffer, "quit\n")==0)
      {
        printf("\nDisconnected from server");
        close(clientsock);
        exit(1);
      }

      if (recv(clientsock, buffer, sizeof(buffer), 0)!=msgsize) 
      {
          printf("ERROR reading from socket");
          exit(1);
      }
       
      printf("\nSERVER: %s",buffer);
    }
    
    
    close(clientsock);
    
    
  return 0;
}

