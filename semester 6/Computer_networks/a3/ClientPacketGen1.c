#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <math.h>

#define buflen 2048
long long int lastTS;

char* genPacket(char[], int, int);
long long int getmicrotime();
char* strgen(int);


//./client 10.2.83.59 8080 100 2 cumult2:  run format


int main(int argc, char* argv[])
{
	unsigned short serverport;
	struct sockaddr_in serv_add;
	int sockclient;
	int i, pbytes, ttl, newttl, sid, num_packets, len;
	long long int curr_time;
	char buffer[buflen];
	socklen_t lenS;
	lenS = sizeof(serv_add);
	num_packets = 50;
	FILE *fp;



	long long int avgRTT[num_packets];
	srand(time(NULL));
	serv_add.sin_family = AF_INET;
	serv_add.sin_addr.s_addr = inet_addr(argv[1]);
	serverport = atoi(argv[2]);
	serv_add.sin_port = htons(serverport);
	pbytes = atoi(argv[3]);
	ttl = atoi(argv[4]);

	fp = fopen(argv[5], "a");

	if((sockclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
	{
		perror("\nERROR creating socket");
		return 1;	
	}


	sid = 0;
	while(1)
	{
		//printf("\n");
		sid++;
		newttl = ttl;
		if(sid>num_packets)
		{
			//printf("\nDisconnected from server...\n\n");
			break;
		}
		bzero(buffer, buflen);
		strcpy(buffer, strgen(pbytes));
		strcpy(buffer,genPacket(buffer, newttl, sid));
	//	printf("Packet sent: %s\n", buffer);

		while(1)
		{
				len = strlen(buffer);
				if(sendto(sockclient, buffer, len, 0, (struct sockaddr *)&serv_add, sizeof(serv_add)) < 0)
				{
					perror("\nERROR sending message");
					return 1;	
				}


				bzero(buffer, buflen);
				if (recvfrom(sockclient, buffer, buflen, 0, (struct sockaddr *) &serv_add, &lenS) < 0)
				{
					perror("ERROR receiving message");
					return 1;
				}
				curr_time = getmicrotime();
				newttl = (buffer[10]-'0')*10+(buffer[11]-'0');
				newttl--;
				if(newttl!=0)
				{
					buffer[10] = (newttl/10)+'0';
					buffer[11] = (newttl%10)+'0';
				}

				else
				{
					//fprintf(fp, "%lld\n", (curr_time - lastTS));
					avgRTT[sid-1] = curr_time - lastTS;
					break;
				}

			// 	
			// 	printf("\nRTT delay for packet %d = %lld microseconds", sid, avgRTT[sid-1]);
		}
	}

	long long int avg, sum = 0;
	for(i = 0; i<num_packets;i++)
		sum+=avgRTT[i];
	avg = sum/(long long int)num_packets;
	fprintf(fp, "%d %lld\n", pbytes, avg);


	close(sockclient);
	fclose(fp);
	return 0;

}





char* genPacket(char buffer[], int ttl, int sid)
{
	static char buf[buflen];
	int num, i, idx=0;
	char ts_char[10];
	long long int ts;

	bzero(buf, buflen);
	while(1)
	{
		num = sid/10;
		if(num!=0)
		{
			buf[idx++] = num+'0';
			sid = sid%10;
		}

		else if((idx==0)&&(num==0))
		{
			buf[idx++] = '0';
			sid = sid%10;
			buf[idx++] = sid+'0';
			break;
		}

		else
		{
			buf[idx++] = sid+'0';
			break;
		}
			

	}

	lastTS = getmicrotime();
  	ts = lastTS%100000000;  

	// while(ts>power)
	//       power*=10;

 //    power/=10;

 //    if(ts<1000)
 //    { 	buf[idx++] = '0'; 
 //       	flag = 1;
 //       	digits--;
 //    }                  //ts will always be of 4 bytes

 //  	while(ts!=0)
 //  	{
 //  		num = ts/power;
 //  		if(num!=0)
 //  		{
 //  			buf[idx++] = num+'0';
 //  			ts = ts - power*num;
 //  		}
  		   
 //  		if(power!=1)
 //  			power/=10;
 //  	}
  	bzero(ts_char, 10);
  	sprintf(ts_char, "%lld", ts);
  	strcat(buf, ts_char);
  	idx+=8;

  	if(ttl<10)
  	   {
  	   	  buf[idx++] = '0';
  	   	  buf[idx++] = ttl+'0'; 
  	   }
  	          //done for single digit ttl
  	else
  	{
  		num = ttl/10;
  		ttl = ttl%10;
  		buf[idx++] = num+'0';
  		buf[idx++] = ttl+'0';
  	}

  	for(i=0;buffer[i]!='\0';i++)
  		buf[idx++] = buffer[i];

  	buf[idx++] = '\0';

	return buf;


}

long long int getmicrotime()
{
	struct timeval timer_usec; 
    long long int timestamp_usec;
    if (!gettimeofday(&timer_usec, NULL)) 
      timestamp_usec = ((long long int) timer_usec.tv_sec) * 1000000ll + (long long int) timer_usec.tv_usec;
   
    else 
      timestamp_usec = -1;

  	return timestamp_usec;
}


char* strgen(int len)
{
	static char str[buflen];
	char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	int i , pos;
	
	for (i = 0; i < len; i++)
        {
        	pos = rand()%(int)(sizeof(charset)-1);
        	str[i] = charset[pos];
        }

    str[len] = '\0';
    return str;
}



/* to run the shell script

	sh -e runfile.sh

	
	chmod +x /home/sandipan/Academics/semester_6/Computer_networks/a3/runfile.sh
	./runfile.sh
*/