#include<stdio.h>
#define SIZE 100
int top=-1;
void push(char);
char pop();
char infix[SIZE],postfix[SIZE],stack[SIZE];
char top_ele();
int precedence(char);

 main()
{int i,j=0,popped_symb,ele1,ele2,op1,op2;
 printf("\n Enter the infix expression with single-digit or character operands : ");
 scanf("%[^\n]",infix);
    for(i=0;infix[i]!='\0';i++);
 infix[i]=')';
 infix[i+1]='\0';
 push('(');
    for(i=0;infix[i]!='\0';i++)
       { if(infix[i]!='('&&infix[i]!=')'&&infix[i]!='^'&&infix[i]!='+'&&infix[i]!='-'&&infix[i]!='*'&&infix[i]!='/')
             postfix[j++]=infix[i];
         else if(infix[i]=='(')
                 push(infix[i]);
         else if (infix[i]==')')
             { while((popped_symb=pop())!='(')
                  postfix[j++]=popped_symb;     
		     }
		 else
		     {ele2=infix[i];
		      op2=precedence(ele2);
		      ele1=top_ele();
		      op1=precedence(ele1);
		      
		        if(op2>op1)
		           push(ele2);
		        else
		            { while(op1>=op2)
		                   {popped_symb=pop();
		                    ele1=top_ele();
		                    postfix[j++]=popped_symb;
							op1=precedence(ele1);						   
					       }
					   push(ele2);	   
					}
			 }
	   }
	postfix[j]='\0';
	printf("\n The postfix expression is : %s",postfix);
	
}
	
int precedence(char ch)
  { switch(ch)
     { case '^': return 3;
       case '*': return 2;
       case '/': return 2;
       case '+': return 1;
       case '-': return 1;
       default : return 0;
     }
	 
  }
 
char pop()
{ if(top!=-1)
      return(stack[top--]);
}

char top_ele()
{ if (top!=-1)
     return(stack[top]);
}

void push(char ch)
{ if(top!=SIZE-1)
    { top++;
      stack[top]=ch;
	}
  return;
}
