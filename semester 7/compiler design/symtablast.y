%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#define DEBUG_INFO 1
	#define MAX_FUNCTIONS 10
	extern FILE *yyin;
	extern int yylineno;
	void yyerror(char *s);
	int yylex();
	#include"lex.yy.c"
	int gscope = 0;
	int function_number = 0;
	int var_buffer[100];
	int var_buffer_index = 0;
	
	struct table_entry{
		int entry_index;
		char var_name;
		int type[10];
		int scope[10];
		int line_no[10];
		int scope_array_index;
		int global_flag;
	}symbol_table[MAX_FUNCTIONS][122],temp_table[122]; 


	void insert_symbol(char *name);
	int found(char *name);
	void display_table(int table_index);
	int check_for_same_scope(struct table_entry node1,struct table_entry node2);
	void check_scope_declaration(char *name,int scope);
	int check_type(char *name1,char *name2);
	int is_number(const char *s);
	void init_symbol_table(void);
	void assign_stmt_type_check(char *name,int type,int scope);
	void assign_type(int t,int flag);
	void initialize_symb_table();
%}



%token WHILE_TOK DO_TOK IF_TOK ELSE_TOK SWITCH_TOK FOR_TOK  CONST_TOK DOUBLE_TOK INT_TOK FLOAT_TOK VOID_TOK  
%token CHAR_TOK  RETURN_TOK CASE_TOK DEFAULT_TOK BREAK_TOK

%token INC_TOK DEC_TOK EQUAL_TOK NOTEQUAL_TOK GTEQ_TOK LTEQ_TOK AND_TOK OR_TOK LSHIFT_TOK RSHIFT_TOK
%token PLUSEQ_TOK MINUSEQ_TOK MULTEQ_TOK DIVEQ_TOK MODEQ_TOK 

%token ID_TOK INTCONST FLOATCONST STRING_LITERAL

%token LPAREN_TOK RPAREN_TOK LCURLY_TOK RCURLY_TOK SQLBKT_TOK SQRBKT_TOK COMMA_TOK GT_TOK LT_TOK ASSIGN_TOK MINUS_TOK PLUS_TOK POWER_TOK
%token SEMICOLON_TOK NOT_TOK XOR_TOK HASH_TOK DOT_TOK DIV_TOK MULT_TOK MODULO_TOK BITAND_TOK BITOR_TOK COLON_TOK 

%union{

	struct s1{
    	int i_type;
    	char *i_val;
    }p;

	struct s2{
		char *name;
		int i_type;
		char *i_val;
	}n;

    struct s3{
    	int i_type;
    }t;
};

%type <p> arith_expression logic_expression unary_expression logi_operator AND_TOK OR_TOK NOT_TOK XOR_TOK
%type <t> datatype
%type <n> data INTCONST FLOATCONST STRING_LITERAL ID_TOK op 


%start S
%%

S:  datatype ID_TOK SQLBKT_TOK INTCONST SQRBKT_TOK SEMICOLON_TOK S 				// int a[5];
	|declaration SEMICOLON_TOK S 								// int a=3, b=9;
	|datatype  ID_TOK LPAREN_TOK RPAREN_TOK
		{
		function_number++;
		if(DEBUG_INFO)
			printf("\nFn. no. %d : Main Function found; line no: %d\n",function_number,yylineno);
		} block S
	|datatype ID_TOK LPAREN_TOK function_args RPAREN_TOK 
		{
		function_number++;
		if(DEBUG_INFO)
			printf("\nFn. no. %d : User-defined Function found; line no: %d\n",function_number,yylineno);
		}
	block S	// int func(...){ ... }
	|
	;

block:
		LCURLY_TOK 
					{ gscope += 1; 
					  printf("\n Scope increased by 1 - new scope= %d",gscope);
					}
		STATEMENTS  blocks 
		 			{ gscope -= 1; 
		 			  printf("\n Scope decreased by 1 - new scope= %d",gscope);
		 			} 
		RCURLY_TOK;

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
		| SWITCH_TOK LPAREN_TOK  op RPAREN_TOK 
		  LCURLY_TOK 
			{ gscope += 1; 
			  printf("\n Scope increased by 1 - new scope= %d",gscope);
			} 
		  cases 
			{
				check_scope_declaration($3.name,gscope);
				{ gscope -= 1; 
				  printf("\n Scope decreased by 1 - new scope= %d",gscope);
				}
			} 
		   RCURLY_TOK															// switch(c){ case ... }

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
			INT_TOK			{$$.i_type=1;}
			| FLOAT_TOK		{$$.i_type=2;}
			| DOUBLE_TOK	{$$.i_type=3;}
			| CHAR_TOK		{$$.i_type=4;} ;

declaration:
			datatype id_token {printf("hiii");}	
			{
				assign_type($1.i_type,1);									// char a, b, c
			}											
			| datatype assign_stmt;											// int a=2, b=3

assign_stmt:
			assign_stmt COMMA_TOK ID_TOK ASSIGN_TOK op						// a=3, b=5
			| ID_TOK assign_ops arith_expression 
					{
						printf("\nvar: %s",$1.name);
						check_scope_declaration($1.name,gscope);
						assign_stmt_type_check($1.name,$3.i_type,gscope);
					}														// a = 2+b 
			| ID_TOK assign_ops logic_expression 	
					{
						check_scope_declaration($1.name,gscope);
						assign_stmt_type_check($1.name,$3.i_type,gscope);
					}														// a = b||b
			| ID_TOK assign_ops unary_expression 
					{
						check_scope_declaration($1.name,gscope);
						assign_stmt_type_check($1.name,$3.i_type,gscope);
					}														// a = k++
			| ID_TOK assign_ops op  
					{
						check_scope_declaration($1.name,gscope);
						check_scope_declaration($3.name,gscope);			//working fine till here
						check_type($1.name,$3.name);
					}														// j = 5.3 or j = k
			| ID_TOK assign_ops call_fn ;									// sum = calsum(3,4)
assign_ops:
			ASSIGN_TOK
			| PLUSEQ_TOK 
			| MINUSEQ_TOK 
			| DIVEQ_TOK 
			| MULTEQ_TOK 
			| MODEQ_TOK ;

id_token: id_token COMMA_TOK ID_TOK     
	      {
	      	printf("\nvar: %s",$3.name);
	      	insert_symbol($3.name);
	      	var_buffer[var_buffer_index++] = $3.name[0];		//store the new variable name encountered
	      }
        | ID_TOK                             
          {
          	printf("\nvar: %s",$1.name);
	      	insert_symbol($1.name);
	      	var_buffer[var_buffer_index++] = $1.name[0];
	      }
        ;

data:
		INTCONST
		| FLOATCONST
		|STRING_LITERAL;

relational_expression:
						op GT_TOK op			{check_scope_declaration($1.name,gscope);} 
						| op LT_TOK op			{check_scope_declaration($1.name,gscope);} 
						| op EQUAL_TOK op		{check_scope_declaration($1.name,gscope);} 
						| op NOTEQUAL_TOK op	{check_scope_declaration($1.name,gscope);} 
						| op GTEQ_TOK op		{check_scope_declaration($1.name,gscope);} 
						| op LTEQ_TOK op		{check_scope_declaration($1.name,gscope);} 
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
				ID_TOK INC_TOK 			{check_scope_declaration($1.name,gscope);} 					// a++
				| ID_TOK DEC_TOK 		{check_scope_declaration($1.name,gscope);} 					// a--
				| INC_TOK ID_TOK 		{check_scope_declaration($2.name,gscope);} 					// ++a
				| DEC_TOK ID_TOK 		{check_scope_declaration($2.name,gscope);} 					// --a
				;

logic_expression:
					op logi_operator op
						{
							check_scope_declaration($1.name,gscope);
							check_scope_declaration($3.name,gscope);
							$$.i_type = check_type($1.name,$3.name);
						}
					|logi_operator op;

arith_expression:
					op arith_operator op
						{

							check_scope_declaration($1.name,gscope);
							check_scope_declaration($3.name,gscope);
							$$.i_type = check_type($1.name,$3.name);
						}								
					| LPAREN_TOK arith_expression RPAREN_TOK {}
					;

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
   initialize_symb_table();
   if (yyparse()==0) 
   {
   		for(int i=1;i <= function_number;i++)
   		{
   			display_table(i);
   		}
   		printf("\n\nParsed Successfully\n");
   	}

   else printf("\n\nParsing Error at Line No %d\n", yylineno);

   return(0);	

}

void initialize_symb_table()
{
	for(int table_index = 0;table_index <= MAX_FUNCTIONS;table_index++)
	{
		for(int i=0;i <= 122;i++){
			symbol_table[table_index][i].entry_index = -1;
		}
	}
	if(DEBUG_INFO){
		printf("Symbol table initialised with -1 (empty now)\n");
		printf("Each node size of Symbol table is: %ld\n",sizeof(symbol_table[function_number][0]));
	}
}

void yyerror(char *s)
{
	printf("yyerror: %s\n",s);
}


int is_number(const char *s)
{
	int point = 1;
	int f = 0;
    while (*s) 
    {
        if ((isdigit(*s)==0)&&((*s)!='.'))
        	return 0; 
        if(((*s)=='.')&&(point==1))
        	{
        		f = 1;
        		point=0;
        	}
        s++;
        if(((*s)=='.')&&(point==0))
        	return 0;
    }
    if(f==0)
    	return 1; 			//indicates int
    else
    	return 2;			// indicates float
}


void check_scope_declaration(char *name,int scope)		//checking variable scope 
{
	if(DEBUG_INFO)
		printf("\nCurrent scope inside check_scope_declaration() for %s is:  %d in line no: %d\n",name,gscope,yylineno);
			
	if(found(name))										/*if variable is already in symbol table,
														  its scope can be obtained */
	{
		if (is_number(name) || symbol_table[function_number][name[0]].type[scope] != 0)
			return;										// if variable is present in current scope
		
		else
		{									// if variable is present in any of the scopes until present scope
			for(int i = 0; i < scope ; i++)
			{
				if(symbol_table[function_number][name[0]].type[i] != 0)
					return;
				
			}
			yyerror("Un-declared till now");
		}
		yyerror("Un-declared till now");
	}
	yyerror("Un-declared till now");
}


/* search for the variable name in the current symbol table. The variable is present in the table if either:
	1. the array pos. with the ascii value of first char of var_name as index is not empty
	2. if it is a var_name, length >1
	3. it is a number
*/ 
int found(char *name)									
{
	return symbol_table[function_number][name[0]].entry_index != -1  || strlen(name) > 1 || is_number(name);
}


void assign_stmt_type_check(char *name,int type,int scope)
{
	if(DEBUG_INFO)
		printf("\nCurrent scope inside assign_stmt_type_check() is: %d in lineno: %d\n",gscope,yylineno);
	
	/* for the var_name in this function, scope_arr_index defines the number of var_names chained to that
	   same location */
	for(int i = 0;i < symbol_table[function_number][name[0]].scope_array_index;i++)
	{
		if(symbol_table[function_number][name[0]].type[symbol_table[function_number][name[0]].scope[i]] == type)
			return;
		
	}
	yyerror("LHS-RHS type mismatch in assignment statement");
}


int  check_type(char *name1,char *name2){
	if(DEBUG_INFO){
		printf("\nCurrent scope inside check_type() for %s, %s is: %d in line_no: %d\n",name1,name2,gscope,yylineno);
	}
	if (strlen(name1) == 1 && strlen(name2) == 1 && !is_number(name2))		//e.g - j=k
	{
		for(int i = 0; i < symbol_table[function_number][name1[0]].scope_array_index;i++)
		{
			for(int j = 0; j < symbol_table[function_number][name2[0]].scope_array_index;j++)
			{
				// COMPARING THE TYPES
				if (symbol_table[function_number][name1[0]].type[symbol_table[function_number][name1[0]].scope[i]] == symbol_table[function_number][name2[0]].type[symbol_table[function_number][name2[0]].scope[j]] && symbol_table[function_number][name1[0]].type[symbol_table[function_number][name1[0]].scope[i]] != 0 )
					return symbol_table[function_number][name1[0]].type[symbol_table[function_number][(int)name1[0]].scope[i]];
			}
		}
		printf("%s === %s\n",name1,name2);
		yyerror("Mismatched Type");
	}
	else if(strlen(name1) == 1)
	{
		if (is_number(name2))				// e.g - j=4 or t = 0.9
		{
			for(int i = 0;i < symbol_table[function_number][name1[0]].scope_array_index;i++)
			{
				if((symbol_table[function_number][name1[0]].type[symbol_table[function_number][name1[0]].scope[i]] == 1) || (symbol_table[function_number][name1[0]].type[symbol_table[function_number][name1[0]].scope[i]] == 2))
					return 1;
				
			}
			yyerror("Integer or Float type not found");
		}
		yyerror("String is not allowed");
	}
	else if(strlen(name2) == 1)
	{
		if(is_number(name1))
		{
			for(int i = 0;i < symbol_table[function_number][name2[0]].scope_array_index;i++)
			{
				if((symbol_table[function_number][name2[0]].type[symbol_table[function_number][name2[0]].scope[i]] == 1) || (symbol_table[function_number][name2[0]].type[symbol_table[function_number][name2[0]].scope[i]] == 1))
					return 1;
				
			}
			yyerror("Integer or Float type not found");
		}
		yyerror("String is not allowed");
	}
	else{
		if(((is_number(name1)==1) && (is_number(name2))==1)|| ((is_number(name1)==2) && (is_number(name2))==2))
		{
			return 1;
		}
		yyerror("Un recognised type of two variables");
	}
}


void insert_symbol(char *name)
{

	printf("\nvar: %s",name);
	int index = myhash(name);
	temp_table[index].entry_index = index;
	temp_table[index].var_name = name[0];
	memset((void*)temp_table[index].type,-1,sizeof(int)*10);
	temp_table[index].scope[0] = gscope;
	temp_table[index].line_no[0] = yylineno;
	temp_table[index].scope_array_index = 0;
}



void assign_type(int t,int flag)
{
	if(DEBUG_INFO){
		printf("\nCurrent scope inside assign_type() is: %d in line_no: %d\n",gscope,yylineno);
	}
	struct table_entry node;
	for(int i = 0;i < var_buffer_index;i++)			// for all variables declared in a line
	{
		if(var_buffer[i] >= 0)
		{
			node = symbol_table[function_number][var_buffer[i]];
			if(node.var_name == temp_table[var_buffer[i]].var_name)
			{
				if(check_for_same_scope(node,temp_table[var_buffer[i]]))
				{
					yyerror("Variable having same name with same scope");
				}
				else
				{
					int element = var_buffer[i];
					symbol_table[function_number][element].entry_index = element;
					symbol_table[function_number][element].var_name = temp_table[element].var_name;
					symbol_table[function_number][element].scope[symbol_table[function_number][element].scope_array_index] = gscope;
					symbol_table[function_number][element].type[gscope] = t;
					symbol_table[function_number][element].line_no[gscope] = yylineno;
					symbol_table[function_number][element].scope_array_index++;
					if(flag == 0 && symbol_table[function_number][element].global_flag != 1)
					{
						symbol_table[function_number][element].global_flag = 0;
					}
					else
					{
						symbol_table[function_number][element].global_flag = 1;
					}
				}
			}
			else
			{
					int element = var_buffer[i];
					symbol_table[function_number][element].entry_index = element;
					symbol_table[function_number][element].var_name = temp_table[element].var_name;
					symbol_table[function_number][element].scope[symbol_table[function_number][element].scope_array_index] = gscope;
					symbol_table[function_number][element].type[gscope] = t;
					symbol_table[function_number][element].line_no[gscope] = yylineno;
					symbol_table[function_number][element].scope_array_index++;
					if(flag == 0 && symbol_table[function_number][element].global_flag != 1)
					{
						symbol_table[function_number][element].global_flag = 0;
					}
					else
					{
						symbol_table[function_number][element].global_flag = 1;
					}
			}
		}
		var_buffer[i] = -1;
	}
}

int check_for_same_scope(struct table_entry node1,struct table_entry node2){
	if(DEBUG_INFO){
		printf("\nCurrent scope inside check_for_same_scope() is:  %d in line_no: %d\n",gscope,yylineno);
	}
	if (node1.entry_index == -1){
		return 0;
	}
	else{
		int target_scope = node2.scope[0];
		for(int i = 0;i < node1.scope_array_index;i++){
			if(node1.scope[i] == target_scope){
				return 1;
			}
		}
		return 0;
	}
}


void display_table(int table_index){
	char *decision = NULL;
	printf("\t\t\t%d %s\n\n",table_index,"CURRENT SYMBOL TABLE ");
	printf("----------------------------------------------------------------------------------------------------\n");
	for(int i=0;i <= 122;i++){
		if(symbol_table[table_index][i].entry_index != -1){
			for(int j=0;j < symbol_table[table_index][i].scope_array_index;j++){
				switch(symbol_table[table_index][i].type[symbol_table[table_index][i].scope[j]]){
					case 0:
						decision = (char*)malloc(sizeof(char) * 12);
						strncpy(decision,(char*)"Invalidated",11);
						break;
					case 1:
						decision = (char*)malloc(sizeof(char) * 4);
						strncpy(decision,(char*)"Int",3);
						break;
					case 2:
						decision = (char*)malloc(sizeof(char) * 5);
						strncpy(decision,(char*)"Float",4);
						break;
					case 3:
						decision = (char*)malloc(sizeof(char) * 6);
						strncpy(decision,(char*)"Double",5);
						break;
					case 4:
						decision = (char*)malloc(sizeof(char) * 5);
						strncpy(decision,(char*)"Char",4);
						break;

				}
				printf("| index: %d name: %c total_of_scope_used: %d type = %s in the scope %d line_no: %d \t   |\n",symbol_table[table_index][i].entry_index,symbol_table[table_index][i].var_name,symbol_table[table_index][i].scope_array_index,decision,symbol_table[table_index][i].scope[j],symbol_table[table_index][i].line_no[symbol_table[table_index][i].scope[j]]);
				free(decision);
			}
			printf("----------------------------------------------------------------------------------------------------\n");
		}
	}
}


int myhash(char * name)
{
	int i, ascii_val = 0;
	for(i=0;i<strlen(name);i++)
	{
		ascii_val += name[i];
	}
	return ascii_val
}