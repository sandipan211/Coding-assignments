#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct node { char name[20];
              struct node* next;
            };
            
 
void insert(struct node** n)
  { struct node *temp,*last;
    char sol_name[20];
	int choice=1;
      do
   {
	 temp=(struct node*)malloc(sizeof(struct node));
	  printf("\n Enter soldier name: ");
	  fflush(stdin);
      gets(sol_name);
      strcpy(temp->name,sol_name);
      
      temp->next=NULL;
      
       if(*n==NULL)
		 {
		    *n=temp;
		  }
  	   else
  	     last->next=temp;
  	   last=temp;
  	  
  	   printf("\n Want to enter another name?(press 1 if yes,else press 0)");
  	   scanf("%d",&choice);
    }while(choice==1);
    last->next=*n; 
  }
  
int display(struct node* head)
  { struct node *t=head;
    int count=1;
    printf("\n \t\t\t\t\t\t\t\t List of soldiers \n \t\t\t\t\t\t-----------------------------------------------------------------");
    printf("\n %s ",t->name);
    t=t->next;
     while(t!=head)
      { printf("\n %s ",t->name);
        t=t->next;
        count++;
      }
    return count;
  }  
  
char* escaper(int num,char *sName,struct node** head)
  { struct node *p=*head;
    struct node *x; 
	int i;
	    if(strcmp(sName,p->name)==0)
	        i=1;
        else
		{
		  p=p->next;
         while(p!=*head)
          { if(strcmp(sName,p->name)==0)
              { 
                break;
			  }
			 p=p->next;
		  }
	    }
	while(p->next!=p)    
	 {
	  for(i=1;i<num;i++)
	   	 {    x=p;
			  p=p->next;
	     }
	  x->next=p->next;
	  free(p);
	  p=x->next;	  
    }
 return p->name;    
}  
  
  
 main()
{ struct node *head=NULL;
  char name[20],esc_name[20];
  srand((unsigned)time(NULL));
  int num,r;
  insert(&head);
  num=display(head);
  r=rand()%num+1;
  printf("\n Enter soldier name from whom count begins: ");
  getchar(); 
  gets(name);
  printf("\n Random number generated: %d",r);
  strcpy(esc_name,escaper(r,name,&head));
  printf("\n Name of the escaping soldier: %s",esc_name);
}
