%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include "tokendef_LEX.h"
%}

letter      [a-zA-Z]
digit       [0-9]
newline     (\n)
ws          [ \t]+
string      \"[^"\n]*\"
exponent    ((E)("+"|"-")?({digit}+))		
float1      {digit}+"."{digit}+{exponent}?
float2      {digit}+{exponent}
double      ({float1}|{float2})
integer     {digit}+
identifier  ({letter}|"_")({letter}|{digit}|"_")*   


%%

int     {	printf("Token: INT_TOK");
			return INT_TOK;
		} 
if     {	printf("Token: IF_TOK");
			return IF_TOK;
		} 
else     {	printf("Token: ELSE_TOK");
			return ELSE_TOK;
		} 
while     {	printf("Token: WHILE_TOK");
			return WHILE_TOK;
		} 
for     {	printf("Token: FOR_TOK");
			return FOR_TOK;
		} 
void     {	printf("Token: VOID_TOK");
			return VOID_TOK;
		} 
char     {	printf("Token: CHAR_TOK");
			return CHAR_TOK;
		} 
return     {	printf("Token: RETURN_TOK");
			return RETURN_TOK;
		} 
switch     {	printf("Token: SWITCH_TOK");
			return SWITCH_TOK;
		} 
do     {	printf("Token: DO_TOK");
			return DO_TOK;
		} 
const     {	printf("Token: CONST_TOK");
			return CONST_TOK;
		} 
double  {	printf("Token: DOUBLE_TOK");
			return DOUBLE_TOK;
		} 
float   {	printf("Token: FLOAT_TOK");
			return FLOAT_TOK;
		} 

"<="	{	printf("Token: LTEQ_TOK");
			return LTEQ_TOK;
		}
"<"		{	printf("Token: LT_TOK");
			return LT_TOK;
		}
"=="	{	printf("Token: EQUAL_TOK");
			return EQUAL_TOK;
		}
">="	{	printf("Token: GTEQ_TOK");
			return GTEQ_TOK;
		}
">"		{	printf("Token: GT_TOK");
			return GT_TOK;
		}
"!="	{	printf("Token: NOTEQUAL_TOK");
			return NOTEQUAL_TOK;
		}
"!"		{	printf("Token: NOT_TOK");
			return NOT_TOK;
		}
"="		{	printf("Token: ASSIGN_TOK");
			return ASSIGN_TOK;
		}
"&&"	{	printf("Token: AND_TOK");
			return AND_TOK;
		}
"||"	{	printf("Token: OR_TOK");
			return OR_TOK;
		}
"&"		{	printf("Token: BITAND_TOK");
			return BITAND_TOK;
		}
"|"		{	printf("Token: BITOR_TOK");
			return BITOR_TOK;
		}
"++"	{	printf("Token: INC_TOK");
			return INC_TOK;
		}
"+"		{	printf("Token: PLUS_TOK");
			return PLUS_TOK;
		}
"--"	{	printf("Token: DEC_TOK");
			return DEC_TOK;
		}
"-"		{	printf("Token: MINUS_TOK");
			return MINUS_TOK;
		}
"**"	{	printf("Token: POWER_TOK");
			return POWER_TOK;
		}
"*"		{	printf("Token: MULT_TOK");
			return MULT_TOK;
		}
"/"		{	printf("Token: DIV_TOK");
			return DIV_TOK;
		}
"%"		{	printf("Token: MODULO_TOK");
			return MODULO_TOK;
		}
"{"		{	printf("Token: LCURLY_TOK");
			return LCURLY_TOK;
		}
"}" 	{	printf("Token: RCURLY_TOK");
			return RCURLY_TOK;
		}
"[" 	{	printf("Token: SQLBKT_TOK");
			return SQLBKT_TOK;
		}
"]"		{	printf("Token: SQRBKT_TOK");
			return SQRBKT_TOK;
		}
"("		{	printf("Token: LPAREN_TOK");
			return LPAREN_TOK;
		}
")"		{	printf("Token: RPAREN_TOK");
			return RPAREN_TOK;
		}
","		{	printf("Token: COMMA_TOK");
			return COMMA_TOK;
		}
";"		{	printf("Token: SEMICOLON_TOK");
			return SEMICOLON_TOK;
		}
"#"		{	printf("Token: HASH_TOK");
			return HASH_TOK;
		}
"."		{	printf("Token: DOT_TOK");
			return DOT_TOK;
		}

{newline}       { return -2;}
{integer}       { 	printf("INTCONST "); 
					return 	INTCONST;
				}
{double}        { 	printf("FLOATCONST "); 
					return FLOATCONST;
				}
{string}        { 	printf("STRING LITERAL "); 
					return -3;
				}
{identifier}    { 	printf("ID_TOK"); 
					return ID_TOK;
				}

%%


int main(int argc, char *argv[])
{
	

			/*to run the code use the following commands: */
			/*lex filename.c*/
			/*cc lex.yy.c -ll*/
			/*./a.out<teacher.c*/
	
	int token;
	char ch;
	if (argc != 2)
	{
		return -1;
	}
	yyin = fopen(argv[1], "r");
		while((ch = getc(yyin)) != EOF)
		{
			fseek(yyin, -1, SEEK_CUR);
			token = yylex();
			if(token!=-1)
			{
				printf(" : %d", token);
				printf("\n");
			}
		}

	fclose(yyin);
	
}












