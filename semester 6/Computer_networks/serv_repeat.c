#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
	int socketfd, clisock, portno, msgsize;
	char buffer[256];
	unsigned int clientlen;
	struct sockaddr_in serv_add, client_add;
	
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd<0)
	{  printf("Error opening socket");
       exit(1);
	}
	
	//Initialize socket structure
	                        //bzero((char*)&serv_add, sizeof(serv_add));
	portno = 8080;
	serv_add.sin_family = AF_INET;
	serv_add.sin_addr.s_addr = INADDR_ANY;   //server's ip address is assigned automatically
	serv_add.sin_port = htons(portno);
	
	if(bind(socketfd, (struct sockaddr *)&serv_add, sizeof(serv_add))<0)
	{ printf("Error binding!");
      exit(1);
	}
	
	listen(socketfd, 5);
    clientlen = sizeof(client_add);
    				
    if((clisock = accept(socketfd, (struct sockaddr *) &client_add, &clientlen))<0)
    { printf("Can't accept!");
         exit(1);
    }
    else
    	printf("Connection to client %s established!", inet_ntoa(client_add.sin_addr));

    for(;;)
    {
    	if((msgsize = recv(clisock, buffer, sizeof(buffer), 0))<0)
		{
			printf("Can't read!");
			exit(1);
		}

		if(strcmp(buffer, "quit\n")==0)
      	{
        	printf("\nClient %s disconnected!", inet_ntoa(client_add.sin_addr));
        	close(clisock);
        	exit(1);
      	}
    
    	printf("\nCLIENT: %s", buffer);
		if(send(clisock, buffer, sizeof(buffer), 0)!=msgsize)
			{
				printf("Error in writing!");
				exit(0);
			}
		   
    }

   	
	close(clisock);		
			
	
	
	return 0;
}

