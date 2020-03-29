#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
struct node { int data;
              struct node* next;
            } *first,*second; 

struct node* create(int info)
   { struct node *p=(struct node*)malloc(sizeof(struct node));
     p->data=info;
     p->next=NULL;
     return p;
   }
   
void insert(struct node** n,int s)
  {   struct node *temp=create(s);
      temp->next=*n;
      *n=temp;
  }


void chunk(int len,char a[],struct node** n)
    { int i,j,k,sum,rem,x,y;
         rem=4-len%4;
        if(len%4==0)
           rem=0;
        for(i=0,j=len-1;i<len/2;i++,j--)
            { x=a[i];
              a[i]=a[j];
              a[j]=x;
			}
		for(i=0;i<rem;i++)
		    strcat(a,"0");
		for(i=0,j=len+rem-1;i<(len+rem)/2;i++,j--)
            { y=a[i];
              a[i]=a[j];
              a[j]=y;
			}
	    for(i=0;i<len+rem;i+=4)
		   {  k=3;
		      sum=0;
		      for(j=i;j<i+4;j++)
		        sum+=(a[j]-48)*pow(10,k--);
             insert(n,sum);       
	       }
	}
	
void display(struct node* n)
  { struct node* np=NULL;
    int first=0;
    while(n!=NULL)
      { insert(&np,n->data);
        n=n->next;
	  }
    while(np!=NULL)
       { 
	       if((first>0)&&(np->data>=100)&&(np->data<1000))
     		 printf("0%d",np->data);
     		 else if((first>0)&&(np->data>=10)&&(np->data<100))
     		    printf("00%d",np->data);
     		      else if((first>0)&&(np->data<10)&&(np->data>=0))
     		         printf("000%d",np->data);
     		              else 
     		                 printf("%d",np->data);
         np=np->next;
         first++;
	   }
  }


struct node* add(struct node* first,struct node* second)     
   { struct node *result=NULL;
     struct node *temp,*prev=NULL;;
     int sum,carry=0;
        while(first!=NULL||second!=NULL)
            {  sum = carry + (first? first->data: 0) + (second? second->data: 0);
               carry = (sum >= 10000)? 1 : 0;
               sum = sum % 10000;
               temp = create(sum);
                 if(result == NULL)
                   result = temp;
                 else
                      prev->next = temp;
              prev  = temp;
               if (first) 
			      first = first->next;
               if (second) 
			      second = second->next;
            }
    if (carry > 0)
      temp->next = create(carry);
    return result;
   }

struct node* subtract(struct node* first,struct node* second)
    {  struct node* result = NULL;
       struct node *temp, *prev = NULL;
       int diff, firstnum=0, secondnum=0, borrow=0;
       while (first != NULL )
      {
        firstnum = ((borrow==0)?first->data:first->data-1);
        secondnum = ((second)?second->data:0);
        if(secondnum<=firstnum)
        {
            diff = firstnum-secondnum;
            borrow = 0;
        }
        else
        {
            diff = firstnum + 10000 - secondnum;
            borrow = 1;
        }
        temp = create(diff);
        if(result == NULL)
            result = temp;
        else
            prev->next = temp;
        prev  = temp;
        if (first) first = first->next;
        if (second) second = second->next;
    }
    return result;
}
	 
int big(char a[],char b[])
  { int i;
     for(i=0;(a[i]!='\0')&&(b[i]!='\0');i++)
         { if(a[i]>b[i])
             return 1;
            else
               return 0;
		 }
  }
main()
{ first=NULL;
  second=NULL;
  struct node *res_add=NULL,*res_subt=NULL;
  int i,x,len1,len2;
  char a[100],b[100];
  printf("\n Enter 1st number:  ");
  gets(a);
  printf("\n Enter 2nd number:  ");
  gets(b);
  for(i=0;a[i]!='\0';i++);
  len1=i;
  for(i=0;b[i]!='\0';i++);
  len2=i;
  
  if(len1>len2)
    { chunk(len1,a,&first);
      chunk(len2,b,&second);
    }
  else if(len1==len2)
    { x=big(a,b);
        if(x)
           { chunk(len1,a,&first);
             chunk(len2,b,&second);
           }
        else
           { chunk(len2,b,&first);
             chunk(len1,a,&second);
		   }
	}
  else
     {   chunk(len2,b,&first);
         chunk(len1,a,&second);
	 }
  res_add=add(first,second);
  printf("\n Added result:       ");display(res_add);
  res_subt=subtract(first,second);
  if(len1>len2)
   { printf("\n Subtracted result:  ");
     display(res_subt);
   }
   else if(len1==len2)
        { 
           if(x)
              { printf("\n Subtracted result:  ");
			    display(res_subt);
              }
			  else
               { printf("\n Subtracted result:  -");
			     display(res_subt);
		       }
         }
	else
    {  printf("\n Subtracted result:  -");
	   display(res_subt);
    }

}
