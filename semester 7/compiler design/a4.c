#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *input;

char terminals[6] = {'i','+', '*', '(', ')','$'};		//also includes epsilon
char non_terminals[5] = {'E','e','T','t','F'};

int findT(char c)
{
	int i;
	//find terminal
	for(i=0;i<6;i++)
		if(c==terminals[i])
			return i;

	return -1;
}

int find_NT(char c)		//find non-terminal
{
	int i;
	for(i=0;i<5;i++)
		if(c==non_terminals[i])
			return i;
	return -1;
}

struct rulepair
 {
 	char lhs[2];
 	char rhs[20];
 }; 

char pstack[20];
int top = -1;

void pushch(char c)
{
	top++;
	pstack[top] = c;
}

void popch()
{
	top--;
}

void dispstack()
{
	int i;
	printf("\nstack:");
	for(i=top;i>=0;i--)
		printf("\n%c",pstack[i]);
}

int parseinput(char buf[], int t[5][6], struct rulepair r[10])
{
	strcat(buf,"$");
	pushch('$');
	pushch('E');

	char auxbuf[10];
	char ipch, stch;
	int stindex, ipindex, j, i=0;

	while(buf[i]!='\0')
	{
		ipch = buf[i];
		//printf("\nipch = %c", ipch);

		if((ipch=='$')&&(pstack[top]=='$'))
		{
			printf("\t\t\t\t\tString accepted!");
			return 0;
		}

		else
		{
			//dispstack();
			stch = pstack[top];
			//printf("\nstch = %c",stch);
			stindex = find_NT(stch);
			//printf("\nstindex = %d",stindex);
			if(stindex!=-1)
			{
				ipindex = findT(ipch);
				//printf("\nipindex = %d",ipindex);
				if(t[stindex][ipindex]==-1)
				{
					//printf("\ntable = %d",t[stindex][ipindex]);
					return -1;
				}
				else
				{
					popch();
					//dispstack();
					memset(auxbuf, '\0', sizeof(auxbuf));
					if(strcmp(r[t[stindex][ipindex]].rhs,"epsilon")!=0)
					{
						//printf("\nrule rhs= %s",r[t[stindex][ipindex]].rhs);
						strcat(auxbuf,r[t[stindex][ipindex]].rhs);
						//printf("\nauxbuf= %s",auxbuf);
						int len;
						for(len=0;auxbuf[len]!='\0';len++);

						for(j=len-1;j>=0;j--)
							pushch(auxbuf[j]);
						//dispstack();
					}


				}
			}

			else
			{
				popch();
				// printf("\ninside else");
				// dispstack();
				i++;
			}
		}
	}

	return 0;
}



int main(int argc, char *argv[])
{
	struct rulepair r[10];
	int token;
	char ch;
	if (argc != 2)
	{
		return -1;
	}

	//make the grammar rules

	int k;
	for(k=0;k<8;k++)
	{
		memset(r[k].lhs,'\0',sizeof(r[k].lhs));
		memset(r[k].rhs,'\0',sizeof(r[k].rhs));
	}


	strcat(r[0].lhs,"E");
	strcat(r[0].rhs,"Te");

	strcat(r[1].lhs,"e");
	strcat(r[1].rhs,"+Te");

	strcat(r[2].lhs,"e");
	strcat(r[2].rhs,"epsilon");

	strcat(r[3].lhs,"T");
	strcat(r[3].rhs,"Ft");

	strcat(r[4].lhs,"t");
	strcat(r[4].rhs,"*Ft");

	strcat(r[5].lhs,"t");
	strcat(r[5].rhs,"epsilon");

	strcat(r[6].lhs,"F");
	strcat(r[6].rhs,"(E)");

	strcat(r[7].lhs,"F");
	strcat(r[7].rhs,"i");

	//make the parsing table
	int ptable[5][6];
	int row, col;
	for(row=0;row<5;row++)
		for(col=0;col<6;col++)
			ptable[row][col] = -1;


	ptable[0][0] = ptable[0][3] = 0;
	ptable[1][1] = 1;
	ptable[1][4] = ptable[1][5] = 2;
	ptable[2][0] = ptable[2][3] = 3;
	ptable[3][2] = 4;
	ptable[3][1] = ptable[3][4] = ptable[3][5] = 5;
	ptable[4][3] = 6;
	ptable[4][0] = 7;

	printf("\nGRAMMAR RULES:\n");
	for(k=0;k<8;k++)
		printf("\n%s -> %s", r[k].lhs, r[k].rhs);

	/* print parsing table*/
	// printf("\n========================================================================================================================================================");
	// printf("\n\ti\t\t+\t\t*\t\t(\t\t)\t\t$");
	// printf("\n========================================================================================================================================================");

	// int m,n;
	// for(m=0;m<5;m++)
	// {
	// 	printf("\n");
	// 	for(n=0;n<7;n++)
	// 	{
	// 		if(n==0)
	// 			printf("%c\t",non_terminals[m]);
	// 		else
	// 			printf("%s -> %s\t\t", r[ptable[m][n-1]].lhs, r[ptable[m][n-1]].rhs);
	// 	}
	// }
	printf("\n");
	int status, linenum=0;
	char ipbuf[100];
	input = fopen(argv[1], "r");

	while (fgets(ipbuf, sizeof(ipbuf), input))
	{
		ipbuf[strcspn(ipbuf, "\n")] = '\0';		//removing trailing \n of fgets 
		printf("\nInput: %s", ipbuf);
		linenum++;

		status = parseinput(ipbuf, ptable, r);
		if(status==-1)
			printf("\nError encountered while parsing line %d", linenum);
		top = -1;
		memset(ipbuf, '\0', sizeof(ipbuf));
		printf("\n");
	}

	fclose(input);
}
