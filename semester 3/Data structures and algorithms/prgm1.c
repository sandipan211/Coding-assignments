#include<stdio.h>
void main()
{ int a[10],i,max,min,avg,sum=0;
  printf("Enter the elements:");
    for(i=0;i<10;i++)
      scanf("%d",&a[i]);
    max=a[0];
    min=a[0];
     for(i=0;i<10;i++)
       { if(a[i]>max)
           max=a[i];
         if(a[i]<min)
           min=a[i];
        sum+=a[i];
        }
     avg=sum/10;
     printf("\n max,min,sum and avg are: %d %d %d %d",max,min,sum,avg);
}
