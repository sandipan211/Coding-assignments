#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define bufsize 100

void *send_receivemsg(void *t);
void welcome_client(int socketfd);
int identify_client(int socketfd, char buf[bufsize], int mode);


int a = 0;
int count = -1;

struct clientinfo
   {
	char uname[bufsize];
	int sock;
   };


struct clientinfo c[30];

int main(int argc, char* argv[])
{

	int msgsize, sockS, sockC, check = 1, portno=5000;
	unsigned int lenC;
	struct sockaddr_in addS;
    pthread_t th;  
    char buffer[bufsize];  
    void *status;
    
    sockS = socket(AF_INET, SOCK_STREAM, 0);
	if(sockS<0)
	{
		printf("Can't create socket!\n");
		return 1;
	}

	addS.sin_family = AF_INET;
	addS.sin_addr.s_addr = INADDR_ANY;
	addS.sin_port = htons(portno);

	check = bind(sockS, (struct sockaddr *) &addS, sizeof(addS));
	if(check<0)
	{
		printf("Error binding!\n");
		return 1;
	}

	listen(sockS, 5);
	int rc;


	for(;;)
	{

		struct sockaddr_in addC;
		lenC = sizeof(addC);
		sockC = accept(sockS, (struct sockaddr *) &addC, &lenC);
		if(sockC<0)
		{
			printf("Can't accept!\n");
			exit(1);
		}

	    else
	    	{
	    		count++;

	    		welcome_client(sockC);


	    		rc = pthread_create(&th, NULL, send_receivemsg, (void *) &sockC);
				if (rc < 0)
        		{
        			printf("Error creating thread!\n");
        			return -1;
        		}

        		printf("%d", count);
		        if(count==-1)
			       break;
        		
        	}
    	
		 
		
	    
  }
   


   pthread_join(th, NULL);    
   close(sockS);
   return 0;

}



void welcome_client(int socketfd)
{
	char buffer[bufsize];
	char sendbuf[bufsize];
    c[count].sock = socketfd;
	

	bzero(buffer, bufsize);
	if(recv(socketfd, buffer, sizeof(buffer), 0)<0)
		perror("Can't read!");

	strcpy(c[count].uname, buffer);
	printf("Connected to client: %s\n", buffer);

	strcpy(sendbuf, "\t\t\t\t\tWELCOME TO CHAT, ");
	strcat(sendbuf, buffer);
	if(send(socketfd, sendbuf, sizeof(sendbuf), 0)<0)
		perror("Can't write to client!");

}


int identify_client(int socketfd, char buf[bufsize], int mode)
{
	int i, j, res = -9;
	char sendoff[bufsize];
	switch(mode)
	{
		case 1: 	    for(i=0;i<30;i++)
	    				{
	    					if(strcmp(c[i].uname, buf)==0)
	    					{
	    						// printf("%s, %d\n", c[i].uname, i);
	    						res = i;
	    						break;

	    					}
	    				}
	    				break;

	    case 2:		  				
	       				for(j=0;j<30;j++)
	    				{
	    					if(socketfd==c[j].sock)
	    					{
	    						// printf("%s, %d\n", c[j].uname, j);
	    						res = j;
	    						break;

	    					}
	    				}

	    				if(strcmp(buf, "quit\n")==0)
					    {			
	     					printf("Client disconnected: %s\n", c[j].uname);
	     					strcpy(sendoff, "Goodbye, ");
	     					strcat(sendoff, c[j].uname);
	     					if(send(socketfd, sendoff, sizeof(sendoff), 0)<0)
	     						perror("ERROR in sendoff!");
	     					bzero(c[j].uname, bufsize);
	     					c[j].sock = -99;
	     					res = -9;
	     				}

	    				break;
	}

	return res;
}












void *send_receivemsg(void *srsock)
{
	int csock = *(int *)srsock;
	char buffer[bufsize];
	char sendbuf[bufsize];
	char temp[bufsize];         // for storing receiver name in case user leaves midway
	int msgsize, i, j, k;


	// printf("client %d: %s, socket = %d\n", count, c[count].uname,csock);
	// for(i=0;i<30;i++)
	//     printf("user %d: %s  ", i, c[i].uname);
	// for(i=0;i<30;i++)
 //    	printf("%d", c[i].sock);
	while(1)
	{
		
    	bzero(buffer, bufsize);
		if(recv(csock, buffer, sizeof(buffer), 0)<0)
	       perror("Can't read!");


	    

		j = identify_client(csock, buffer, 2);      //mode 2 is to identify the sender in the database
	    if(j==-9)
	    	{
	    		count--;
	    		printf("Online users: %d\n", count+1);
	    		close(csock);
	    		break;
	    	}

	    else
	    {
	    		    i = identify_client(csock, buffer, 1);      //mode 1 is to search for an online receiver
	    	   	    // printf("i=%d, j=%d\n",i, j);

	    		    if(i!=-9)
	    		    	{
	    		    		if(send(c[i].sock, c[j].uname,  sizeof(c[j].uname), 0)<0) 
	    		                perror("ERROR writing to socket!\n");
	    		            strcpy(temp, c[i].uname);

	    		            bzero(buffer, bufsize);
	    		   		    if(recv(c[j].sock, buffer, sizeof(buffer), 0)<0)
	    			    		printf("Can't read!");

	    		    		printf("%s\n", buffer);

	    		    		k = identify_client(csock, temp, 1);
	    		    		if(k!=-9)
	    		    		{
	    		    			if(send(c[k].sock, buffer,  sizeof(buffer), 0)<0) 
	    		     			   perror("Error writing to socket!\n");
	    		    		}
	    		    		else
	    		    		{
	    		    			bzero(sendbuf, bufsize);
	    		    			strcpy(sendbuf, "Sorry, user went offline before your message could be sent!\n\n");
	    		    			if(send(c[j].sock, sendbuf,  sizeof(sendbuf), 0)<0) 
	    		                   perror("ERROR writing to socket!\n");
	    		    		}

	    		    	}

	    		    else
	    		    	   {
	    		    			bzero(sendbuf, bufsize);
	    		    			strcpy(sendbuf, "Sorry, user offline...\n\n");
	    		    			if(send(c[j].sock, sendbuf,  sizeof(sendbuf), 0)<0) 
	    		                   perror("ERROR writing to socket!\n");
	    		    		}


	    }
	   
	    

	}
	// if(count==0)
	// 	return (void*) count;
	
   // pthread_exit(NULL);


}
