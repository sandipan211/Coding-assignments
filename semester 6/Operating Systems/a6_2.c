#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /* for thread functions */
#include <errno.h> /* For the macros used here - EAGAIN, EINVAL, EPERM. etc.*/
#include <math.h>

#define num 8
int sumOfElements(int [], int);
void *add( void *param); 
int arr[num];
struct passedData
{
	int *ele1;
	int *ele2;
	int iele1;
	int iele2;
};

struct passedData *threadData;
pthread_mutex_t locks[num];

int main()
{
	int i;
	// printf("\nEnter the no. of elements: ");
	// scanf("%d",&num);
	
	// int arr[num];
	printf("\nEnter array elements: ");
	for(i=0;i<num;i++)
		scanf("%d",&arr[i]);

	

	printf("\nResult: %d",sumOfElements(arr,num));
}

int sumOfElements(int data[],int s)
{
	int size,i,j,status,res,p=1;
	
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	for (i = 0; i < num; i++)
        pthread_mutex_init(&locks[i], NULL);

	while(1)
	{
		size = s/((int)pow(2,p));
		if(size<1)
			break;
		pthread_t tids[size];
		for(i=0;i<size;i++)
		{
			threadData = (struct passedData *)malloc(sizeof(struct passedData));
			threadData->ele1 = &(data[(int)pow(2,p)*i]);
			threadData->iele1 = (int)pow(2,p)*i;
			threadData->ele2 = &(data[(int)pow(2,p)*i+(int)pow(2,p-1)]); 
			threadData->iele2 = (int)pow(2,p)*i+(int)pow(2,p-1); 
			status = pthread_create(&tids[i], &attr, add, threadData);
			if (status != 0) 
			{ 
				fprintf(stderr, "pthread_create() failed: %s.\n", status == EAGAIN?"Insufficient resources to create another thread OR A  system-imposed  limit on the number of threads was encountered.":status == EINVAL?"Invalid settings in attr.":status == EPERM?"No permission to set the scheduling policy and parameters specified in attr.":"Unknown Error");
				exit(1);
			}
			
			
		}
		for(i = 0; i < size; i++) 
		{

		    status = pthread_join(tids[i], NULL);
		    if (status != 0)
		    { 
			    fprintf(stderr, "pthread_join() failed: %s.\n", status == EDEADLK?"A deadlock was detected (e.g., two threads tried to join with each other); or thread specifies the calling thread.":status == EINVAL?"thread is not a joinable thread OR Another thread is already waiting to join with this thread.":status == ESRCH?"No thread with the ID thread could be found.":"Unknown Error");
			    exit(1);
			}
		}
		printf("\n");
		for(j=0;j<s;j++)
			printf("%d ",data[j]);
		p++;
	}
	res = data[0];
	return res;
}


void *add( void *param)
{
	int status, i1, i2;
	struct passedData *to_add;
	to_add = (struct passedData*)param;
	i1 = to_add->iele1;
	i2 = to_add->iele2;
	pthread_mutex_lock(&locks[i1]);
	pthread_mutex_lock(&locks[i2]);
	arr[i1] = *(to_add->ele1)+*(to_add->ele2);
	// printf("%d",to_add->ele1);
	pthread_mutex_unlock(&locks[i1]);
	pthread_mutex_unlock(&locks[i2]);

	free(param);
	pthread_exit(0);
}