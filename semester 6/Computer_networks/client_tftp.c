#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 6900
#define RRQ 1
#define WRQ 2
#define DATA 3
#define ACK 4
#define ERR 5
#define PSIZE 516
#define MODE "octet"
#define max_retransmisssions 5
#define prompt "myTFTP> "

int get_sockfd();
void send_file(int, struct sockaddr_in, char[]);
void recv_file(int, struct sockaddr_in, char[]);

int main(int argc, char* argv[])
{
	struct sockaddr_in serv_add;
	int sockclient;

	serv_add.sin_family = AF_INET;
	serv_add.sin_addr.s_addr = inet_addr(argv[1]);
	serv_add.sin_port = htons(PORT);

	sockclient = get_sockfd();
	char op[100] , filename[100];
	while(1)
	{
		bzero(op, 100);
		printf("\n%s", prompt);
		fgets(op, 100, stdin);

		if(strcmp(op,"quit\n")==0)
		{
			break;
		}
		
		if(strcmp(op,"put\n")==0)
		{
			printf("Enter file name: ");
			fgets(filename, 100, stdin);
			filename[strcspn(filename,"\n")]= '\0'; 
			send_file(sockclient, serv_add, filename);
		}

		if(strcmp(op,"get\n")==0)
		{
			printf("Enter file name: ");
			fgets(filename, 100, stdin);
			filename[strcspn(filename,"\n")]= '\0';  
			recv_file(sockclient, serv_add, filename);
		}

	}
}


int recvfromTimeOut(int socket, long sec, long usec)
{
	struct timeval timeout;
	timeout.tv_sec = sec;
	timeout.tv_usec = usec;
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(socket, &fds);

	return select(FD_SETSIZE, &fds, NULL, NULL, &timeout);
				//FD_SETSIZE is the max no of fds an fdset can hold info about
}

int get_sockfd()
{
    int sockfd;
    if ((sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("socket creation");
    }
    return sockfd;
}

void send_file(int csock, struct sockaddr_in serv_addr, char filename[])
{
	char wrqpacket[PSIZE];
	wrqpacket[0] = 0;								// construct wrq packet
	wrqpacket[1] = WRQ;
	strcpy(wrqpacket+2, filename);
	strcpy(wrqpacket+2+strlen(filename)+1 , MODE);
	int packet_len = 2+strlen(filename)+1+strlen(MODE)+1;
	socklen_t lenS;
	lenS = sizeof(serv_addr);
	if(sendto(csock, wrqpacket, packet_len, 0, (struct sockaddr *) &serv_addr, lenS)<0)
		perror("sendto()");
	else
		printf("\nWRQ sent");

	
	struct sockaddr_in reply_addr ;
    socklen_t lenR= sizeof(reply_addr);


    int i, n, res, ackblock, blockno = 0;
    char packet[PSIZE];
    //fd_set sockset;

    FILE *fp;
    fp = fopen(filename, "r");
    if(fp==NULL)
    {
    	perror("Error opening file.");
    }

    while(1)
    {
    	for(i = 1;i<=max_retransmisssions;i++)
    	{
    		bzero(packet, PSIZE);
    		if(recvfrom(csock, packet, PSIZE, 0, (struct sockaddr *) &reply_addr, &lenR)<0)	
				perror("recvfrom()");		// waiting for ACK packet from server
			

			// res = recvfromTimeOut(csock, 0, 10000000);
			// if(res==0)
			// 	printf("\nACK signal not received for block %d, retransmitting...", blockno);
			// else if (res==-1)
			// 	{	printf("ERROR with timer recvfromTimeOut()\n");
			// 		exit(-1);
			// 	}
			//else
			//{
				ackblock = (packet[2]<<8) + packet[3];			/* packet[2] will be MSByte, packet[3] is added 
													    to make the complete block number (int is 2 bytes)*/
				if((packet[1]==ERR)||(ackblock==blockno-1)) 	// block number starts from 1, ack from 0
				{												
					printf("\nError in sending/ACK signal not received for block %d, retransmitting...", blockno);
					if(sendto(csock, wrqpacket, packet_len, 0, (struct sockaddr *) &serv_addr, lenS)<0)
						perror("sendto()");
					
				}	
				else
					break;
			//}
			
			
    	}

    	if(i>max_retransmisssions)
    	{
    		printf("\nExceeded max. retransmisssions");
    		return;
    	}

    	printf("\nACK signal %d \n", blockno);

    	blockno++;
    	bzero(wrqpacket, PSIZE);
    	wrqpacket[0] = 0;
    	wrqpacket[1]=DATA;
    	wrqpacket[2]=blockno>>8;		//get the MSByte of integer blockno
		wrqpacket[3]=blockno%256;		//get the 2nd Byte of integer blockno



		n = fread(wrqpacket+4 , 1 , 512 , fp);	// as per datablock format; reading data from file to send
    	printf("Sending block %d of %d bytes.", blockno, n);
    	if (sendto(csock, wrqpacket, n+4 , 0 , (struct sockaddr *) &reply_addr, lenR)<0)
	    	perror("sendto()");

	    if(n<512)								// last block size would be less than 512 bytes
	    	break;
    }

    fclose(fp);
    printf("\nFile sent successfully");

}


void recv_file(int csock, struct sockaddr_in serv_addr, char filename[])
{
	char rrqpacket[PSIZE];
	bzero(rrqpacket, PSIZE);
	char path[100];
	bzero(path, 100);
	strcpy(path, "/var/lib/tftpboot/");
	strcat(path, filename);

	rrqpacket[0] = 0;								// construct rrq packet
	rrqpacket[1] = RRQ;
	strcpy(rrqpacket+2, filename);
	strcpy(rrqpacket+2+strlen(filename)+1 , MODE);
	int packet_len = 2+strlen(filename)+1+strlen(MODE)+1;
	socklen_t lenS;
	lenS = sizeof(serv_addr);

	if(sendto(csock, rrqpacket, packet_len, 0, (struct sockaddr *) &serv_addr, lenS)<0)
		perror("sendto()");
	else
		printf("\nRRQ sent\n");

	struct sockaddr_in reply_addr ;
    socklen_t lenR= sizeof(reply_addr);

    int i, n, blockno = 0;
    char packet[PSIZE];

    FILE *fp;
    fp = fopen(path, "w");
    if(fp==NULL)
    {
    	perror("fopen()");
    }

    while(1)
    {
    	bzero(packet, PSIZE);
    	n = recvfrom(csock, packet, 516, 0, (struct sockaddr *) &reply_addr, &lenR);
    	printf("\n%d", n);
    	printf("\npac[1] = %d", packet[1]);
    	n = n-4;				// to see if n is less than 512 => it is the last block 
    	if(packet[1]==ERR)
    	{
    		printf("\nFile transfer failed");
    	}

	    fwrite(&packet[4],1,n,fp);
	    printf("\nReceived block %d of size %d bytes", blockno+1, n);

	    bzero(rrqpacket, PSIZE);
		rrqpacket[0]=0;
		rrqpacket[1]=ACK;
		rrqpacket[2]=blockno>>8;
		rrqpacket[3]=blockno%256;

		if(sendto(csock, rrqpacket, 4, 0, (struct sockaddr *) &serv_addr, lenS)<0)
			perror("sendto()");
		else
			printf("\nACK sent\n");

		blockno++;

		if(n<512)
			break;	

    }

    fclose(fp);
}




//sudo chown -R tftp /var/lib/tftpboot: ran this command to enable put
