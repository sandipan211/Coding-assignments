#include<stdio.h>
#include<conio.h>
 main()
{ int i,highest,lowest,num[200],a[100],b[100],mina[100],maxa[100],minb[100],maxb[100],n,count=0,min[2],max[2],s1,s2,b1,b2;
  printf("\nHow many numbers u want to enter?:");
  scanf("%d",&n);
  printf("\n Enter %d numbers:",n);
   for(i=0;i<n;i++)
    scanf("%d",&num[i]);
   for(i=0;i<n/2;i++)
     a[i]=num[i];
   for(i=0;i<n/2;i++)
     b[i]=num[n/2+i];
  
  for(i=0;i<n/2;i=i+2)
   { if(a[i]<a[i+1])
      { mina[i/2]=a[i];
         maxa[i/2]=a[i+1];
        count++;
      }
     else
      {mina[i/2]=a[i+1];
        maxa[i/2]=a[i];
        count++;
	  }
       
   }
   for(i=0;i<n/2;i=i+2)
   { if(b[i]<b[i+1])
      { minb[i/2]=b[i];
         maxb[i/2]=b[i+1];
        count++;
      }
     else
      {minb[i/2]=b[i+1];
        maxb[i/2]=b[i];
        count++;
	  }
       
   }
   s1=mina[0];
   b1=maxa[0];
   for(i=1;i<n/4;i++)
      { if(mina[i]<s1)
         { s1=min[i];
           count++;
           
		 }
		if(maxa[i]>b1)
		{ b1=maxa[i];
		  count++;
		}
	  }
   min[0]=s1;
   max[0]=b1;
   s2=minb[0];
   b2=maxb[0];
    for(i=1;i<n/4;i++)
      { if(minb[i]<s2)
         { s2=min[i];
           count++;
           
		 }
		if(maxb[i]>b2)
		{ b2=maxb[i];
		  count++;
		}
	  }
   min[1]=s2;
   max[1]=b2;
     if(min[0]<min[1])
       { lowest=min[0];
         count++;
	   }
	  else
	   {  lowest=min[1];
	      count++;
       }
	 if (max[0]>max[1])
	  { highest=max[0];
	    count++;
	  }
     else
       { highest=max[1];
         count++;
	   }
  printf("\n Highest and lowest numbers are %d and %d found in %d comparisons",highest,lowest,count);
  getch();
}

