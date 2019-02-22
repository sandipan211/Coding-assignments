#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>



void handleClient(int clientsock);
void *sendMsg(void *t);



int main(int argc, char* argv[])
{
	int sockS, sockC, msgsize, portno=5000;
	unsigned int lenC;
	struct sockaddr_in addS, addC;
    pthread_t th;
    char buffer[1024];

    lenC = sizeof(addC);
	if((sockS = socket(AF_INET, SOCK_STREAM, 0))<0)
	{
		printf("Can't create socket!\n");
		exit(1);
	}

	addS.sin_family = AF_INET;
	addS.sin_addr.s_addr = INADDR_ANY;
	addS.sin_port = htons(portno);

	if(bind(sockS, (struct sockaddr *) &addS, sizeof(addS))<0)
	{
		printf("Error binding!\n");
		exit(1);
	}

	listen(sockS, 5);

	if((sockC = accept(sockS, (struct sockaddr *) &addC, &lenC))<0)
		{
			printf("Can't accept!\n");
			exit(1);
		}

	if (pthread_create (&th, NULL, sendMsg, (void *) &sockC) < 0)
        {
        	printf("Error creating thread!\n");
        	exit(1);
        }


	for(;;)
	{
		    if(msgsize = (recv(sockC, buffer, sizeof(buffer), 0))<0)
			   {
				printf("Can't read!");
				exit(1);
			   }


			while(msgsize>0)
			{
				printf("CLIENT: %s", buffer);
				if((msgsize = recv(sockC, buffer, sizeof(buffer), 0))<0)
			    {
				    printf("Can't read!");
				    exit(1);
			    }
			}
		

	}
    pthread_join(th, NULL);

	close(sockC);

}


void *sendMsg(void *c)
{
	int sockC = *(int *)c;
	char buffer[1024];
	int msgsize;


	printf("\nSERVER:");
	fgets(buffer, 1024, stdin);
	if((msgsize = send(sockC, buffer, sizeof(buffer), 0))<0)
	{
		printf("Error in writing!");
		exit(0);
	}

	while(msgsize>0)
	{
		printf("\nSERVERin:");
	    fgets(buffer, 1024, stdin);
	    if((msgsize = send(sockC, buffer, sizeof(buffer), 0))<0)
		{
			printf("Error in writing!");
			exit(0);
		}
	}
	
     pthread_exit(0);


}
