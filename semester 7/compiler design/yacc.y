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
%token CHAR_TOK  RETURN_TOK CASE_TOK DEFAULT_TOK BREAK_TOK

%token INC_TOK DEC_TOK EQUAL_TOK NOTEQUAL_TOK GTEQ_TOK LTEQ_TOK AND_TOK OR_TOK LSHIFT_TOK RSHIFT_TOK
%token PLUSEQ_TOK MINUSEQ_TOK MULTEQ_TOK DIVEQ_TOK MODEQ_TOK 

%token ID_TOK INTCONST FLOATCONST STRING_LITERAL

%token LPAREN_TOK RPAREN_TOK LCURLY_TOK RCURLY_TOK SQLBKT_TOK SQRBKT_TOK COMMA_TOK GT_TOK LT_TOK ASSIGN_TOK MINUS_TOK PLUS_TOK POWER_TOK
%token SEMICOLON_TOK NOT_TOK XOR_TOK HASH_TOK DOT_TOK DIV_TOK MULT_TOK MODULO_TOK BITAND_TOK BITOR_TOK COLON_TOK 

%start S
%%

S:  datatype ID_TOK SQLBKT_TOK INTCONST SQRBKT_TOK SEMICOLON_TOK S 				// int a[5];
	|declaration SEMICOLON_TOK S 								// int a=3, b=9;
	|datatype  ID_TOK LPAREN_TOK RPAREN_TOK block S
	|datatype ID_TOK LPAREN_TOK function_args RPAREN_TOK block S	// int func(...){ ... }
	|
	;

block:
		LCURLY_TOK  STATEMENTS  blocks  RCURLY_TOK;

blocks: block STATEMENTS blocks                                
      |
      ;

STATEMENTS:STATEMENTS  stmt
          |
          ;
stmt:
		SEMICOLON_TOK
		| expression SEMICOLON_TOK		
		| IF_TOK LPAREN_TOK relational_expression RPAREN_TOK block 					// if(relational_exp);
		| IF_TOK LPAREN_TOK relational_expression RPAREN_TOK block if_else_ladder 
		| SWITCH_TOK LPAREN_TOK op RPAREN_TOK LCURLY_TOK cases RCURLY_TOK		// switch(c){ case ... }
		| entry_ctrl_loop block
		| DO_TOK block WHILE_TOK LPAREN_TOK relational_expression RPAREN_TOK SEMICOLON_TOK 
		| RETURN_TOK op
		;			

entry_ctrl_loop:
				FOR_TOK LPAREN_TOK ID_TOK ASSIGN_TOK op SEMICOLON_TOK relational_expression SEMICOLON_TOK expression RPAREN_TOK
				| WHILE_TOK LPAREN_TOK relational_expression RPAREN_TOK;

cases:
			CASE_TOK INTCONST COLON_TOK STATEMENTS BREAK_TOK SEMICOLON_TOK cases
			| DEFAULT_TOK COLON_TOK STATEMENTS BREAK_TOK SEMICOLON_TOK
			|
			;
			
if_else_ladder:
				ELSE_TOK IF_TOK LPAREN_TOK relational_expression RPAREN_TOK block if_else_ladder
				| ELSE_TOK block;


expression:
			datatype ID_TOK 													// int/float/char/double x 
			| ID_TOK 															// a
			| datatype															// 2, 2.5
			| declaration															
			| assign_stmt
			| unary_expression													// a++,++a,a--,--a
			| ID_TOK EQUAL_TOK logic_expression 								// a = a||a
			| logic_expression 													// a||a , a&&a , a^a
			| call_fn 															//val = sum()														
			;



function_args:

				| function_args COMMA_TOK int_arg  
				| function_args COMMA_TOK char_arg
				| function_args COMMA_TOK float_arg
				| function_args COMMA_TOK double_arg  
				|int_arg
				| float_arg
				| double_arg
				| char_arg    
				;

int_arg:
		INT_TOK ID_TOK;

float_arg:
		FLOAT_TOK ID_TOK;

double_arg:
		DOUBLE_TOK ID_TOK;

char_arg:
		CHAR_TOK ID_TOK;

datatype: 
			INT_TOK
			| FLOAT_TOK
			| DOUBLE_TOK
			| CHAR_TOK;

declaration:
			datatype id_token												// char a, b, c
			| datatype assign_stmt;											// int a=2, b=3

assign_stmt:
			assign_stmt COMMA_TOK ID_TOK ASSIGN_TOK op						// a=3, b=5
			| ID_TOK assign_ops arith_expression							// a = 2+b 
			| ID_TOK assign_ops logic_expression 							// a = b||b
			| ID_TOK assign_ops unary_expression 							// a = k++
			| ID_TOK assign_ops op  										// j = 5.3 or j = k
			| ID_TOK assign_ops call_fn 									// sum = calsum(3,4)
assign_ops:
			ASSIGN_TOK
			| PLUSEQ_TOK 
			| MINUSEQ_TOK 
			| DIVEQ_TOK 
			| MULTEQ_TOK 
			| MODEQ_TOK ;

id_token: id_token COMMA_TOK ID_TOK          {}
        | ID_TOK                             {}
        ;

data:
		INTCONST
		| FLOATCONST
		|STRING_LITERAL;

relational_expression:
						op GT_TOK op
						| op LT_TOK op
						| op EQUAL_TOK op
						| op NOTEQUAL_TOK op
						| op GTEQ_TOK op
						| op LTEQ_TOK op
						| LPAREN_TOK relational_expression RPAREN_TOK
						| LPAREN_TOK relational_expression RPAREN_TOK logi_operator relational_expression
						|;



op:
	data
	|ID_TOK;

logi_operator:
				AND_TOK
				| OR_TOK
				| NOT_TOK
				| XOR_TOK;


unary_expression:
				ID_TOK INC_TOK 								// a++
				| ID_TOK DEC_TOK 							// a--
				| INC_TOK ID_TOK 							// ++a
				| DEC_TOK ID_TOK 							// --a
				;

logic_expression:
					logi_operator op
					|op logi_operator op;

arith_expression:
					arith_expression arith_operator arith_expression
					| LPAREN_TOK arith_expression RPAREN_TOK
					|op ;

arith_operator:
				PLUS_TOK
				|MINUS_TOK
				|DIV_TOK
				|MULT_TOK
				|MODULO_TOK
				|POWER_TOK
				|LSHIFT_TOK
				|RSHIFT_TOK
				|BITOR_TOK
				|BITAND_TOK;


call_fn:
			ID_TOK LPAREN_TOK call_args RPAREN_TOK;

call_args:
			op
			| op COMMA_TOK call_args
			| 
			;



%%

int main()
{
   if (yyparse()==0) printf("\n\nParsed Successfully\n");
   else printf("\n\nParsing Error at Line No %d\n", yylineno);

   return(0);	

}

void yyerror(char *s)
{
	printf("yyerror: %s\n",s);
}
