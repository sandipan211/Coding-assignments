#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /* for thread functions */
#include <errno.h> /* For the macros used here - EAGAIN, EINVAL, EPERM. etc.*/
#include <math.h>

#define num 20
int sumOfElements(int [], int);
void *add( void *param); 
int arr[num];
struct passedData
{
	int ele1;
	int ele2;
	int iele1;
	int iele2;
};


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
	int size,i,j,status,res,p, iters, isodd,first, nths, count, idx;
	nths = 0;
	first = 1;
	p = 1;
	idx = 0;

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	for (i = 0; i < num; i++)
        pthread_mutex_init(&locks[i], NULL);

    for(i=s/2;i>=1;i/=2)
    	nths += i;


	pthread_t tids[nths];
	struct passedData threadData[nths];

	while(1)
	{
		
		count = 0;
		iters = s/((int)pow(2,p));
		// printf("\niters= %d ",iters);

		for(i=0;i<s;i += (int)pow(2,p))
		{
			if(count<iters)
			{
			
				threadData[idx].ele1 = data[i];
				printf("\nThreadele1[%d]= %d",idx,threadData[idx].ele1);
				threadData[idx].iele1 = i;
				threadData[idx].ele2 = data[i+(int)pow(2,p-1)]; 
				printf("\nThreadele2[%d]= %d",idx,threadData[idx].ele2);
				threadData[idx].iele2 = i+(int)pow(2,p-1);
				data[i] = threadData[idx].ele1 + threadData[idx].ele2;
				count++;
				idx++;
			}
			else
			{
				if((count==iters)&&(first==1))
				{
					data[0] = data[0]+data[i];
					threadData[0].ele1 = threadData[0].ele1+data[i];
					break;
				}

				if((count==iters)&&(isodd==1))
				{
					
					threadData[idx-iters].ele1 = threadData[idx-iters].ele1+data[i];
					//printf("\nThreadele1[%d]= %d",idx-iters,threadData[idx-iters].ele1);
					data[0]  = data[0]+data[i];
					break;
				}
				if((count==iters)&&(isodd==0))
					break;

			}
			
		}
		printf("\n");
		for(i=0;i<s;i++)
			printf("%d ",data[i]);
		first = 0;
		p++;
		if(iters%2!=0)
			isodd = 1;
		else
			isodd = 0;

		if(iters==1)
			break;
	}

	for(i=0;i<nths;i++)
	{

		status = pthread_create(&tids[i], &attr, add, (void*)&threadData[i]);
		if (status != 0) 
		{ 
			fprintf(stderr, "pthread_create() failed: %s.\n", status == EAGAIN?"Insufficient resources to create another thread OR A  system-imposed  limit on the number of threads was encountered.":status == EINVAL?"Invalid settings in attr.":status == EPERM?"No permission to set the scheduling policy and parameters specified in attr.":"Unknown Error");
			exit(1);
		}
		
		
	}
	for(i = 0; i < nths; i++) 			//repair here
	{

	    status = pthread_join(tids[i], NULL);
	    if (status != 0)
	    { 
		    fprintf(stderr, "pthread_join() failed: %s.\n", status == EDEADLK?"A deadlock was detected (e.g., two threads tried to join with each other); or thread specifies the calling thread.":status == EINVAL?"thread is not a joinable thread OR Another thread is already waiting to join with this thread.":status == ESRCH?"No thread with the ID thread could be found.":"Unknown Error");
		    exit(1);
		}
	}
	res = data[0];
	return res;
}


void *add( void *param)
{
	int status, i1, i2;
	struct passedData to_add;
	to_add = *(struct passedData*)param;
	i1 = to_add.iele1;
	i2 = to_add.iele2;
	pthread_mutex_lock(&locks[i1]);
	pthread_mutex_lock(&locks[i2]);
	arr[i1] = to_add.ele1+to_add.ele2;
	// printf("%d",to_add->ele1);
	pthread_mutex_unlock(&locks[i1]);
	pthread_mutex_unlock(&locks[i2]);

//	free(param);
	pthread_exit(0);
}