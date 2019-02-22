%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include"y.tab.h"
	extern int yylineno;

%}


letter      [a-zA-Z]
digit       [0-9]
newline     (\n)
ws          [ \t]+
string      \"[^"\n]*\"
exponent    ((E|e)("+"|"-")?({digit}+))
float1      {digit}+"."{digit}+{exponent}?		
float2      {digit}+{exponent}
floatnum    ({float1}|{float2})
integer     {digit}+
identifier  ({letter}|"_")({letter}|{digit}|"_")* 

%%

int     {	printf("\n%s -> Token: INT_TOK", yytext);
			return INT_TOK;
		} 
if     {	printf("\n%s -> Token: IF_TOK", yytext);
			return IF_TOK;
		} 
else     {	printf("\n%s -> Token: ELSE_TOK", yytext);
			return ELSE_TOK;
		} 
while     {	printf("\n%s -> Token: WHILE_TOK", yytext);
			return WHILE_TOK;
		} 
for     {	printf("\n%s -> Token: FOR_TOK", yytext);
			return FOR_TOK;
		} 
void     {	printf("\n%s -> Token: VOID_TOK", yytext);
			return VOID_TOK;
		} 
char    {	printf("\n%s -> Token: CHAR_TOK", yytext);
			return CHAR_TOK;
		} 
return  {	printf("\n%s -> Token: RETURN_TOK", yytext);
			return RETURN_TOK;
		} 
default	{	printf("\n%s -> Token: DEFAULT_TOK", yytext);
			return DEFAULT_TOK;
		}
switch  {	printf("\n%s -> Token: SWITCH_TOK", yytext);
			return SWITCH_TOK;
		} 
break   {	printf("\n%s -> Token: BREAK_TOK", yytext);
			return BREAK_TOK;
		} 
case     {	printf("\n%s -> Token: CASE_TOK", yytext);
			return CASE_TOK;
		} 
do     {	printf("\n%s -> Token: DO_TOK", yytext);
			return DO_TOK;
		} 
const     {	printf("\n%s -> Token: CONST_TOK", yytext);
			return CONST_TOK;
		} 
double  {	printf("\n%s -> Token: DOUBLE_TOK", yytext);
			return DOUBLE_TOK;
		} 
float   {	printf("\n%s -> Token: FLOAT_TOK", yytext);
			return FLOAT_TOK;
		} 
"<="	{	printf("\n%s -> Token: LTEQ_TOK", yytext);
			return LTEQ_TOK;
		}
"<"		{	printf("\n%s -> Token: LT_TOK", yytext);
			return LT_TOK;
		}
"=="	{	printf("\n%s -> Token: EQUAL_TOK", yytext);
			return EQUAL_TOK;
		}
">="	{	printf("\n%s -> Token: GTEQ_TOK", yytext);
			return GTEQ_TOK;
		}
">"		{	printf("\n%s -> Token: GT_TOK", yytext);
			return GT_TOK;
		}
"!="	{	printf("\n%s -> Token: NOTEQUAL_TOK", yytext);
			return NOTEQUAL_TOK;
		}
"!"		{	printf("\n%s -> Token: NOT_TOK", yytext);
			return NOT_TOK;
		}
"="		{	printf("\n%s -> Token: ASSIGN_TOK", yytext);
			return ASSIGN_TOK;
		}
"&&"	{	printf("\n%s -> Token: AND_TOK", yytext);
			return AND_TOK;
		}
"||"	{	printf("\n%s -> Token: OR_TOK", yytext);
			return OR_TOK;
		}
"&"		{	printf("\n%s -> Token: BITAND_TOK", yytext);
			return BITAND_TOK;
		}
"^"		{	printf("\n%s -> Token: XOR_TOK", yytext);
			return XOR_TOK;
		}
"|"		{	printf("\n%s -> Token: BITOR_TOK", yytext);
			return BITOR_TOK;
		}
"++"	{	printf("\n%s -> Token: INC_TOK", yytext);
			return INC_TOK;
		}
"+"		{	printf("\n%s -> Token: PLUS_TOK", yytext);
			return PLUS_TOK;
		}
"--"	{	printf("\n%s -> Token: DEC_TOK", yytext);
			return DEC_TOK;
		}
"-"		{	printf("\n%s -> Token: MINUS_TOK", yytext);
			return MINUS_TOK;
		}
"**"	{	printf("\n%s -> Token: POWER_TOK", yytext);
			return POWER_TOK;
		}
"*"		{	printf("\n%s -> Token: MULT_TOK", yytext);
			return MULT_TOK;
		}
"/"		{	printf("\n%s -> Token: DIV_TOK", yytext);
			return DIV_TOK;
		}
"%"		{	printf("\n%s -> Token: MODULO_TOK", yytext);
			return MODULO_TOK;
		}
"{"		{	printf("\n%s -> Token: LCURLY_TOK", yytext);
			return LCURLY_TOK;
		}
"}" 	{	printf("\n%s -> Token: RCURLY_TOK", yytext);
			return RCURLY_TOK;
		}
"[" 	{	printf("\n%s -> Token: SQLBKT_TOK", yytext);
			return SQLBKT_TOK;
		}
"]"		{	printf("\n%s -> Token: SQRBKT_TOK", yytext);
			return SQRBKT_TOK;
		}
"("		{	printf("\n%s -> Token: LPAREN_TOK", yytext);
			return LPAREN_TOK;
		}
")"		{	printf("\n%s -> Token: RPAREN_TOK", yytext);
			return RPAREN_TOK;
		}
","		{	printf("\n%s -> Token: COMMA_TOK", yytext);
			return COMMA_TOK;
		}
";"		{	printf("\n%s -> Token: SEMICOLON_TOK", yytext);
			return SEMICOLON_TOK;
		}
"#"		{	printf("\n%s -> Token: HASH_TOK", yytext);
			return HASH_TOK;
		}
"."		{	printf("\n%s -> Token: DOT_TOK", yytext);
			return DOT_TOK;
		}
":"		{	printf("\n%s -> Token: COLON_TOK", yytext);
			return COLON_TOK;
		}

{newline}     	{
					yylineno++;
				}  
{ws}
{integer}       { 	printf("\n%s -> Token: INTCONST ", yytext); 
					char *temp = strdup(yytext);
					yylval.n.name = (char*)malloc(sizeof(char)*yyleng);
					yylval.n.i_val = (char*)malloc(sizeof(char)*yyleng);
					strncpy(yylval.n.name,temp,yyleng);
					strncpy(yylval.n.i_val,temp,yyleng);
					temp = NULL;
					return 	INTCONST;
				}
{floatnum}       { 	printf("\n\n%s -> Token: FLOATCONST ", yytext); 
					char *temp = strdup(yytext);
					yylval.n.name = (char*)malloc(sizeof(char)*yyleng);
					yylval.n.i_val = (char*)malloc(sizeof(char)*yyleng);
					strncpy(yylval.n.name,temp,yyleng);
					strncpy(yylval.n.i_val,temp,yyleng);
					temp = NULL;
					return 	INTCONST;
					return 	FLOATCONST;
				}

{string}        { 	printf("\n\n%s -> Token: STRING_LITERAL ", yytext); 
					return -3;
				}
{identifier}    { 	
					printf("\n\n%s -> Token: ID_TOK", yytext); 
					char *temp = strdup(yytext);
					yylval.n.name = (char*)malloc(sizeof(char)*yyleng);
					strncpy(yylval.n.name,temp,yyleng);
					temp = NULL;
					return ID_TOK;
				}

%%















