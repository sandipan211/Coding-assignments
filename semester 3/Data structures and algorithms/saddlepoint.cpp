#include<stdio.h>
#include<conio.h>
 main()
{ int i,j,k,m,n,a[20][20],minr,maxr,minc,maxc,col,flag=0;
 printf("\n Enter no. of rows:");
 scanf("%d",&m);
 printf("\n Enter no. of columns:");
 scanf("%d",&n);
 printf("\n Enter the matrix elements:");
  for (i=0;i<m;i++)
   { for(j=0;j<n;j++)
      scanf("%d",&a[i][j]);
   }
  printf("\n The given matrix is :");
   for(i=0;i<m;i++)
    { printf("\n");
       for(j=0;j<n;j++)
        printf("%d ",a[i][j]);
	 } 
  
  for(i=0;i<m;i++)
   { minr=a[i][0];
      for(j=0;j<n;j++)
       { if(a[i][j]<minr)
          {
		    minr=a[i][j];
		    col=j;
	      } 
	     else
	       col=0;
       }
     maxc=a[0][col];
      for(k=0;k<m;k++)
        { if(a[k][col]>maxc)
            maxc=a[k][col];
		}
     
       if(minr==maxc)
        { flag=1;
          printf("\n Saddle point is %d at position (%d,%d)",a[i][col],i+1,col+1);
		}
       
   }
  for(i=0;i<m;i++)
   { maxr=a[i][0];
      for(j=0;j<n;j++)
        { if(a[i][j]>maxr)
           {maxr=a[i][j];
            col=j;
		   }
		  else
		   col=0;
		}
	 minc=a[0][col];
	   for(k=0;k<m;k++)
	    { if(a[k][col]<minc)
	        minc=a[k][col];
	    
		}
	if(maxr==minc)
	 { flag=1;
	   printf("\n Saddle point is %d at position (%d,%d)",a[i][col],i+1,col+1);
		
	 }
   }
  if(flag==0)
    printf("\n No saddle point!");
getch();
    
}

