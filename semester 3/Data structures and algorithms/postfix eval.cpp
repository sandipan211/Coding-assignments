#include<stdio.h>
#include<stdlib.h>
#define SIZE 100
#include<math.h>
struct stack { int top;
               char items[SIZE];
             };

void create(struct stack *p)
  { p->top=-1; }

void push(struct stack *p,char y)
     {   if(p->top==(SIZE-1))
           { printf("\n Overflow!");
             exit(0);
           }
          else
         p->items[++(p->top)]=y;
       return;
     }

char pop(struct stack *p)
     { if(p->top==-1)
          { printf("\n UNDERFLOW!");
            exit(0);
          }
       else
           return(p->items[p->top--]);
     }
int operation(int x,int y,char z)
{ int res;
  switch(z)
  { case '+' : res=x+y-(48*2);
               break;
    case '-' : res=(y-48)-(x-48);
               break;
    case '*' : res=(x-48)*(y-48);
               break;
    case '/' : res=(y-48)/(x-48);
               break;
    case '$' : res=pow((y-48),(x-48));
               break;
   }
  return res;
}

 main()
{ struct stack s;
  char exp[100],symb;
  int i=0,ans,op1,op2,value;
  printf("\n Enter the postfix expression: ");
  scanf("%[^\n]",exp);
   while(exp[i]!='\0')
      {  symb=exp[i];
           if((symb>=48)&&(symb<=57))
             push(&s,symb);
           else
              { op2=pop(&s);
                op1=pop(&s);
                value=operation(op2,op1,symb);
                push(&s,value);
               }
         i++;
       }
   ans=pop(&s);
  printf("\n Answer is: %d",ans+48);
}


