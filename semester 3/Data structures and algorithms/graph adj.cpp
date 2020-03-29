#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int num,k=0;
int a[50][50];
int pathlength[50];
void dfs(int s,int t,int traversed[],int paths[],int index)
{ 

  traversed[s-1]=1;
  paths[index]=s;
  index++;
  int j;
  if(s==t)
    {  
	  for ( j = 0; j<index; j++)
          { printf("%d",paths[j]);
            if(j!=index-1)
             printf(" ->");
          }
        printf("\n");
        pathlength[k]=index-1;
        k++;
	}
  else
    {  for(j=1;j<=num;j++)
          { if(!traversed[j-1]&&a[s][j]==1)
            dfs(j,t,traversed,paths,index);                                                         
		  }
	}	
  index--;
  traversed[s-1]=0; 	

}
void findpaths(int s,int t)
{ int traversed[num];
  int paths[num],i,index;
  index=0;
  for(i=0;i<num;i++)
   traversed[i]=0;
  dfs(s,t,traversed,paths,index);
}

 
       







 main()
{  srand((unsigned)time(NULL));
    int r,i,j,n1,n2,plength,m,choice;
    for (i=0;i<50;i++)
	  pathlength[i]=0;   
    printf("\n Enter the number of nodes: ");
    scanf("%d",&num);
    printf("\n If you want to generate adjacency matrix randomly or manually? (press 1 if randomly,0 if manually)");
    scanf("%d",&choice);
    if (choice)
    {
	  for (i=0;i<=num;i++)
      { for(j=0;j<=num;j++)
           { if((i==0)&&(j==0))
               a[i][j]=0;
                else if (i==0)
                   a[i][j]=j;
                   else if (j==0)
                     a[i][j]=i;
                     else if(i==j)
                       a[i][j]=0;
                     else
                        { if (i==1)
						   {r=rand()%2;
                            a[i][j]=r;
					       }
					       else if(j<i)
					          { for(m=1;m<i;m++)
					              { if(a[m][i]==1)
					                   a[i][m]=1;
					                 if (a[m][i]==0)
					                      a[i][m]=0;
					              }
					             
							  }
						   else
						   {r=rand()%2;
                            a[i][j]=r;
					       }
					}
		   }
	  }
	  printf("\n  Randomly generated adjacency matrix:-");
    for(i=0;i<=num;i++)
     { printf("\n");
        for(j=0;j<=num;j++)
          { if ((i==0)&&(j==0))
              printf("  ");
              else
                printf("%d ",a[i][j]);
		  }
	 }
   }
   else
   { printf("\n Enter the matrix in tabular form also mentioning nodes in it: ");
     for(i=0;i<=num;i++)
	   { for(j=0;j<=num;j++)
	      scanf("%d",&a[i][j]);
        }
       
       printf("\n  Adjacency matrix:-");
    for(i=0;i<=num;i++)
     { printf("\n");
        for(j=0;j<=num;j++)
          { if ((i==0)&&(j==0))
              printf("  ");
              else
                printf("%d ",a[i][j]);
		  }
	 }
   }  
    
	int ctr=0;
	printf("\n Enter source node: ");
	scanf("%d",&n1);
	printf("\n Enter target node: ");
	scanf("%d",&n2);
	printf("\n Enter path length: ");
	scanf("%d",&plength);
	findpaths(n1,n2);
	
	for(i=0;pathlength[i]!=0;i++)
	    { if(pathlength[i]==plength)
		   ctr++;
	    }
    if(ctr)
       printf("\n No. of paths of given length : %d",ctr);
    else
       printf ("\n There exists no path of given length!");
 }
	 

