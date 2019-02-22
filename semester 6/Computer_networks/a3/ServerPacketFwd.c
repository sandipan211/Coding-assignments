#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


#define buflen 2048
#define pbytes 1300

int main(int argc, char* argv[])
{
	unsigned short serverport, sid;
	struct sockaddr_in serv_add;
	struct sockaddr_in cli_addr;
	int sockserver;
	socklen_t lenC;
	int ttl, num_packets;
	long long int timestamp;
	char buffer[buflen], payload[pbytes];
	char ch_ttl;


	serverport = atoi(argv[1]);
	serv_add.sin_family = AF_INET;
	serv_add.sin_addr.s_addr = INADDR_ANY;
	serv_add.sin_port = htons(serverport);
	lenC = sizeof(cli_addr);

	if((sockserver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
	{
		perror("\nERROR creating socket");
		return 1;	
	}

	if(bind(sockserver, (struct sockaddr *)&serv_add, sizeof(serv_add)) < 0)
	{
		perror("\nError binding!");
		return 1;
	}

	printf("\nWaiting for data packets...");
	
	while(1)
	{
		bzero(buffer, buflen);
		if (recvfrom(sockserver, buffer, buflen, 0, (struct sockaddr *) &cli_addr, &lenC) < 0)
		{
			perror("ERROR receiving message");
			return 1;
		}
		//printf("\nCLIENT: %s", buffer);
		ttl = (buffer[10]-'0')*10+(buffer[11]-'0');
		ttl--;
		if(strcmp(buffer, "quit\n")==0)
		{
			printf("\nClient disconnected...");
			break;
		}


		printf("\n");
		buffer[10] = (ttl/10)+'0';
		buffer[11] = (ttl%10)+'0';
		if(sendto(sockserver, buffer, sizeof(buffer), 0, (struct sockaddr *)&cli_addr, lenC) < 0)
		{
			perror("\nERROR sending message");
			return 1;	
		}

	}

	close(sockserver);
	return 0;

}