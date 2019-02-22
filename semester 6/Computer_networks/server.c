#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include<unistd.h>

void handleClient(int clientsock);

int main(int argc, char* argv[])
{
	int socketfd, clisock, portno;
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

	for(;;)
	{
		    clientlen = sizeof(client_add);
						
			if((clisock = accept(socketfd, (struct sockaddr *) &client_add, &clientlen))<0)
			{ printf("Can't accept!");
		      exit(1);
			}

			handleClient(clisock);
			
			
	}
	
	
	return 0;
}

void handleClient(int clisock)
{
	char buffer[256], sendmsg[256];
	int msgsize;
	if((msgsize = recv(clisock, buffer, sizeof(buffer), 0))<0)
	{
		printf("Can't read!");
		exit(1);;
	}


	while(msgsize>0)
	{
		printf("Message received from client: %s", buffer);
		printf("\n Message for client:");
		fgets(sendmsg, 256, stdin);
		if(send(clisock, sendmsg, sizeof(sendmsg), 0)!=msgsize)
		{
			printf("Error in writing!");
			exit(0);
		}

        if((msgsize = recv(clisock, buffer, sizeof(buffer), 0))<0)
	   {
		printf("Can't read!");
		exit(1);;
	   }


	}
	
	close(clisock);
}
