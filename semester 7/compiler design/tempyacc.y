%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	extern FILE *yyin;
	extern int yylineno;
	void yyerror(char *s);
	int yylex();
	#include"lex.yy.c"
	int scope = 0;
%}


%token WHILE_TOK DO_TOK IF_TOK ELSE_TOK SWITCH_TOK FOR_TOK  CONST_TOK DOUBLE_TOK INT_TOK FLOAT_TOK VOID_TOK  
%token MAIN_TOK  CHAR_TOK  RETURN_TOK 

%token INC_TOK DEC_TOK EQUAL_TOK NOTEQUAL_TOK GTEQ_TOK LTEQ_TOK AND_TOK OR_TOK LSHIFT_TOK RSHIFT_TOK
%token PLUSEQ_TOK MINUSEQ_TOK MULTEQ_TOK DIVEQ_TOK MODEQ_TOK POWER_TOK

%token ID_TOK INTCONST FLOATCONST EXPCONST

%token LPAREN_TOK RPAREN_TOK LCURLY_TOK RCURLY_TOK COMMA_TOK GT_TOK LT_TOK ASSIGN_TOK MINUS_TOK PLUS_TOK
%token SEMICOLON_TOK NOT_TOK XOR_TOK HASH_TOK DOT_TOK DIV_TOK MULT_TOK MODULO_TOK BITAND_TOK BITOR_TOK

%start S
%%

S: 
	datatype  ID_TOK LPAREN_TOK RPAREN_TOK block      {printf("Syntax for Main Function is Ok....\n");}
block:
		LCURLY_TOK  STATEMENTS  blocks  RCURLY_TOK;

blocks: block STATEMENTS blocks                                {}
      |
      ;

STATEMENTS:STATEMENTS  stmt
          |
          ;
stmt:
		SEMICOLON_TOK
		| expression SEMICOLON_TOK		
		| IF_TOK LPAREN_TOK relational_expression RPAREN_TOK nested_block 	// if(relational_exp);
		| IF_TOK LPAREN_TOK arith_expression RPAREN_TOK nested_block 		// if(arith_exp);
		| IF_TOK LPAREN_TOK relational_expression RPAREN_TOK nested_block ELSE_TOK nested_block 	// if(..){...}else{..}


		|
		;




expression:
	datatype ID_TOK 														// int/float/char/double x 
	| ID_TOK 																// a
	| datatype																// 2, 2.5
	| declaration


	| assignment_expression 												// a = 2 or a = b
	| ID_TOK EQUAL_TOK arith_expression 									// a = arith_exp
	| relational_expression 												// a >,<,>=,<=,== b or 2
	| unary_expression														// a++,++a,a--,--a
	| ID_TOK EQUAL_TOK logic_expression 									// a = a||a , a&&a, a^a, !a
	| logic_expression 														// a||a , a&&a , a^a
	| func_call 															// void function()
	| ID_TOK assignment_expression 											// a = func()
	;

datatype: 
			INT_TOK
			| FLOAT_TOK
			| DOUBLE_TOK
			| CHAR_TOK;

declaration:
			datatype id_token												// char a, b, c
			| datatype assign_stmt;											// int a=2, b=3

assign_stmt:
			assign_stmt COMMA_TOK ID_TOK ASSIGN_TOK data
			| ID_TOK ASSIGN_TOK data;

id_token: id_token COMMA_TOK ID_TOK          {}
        | ID_TOK                             {}
        ;

relational_expression:
						rel_operand GT_TOK rel_operand
						| rel_operand LT_TOK rel_operand
						| rel_operand EQUAL_TOK rel_operand
						| rel_operand NOTEQUAL_TOK rel_operand
						| rel_operand GTEQ_TOK rel_operand
						| rel_operand LTEQ_TOK rel_operand
						| LPAREN_TOK relational_expression RPAREN_TOK
						| LPAREN_TOK relational_expression RPAREN_TOK
						| LPAREN_TOK relational_expression RPAREN_TOK logi_operator relational_expression
						|;

rel_operand:
				arith_expression
				| op;

data:
		INTCONST
		| FLOATCONST;

op:
	data
	|ID_TOK;

logi_operator:
				AND_TOK
				| OR_TOK
				| NOT_TOK;

arith_expression:
					op PLUS_TOK op
					| op MINUS_TOK op
					| op DIV_TOK op
					| op MULT_TOK op
					| op MODULO_TOK op
					| op PLUSEQ_TOK op
					| op MINUSEQ_TOK op
					| op DIVEQ_TOK op
					| op MULTEQ_TOK op
					| op MODEQ_TOK op
					| op LSHIFT_TOK op
					| op RSHIFT_TOK op
					| op POWER_TOK op
					| op BITOR_TOK op
					| op BITAND_TOK op
					| op BITOR_TOK op
					| LPAREN_TOK arith_expression RPAREN_TOK
nested_block:
				LCURLY_TOK nested_stmt RCURLY_TOK
				|;

nested_stmt:
				stmt nested_stmt
				|;

int_arg:
		INT_TOK ID_TOK;

float_arg:
		FLOAT_TOK ID_TOK;

double_arg:
		DOUBLE_TOK ID_TOK;

char_arg:
		CHAR_TOK ID_TOK;




int main(int argc, char *argv[])
{
			/*to run the code use the following commands: */
			/*lex lex.l*/
			/*cc lex.yy.c -ll*/
			/*./a.out<teacher.c*/

	yyin = fopen(argv[1], "r");
	while(yylex());

	fclose(yyin);
	
}






%%

int main()
{
   if (yyparse()==0) printf("Parsed Successfully\n");
   else printf("\nParsing Error at Line No %d\n", yylineno);

   return(0);	

}

void yyerror(char *s)
{
	printf("yyerror: %s\n",s);
}
