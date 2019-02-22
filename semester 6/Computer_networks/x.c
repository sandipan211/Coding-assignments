#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>


void *receivemsg(void *t);

int main(int argc, char* argv[])
{
	int thread, sockS, sockC, portno=5000;
	unsigned int lenC;
	struct sockaddr_in addS, addC;
    pthread_t th;
    char sendmsg[1024];
    void *status;

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

	else
		printf("Connected to client %s\n", inet_ntoa(addC.sin_addr));

	if (pthread_create (&th, NULL, receivemsg, (void *) &sockC) < 0)
        {
        	printf("Error creating thread!\n");
        	return -1;
        }

    

	for(;;)
	{
		// printf("%d\n", *(int*)status);
		// if((*(int*)status)==-2)
		// 	break;
		fgets(sendmsg, 1024, stdin);
		printf("\n");
		if(send(sockC, sendmsg, sizeof(sendmsg), 0)<0)
		{
			printf("Error in writing!");
			return -1;
		}

	}

    printf("pthread_joined");
    pthread_join(th, NULL);
	close(sockC);

}


void *receivemsg(void *c)
{
	int csock = *(int *)c;
	char buffer[1024];
	int msgsize;


    if((msgsize = recv(csock, buffer, sizeof(buffer), 0))<0)
	   {
		printf("Can't read!");
		return;
	   }


	while(msgsize>0)
	{
		if(strcmp(buffer, "quit\n")==0)
    	{
     	  printf("Client disconnected!\n");
     	  close(csock);
    	  //return (void*) -2;
    	  exit(1);
    	}


		printf("CLIENT: %s\n", buffer);
		if((msgsize = recv(csock, buffer, sizeof(buffer), 0))<0)
	    {
		    printf("Can't read!");
		    return;
	    }
	}
	
    // pthread_exit(0);


}
