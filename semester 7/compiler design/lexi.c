#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

FILE *yyin;
char *yytext;

/* Single character lexemes */
// #define LPAREN_TOK '('
// #define RPAREN_TOK ')'
// #define LCURLY '{'
// #define RCURLY '}'
// #define COMMA_TOK ','
// #define COMPLEMENT_TOK '~'
// #define GT_TOK '>'
// #define LT_TOK '<'
// #define ASSIGN_TOK '='
// #define MINUS_TOK '-'
// #define PLUS_TOK '+'
// #define  SEMICOLON_TOK ';'
// #define NOT_TOK '!'
// #define XOR_TOK '^'


/*....................
.......................*/
/* Reserved words */

#define	 WHILE_TOK  256
#define	 DO_TOK  257
#define	 IF_TOK 258
#define	 ELSE_TOK  259
#define	 SWITCH_TOK  260
#define	 FOR_TOK  261
#define	 CONST_TOK  262
#define	 DOUBLE_TOK 263
#define	 INT_TOK 264
#define	 FLOAT_TOK 265
#define	 VOID_TOK  266
#define	 MAIN_TOK  267
#define	 CHAR_TOK  268
#define	 RETURN_TOK 269


//OPERATORS
#define INC_TOK 288
#define DEC_TOK 289
#define EQUAL_TOK 290
#define NOTEQUAL_TOK 291
#define GTEQ_TOK 292
#define LTEQ_TOK 293
#define AND_TOK 294
#define OR_TOK 295
#define LSHIFT_TOK 296
#define RSHIFT_TOK 297
#define PLUSEQ_TOK 298
#define MINUSEQ_TOK 299
#define MULTEQ_TOK 300
#define DIVEQ_TOK 301
#define MODEQ_TOK 302
#define XOREQ_TOK 303
#define ANDEQ_TOK 304
#define OREQ_TOK 305
#define POWER_TOK 306

/* Identifier, constants..*/
#define ID_TOK 307
#define INTCONST 308

char strings[][10] = {"while", "do", "if", "else", "switch", "for", "const", "double", "int", "float", "void", "main", "char", "return"};
/*
static inline char *stringFromenum(enum keywords k)
{
    static const char *strings[] = {"while", "do", "if", "else", "switch", "for", "const", "double", "int", "float", "void", "main", "char", "return"};

    return *strings[k];
}
*/
void yylex()
{
	char ch, ch2, prevch;
	char buf[100];
	int flag, pos = 0;
	memset(buf, '\0', 100);
	while(1)
	{
		flag = 0;
		ch = getc(yyin);
		// printf("ch = %c", ch);
		while (isspace(ch))
		{
			prevch = ch;
			ch = getc(yyin); // discard any white space
			// if(!(isspace(ch)))
			// 	fseek(yyin, -1, SEEK_CUR);
			flag = 1;
		}
		if(flag==1)
		{
			fseek(yyin, -1, SEEK_CUR);
			ch = ' ';
		}
		if(((ch=='_')||(isalpha(ch)||isdigit(ch)))&&(flag==0))	//also put condition on '.' in case of floats
			buf[pos++] = ch;
		else
		{
			if(pos>=1)
				fseek(yyin, -1, SEEK_CUR);
			break;
		}	
	}
	
	if(pos==0)
	{
		// printf("single = %c  ",ch);
		switch(ch)
		{
			case ';':	printf("SEMICOLON_TOK : %d", ch);
					 	return;
			case '#':	printf("HASH_TOK : %d", ch);
					 	return;
			case '"':	printf("DQUOTE_TOK : %d", ch);
					 	return;		 	
			case ',':	printf("COMMA_TOK : %d", ch);
					 	return;
			case '.':	printf("DOT_TOK : %d", ch);
					 	return;
			case '=':	ch2 = getc(yyin);
						if(ch2=='=')
						{
							printf("EQUAL_TOK : %d", EQUAL_TOK);
					 		return;
						}
						else
						{
							printf("ASSIGN_TOK : %d", ch);
							fseek(yyin, -1, SEEK_CUR);
					 		return;
						}
						
			case '~':	printf("COMPLEMENT_TOK : %d", ch);
					 	return; 
			case '(':	printf("LPAREN_TOK : %d", ch);
					 	return; 
			case ')':	printf("RPAREN_TOK : %d", ch);
					 	return; 
			case '{':	printf("LCURLY_TOK : %d", ch);
					 	return; 
			case '}':	printf("RCURLY_TOK : %d", ch);
					 	return; 
			case '<':	ch2 = getc(yyin);
						if(ch2=='=')
						{
							printf("LTEQ_TOK : %d", LTEQ_TOK);
					 		return;
						}
						else if(ch2=='<')
						{
							printf("LSHIFT_TOK : %d", LSHIFT_TOK);
					 		return;	
						}
						else 
						{
							printf("LT_TOK : %d", ch);
							fseek(yyin, -1, SEEK_CUR);
					 		return;
						}

			case '>':	ch2 = getc(yyin);
						if(ch2=='=')
						{
							printf("GTEQ_TOK : %d", GTEQ_TOK);
					 		return;
						}
						else if(ch2=='>')
						{
							printf("RSHIFT_TOK : %d", RSHIFT_TOK);
					 		return;	
						}
						else 
						{
							printf("GT_TOK : %d", ch);
							fseek(yyin, -1, SEEK_CUR);
					 		return;
						}
			case '[':	printf("SQLBKT_TOK : %d", ch);
					 	return;  
			case ']':	printf("SQRBKT_TOK : %d", ch);
					 	return;  
			case '+':	ch2 = getc(yyin);
						if(ch2=='=')
						{
							printf("PLUSEQ_TOK : %d", PLUSEQ_TOK);
					 		return;
						}
						else if(ch2=='+')
						{
							printf("INC_TOK : %d", INC_TOK);
							return;
						}
						else
						{
							printf("ADD_TOK : %d", ch);
							fseek(yyin, -1, SEEK_CUR);
					 		return;
						}
			case '-':	ch2 = getc(yyin);
						if(ch2=='=')
						{
							printf("MINUSEQ_TOK : %d", MINUSEQ_TOK);
					 		return;
						}
						else if(ch2=='-')
						{
							printf("DEC_TOK : %d", DEC_TOK);
							return;
						}
						else
						{
							printf("SUBT_TOK : %d", ch);
							fseek(yyin, -1, SEEK_CUR);
					 		return;
						} 
			case '*':	ch2 = getc(yyin);
						if(ch2=='=')
						{
							printf("MULTEQ_TOK : %d", MULTEQ_TOK);
					 		return;
						}
						else if(ch2=='*')
						{
							printf("POWER_TOK : %d", POWER_TOK);
							return;
						}
						else
						{
							printf("MULT_TOK : %d", ch);
							fseek(yyin, -1, SEEK_CUR);
					 		return;
						}
			case '/':	ch2 = getc(yyin);
						if(ch2=='=')
						{
							printf("DIVEQ_TOK : %d", DIVEQ_TOK);
					 		return;
						}
						else
						{
							printf("DIV_TOK : %d", ch);
							fseek(yyin, -1, SEEK_CUR);
					 		return;
						}
			case '&':	ch2 = getc(yyin);
						if(ch2=='&')
						{
							printf("AND_TOK : %d", AND_TOK);
					 		return;
						}
						else if(ch2=='=')
						{
							printf("ANDEQ_TOK : %d", ANDEQ_TOK);
					 		return;
						}
						else
						{
							printf("BITAND_TOK : %d", ch);
							fseek(yyin, -1, SEEK_CUR);
					 		return;
						}
			case '|':	ch2 = getc(yyin);
						if(ch2=='|')
						{
							printf("OR_TOK : %d", OR_TOK);
					 		return;
						}
						else if(ch2=='=')
						{
							printf("OREQ_TOK : %d", OREQ_TOK);
					 		return;
						}
						else
						{
							printf("BITOR_TOK : %d", ch);
							fseek(yyin, -1, SEEK_CUR);
					 		return;
						}
			case '^':	ch2 = getc(yyin);
						if(ch2=='=')
						{
							printf("XOREQ_TOK : %d", XOREQ_TOK);
							return;
						}
						else
						{
							printf("BITXOR_TOK : %d", ch);
					 		fseek(yyin, -1, SEEK_CUR);
							return;	
						}
			case '%':	ch2 = getc(yyin);
						if(ch2=='=')
						{
							printf("MODEQ_TOK : %d", MODEQ_TOK);
					 		return;
						}
						else
						{
							printf("MOD_TOK : %d", ch);
							fseek(yyin, -1, SEEK_CUR);
					 		return;
						}
			case '!':	ch2 = getc(yyin);
						if(ch2=='=')
						{
							printf("NOTEQUAL_TOK : %d", NOTEQUAL_TOK);
					 		return;
						}
						else
						{
							printf("NOT_TOK : %d", ch);
							fseek(yyin, -1, SEEK_CUR);
					 		return;
						}
			
//						yytext[0] = ch;
//						yyleng = 1;
//						return ch; // ASCII value is used as token value

		}
		
	}
	
	else if(pos==1)
	{
		// printf("alphanum = %c ", buf[0]);
		if(isdigit(buf[0]))
		{
			printf("INTCONST : %d", INTCONST);
			return;
		}
		if(isalpha(buf[0])||(buf[0]=='_'))
		{
			printf("ID_TOK : %d", ID_TOK);
			return;
		}
	}
	else
	{
		int i, j;
		char buf2[100], kw[100];
		// for(i=0;buf[i]!='\0';i++)
		// 	printf("word%c", buf[i]);
		// printf(" ");
		for(i = 0; i<=13; i++)
		{
			memset(buf2, '\0', 100);
			strcpy(buf2, strings[i]);
			if(strcmp(buf, buf2)==0)	
			{
				for(j=0;buf[j]!='\0';j++)
					buf2[j] = toupper(buf2[j]);
				strcpy(kw, buf2);
				strcat(kw, "_TOK");
				printf("%s : %d", kw, i+256);
				return;
			}
		}
		
		for(i=0;buf[i]!='\0';i++)
		{
			if(isalpha(buf[i])||(buf[i]=='_'))
			{
				printf("ID_TOK : %d", ID_TOK);
				return;
			}
		}
		printf("INTCONST : %d", INTCONST);
		return;
	}
	
}


int main(int argc, char *argv[])
{
	
	int token;
	if (argc != 2)
	{
		return -1;
	}
	else
	{
		yyin = fopen(argv[1], "r");
		while(!feof(yyin))
		{
			//token = yylex();
			//printf("%d", token);
			yylex();
			printf("\n");
		}
	fclose(yyin);
	}
}

