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
int relational[] = {2, 3, 5, 7, 8, 10, 11, 12};
int logical[] = {14,15,17,18};
int arithmetic[] = {31, 32, 34, 35, 37, 38, 39, 40};
int idkey = 52;
int expnum = 66;
int floatnum = 67;
int intnum = 68;
int delim = 82;

#define initstate 0

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
#define FLOATCONST 309
#define EXPCONST 310

char strings[][10] = {"while", "do", "if", "else", "switch", "for", "const", "double", "int", "float", "void", "char", "return"};
/*
static inline char *stringFromenum(enum keywords k)
{
    static const char *strings[] = {"while", "do", "if", "else", "switch", "for", "const", "double", "int", "float", "void", "main", "char", "return"};

    return *strings[k];
}
*/

void printbuf(char buf[])
{
	int i;
	printf("\n");
	for(i=0;buf[i]!='\0';i++)
		printf("%c", buf[i]);
	printf("\t");
}

int key_or_not(char buf[])
{
	int i, j;
	char buf2[100], kw[100];
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
			printf("%s", kw);
			return (i+256);
		}
	}

	return -1;
}



int yylex()
{
	char c;
	char buf[100];
	int state, pos = 0;
	memset(buf, '\0', 100);
	state = initstate;
	while(1)
	{
		switch(state)
		{
			case 0: c = getc(yyin);
					if (c==' ' || c=='\t' || c=='\n')
					{
						printf("%c", c);
						return -1;
					}
					buf[pos++] = c;
					if (c=='<') state = 1;
					else if (c=='=') state = 4;
					else if (c=='>') state = 6;
					else if (c=='!') state = 9;
					else if (c=='&') state = 13;
					else if (c=='|') state = 16;
					else if (c=='+') state = 30;
					else if (c=='-') state = 33;
					else if (c=='*') state = 36;
					else if (c=='/') state = 39;
					else if (c=='%') state = 40;
					else if (isalpha(c)||(c=='_')) state = 51;
					else if (isdigit(c)) state = 60;
					else if (c=='{') state = 69;
					else if (c=='}') state = 70;
					else if (c=='[') state = 71;
					else if (c==']') state = 72;
					else if (c=='(') state = 73;
					else if (c==',') state = 74;
					else if (c==';') state = 75;
					else if (c=='#') state = 76;
					else if (c=='"') state = 77;
					else if (c=='.') state = 78;
					else if (c==')') state = 79;

					break;
			
		
			case 1:	c = getc(yyin);
					buf[pos++] = c;
					if(c=='=') state = 2;
					else 
					{
						state = 3;
						fseek(yyin, -1, SEEK_CUR);
					}
					break;

			case 2: buf[pos-1] = '\0';
					printbuf(buf);
					printf("LTEQ_TOK");
					return LTEQ_TOK;

			case 3: buf[pos-1] = '\0';
					printbuf(buf);
					printf("LT_TOK");
					return buf[0];

			case 4: c = getc(yyin);
					buf[pos++] = c;
					if(c=='=') state = 5;
					else 
					{
						state = 12;
						fseek(yyin, -1, SEEK_CUR);
					}
					break;

			case 5: buf[pos-1] = '\0';
					printbuf(buf);
					printf("EQUAL_TOK");
					return EQUAL_TOK;

					break;

			case 6: c = getc(yyin);
					buf[pos++] = c;
					if(c=='=') state = 7;
					else 
					{
						state = 8;
						fseek(yyin, -1, SEEK_CUR);
					}
					break;

			case 7: printbuf(buf);
					printf("GTEQ_TOK");
					return GTEQ_TOK;

					break;

			case 8: printbuf(buf);
					printf("GT_TOK");
					return buf[0];

					break;

			case 9: c = getc(yyin);
					buf[pos++] = c;
					if(c=='=') state = 10;
					else 
					{
						state = 11;
						fseek(yyin, -1, SEEK_CUR);
					}
					break;

			case 10:buf[pos-1] = '\0';
					printbuf(buf);
					printf("NOTEQUAL_TOK");
					return NOTEQUAL_TOK;

			case 11:printbuf(buf);
					printf("NOT_TOK");
					return buf[0];

			case 12:printbuf(buf);
					printf("ASSIGN_TOK");
					return buf[0];

			case 13:c = getc(yyin);
					buf[pos++] = c;
					if(c=='&') state = 14;
					else 
					{
						state = 15;
						fseek(yyin, -1, SEEK_CUR);
					}
					break;

			case 14:buf[pos-1] = '\0';
					printbuf(buf);
					printf("AND_TOK");
					return AND_TOK;

			case 15:printbuf(buf);
					printf("BITAND_TOK");
					return buf[0];

			case 16:c = getc(yyin);
					buf[pos++] = c;
					if(c=='|') state = 17;
					else
					{
						state = 18;
						fseek(yyin, -1, SEEK_CUR);
					}
					break;

			case 17:buf[pos-1] = '\0';
					printbuf(buf);
					printf("OR_TOK");
					return OR_TOK;

			case 18:printbuf(buf);
					printf("BITOR_TOK");
					return buf[0];

			case 30:c = getc(yyin);
					buf[pos++] = c;
					if(c=='+') state = 31;
					else 
					{
						state = 32;
						fseek(yyin, -1, SEEK_CUR);
					}
					break;

			case 31:buf[pos-1] = '\0';
					printbuf(buf);
					printf("INC_TOK");
					return INC_TOK;

			case 32:printbuf(buf);
					printf("PLUS_TOK");
					return buf[0];

			case 33:c = getc(yyin);
					buf[pos++] = c;
					if(c=='-') state = 34;
					else 
					{
						state = 35;
						fseek(yyin, -1, SEEK_CUR);
					}
					break;

			case 34:buf[pos-1] = '\0';
					printbuf(buf);
					printf("DEC_TOK");
					return DEC_TOK;

			case 35:printbuf(buf);
					printf("MINUS_TOK");
					return buf[0];

			case 36:c = getc(yyin);
					buf[pos++] = c;
					if(c=='*') state = 37;
					else 
					{
						state = 38;
						fseek(yyin, -1, SEEK_CUR);
					}
					break;

			case 37:buf[pos-1] = '\0';
					printbuf(buf);
					printf("POWER_TOK");
					return POWER_TOK;

			case 38:buf[pos-1] = '\0';
					printbuf(buf);
					printf("MULT_TOK");
					return buf[0];

			case 39:printbuf(buf);
					printf("DIV_TOK");
					return buf[0];

			case 40:printbuf(buf);
					printf("MODULO_TOK");
					return buf[0];

			case 51:c = getc(yyin);
					buf[pos++] = c;
					if(isalnum(c)||(c=='_')) state = 51;
					else 
					{
						state = 52;
						fseek(yyin, -1, SEEK_CUR);
					}
					break;

			case 52:buf[pos-1] = '\0';
					printbuf(buf);
					int tok = key_or_not(buf);
					if(tok==-1)
					{
						printf("ID_TOK");
						return ID_TOK;
					}
					return tok;

			case 60:c = getc(yyin);
					buf[pos++] = c;
					if(isdigit(c)) state = 60;
					else if(c=='.')state = 61;
					else if(c=='E')state = 63;
					else 
					{
						state = 68;
						fseek(yyin, -1, SEEK_CUR);
					}
					break;

			case 61:c = getc(yyin);
					buf[pos++] = c;
					if(isdigit(c)) state = 62;
					else
					{
						buf[pos-1] = '\0';
						printbuf(buf);
						printf("ID_TOK");
						fseek(yyin, -1, SEEK_CUR);
						return ID_TOK;
					}

					break;

			case 62:c = getc(yyin);
					buf[pos++] = c;
					if(isdigit(c)) state = 62;
					else if(c=='E')state = 63;
					else 
					{
						state = 67;
						fseek(yyin, -1, SEEK_CUR);
					}
					break;

			case 63:c = getc(yyin);
					buf[pos++] = c;
					if(isdigit(c)) state = 65;
					else if((c=='+')||(c=='-')) state = 64;
					else
					{
						buf[pos-1] = '\0';
						printbuf(buf);
						printf("ID_TOK");
						fseek(yyin, -1, SEEK_CUR);
						return ID_TOK;
					}

					break;
					
			case 64:c = getc(yyin);
					buf[pos++] = c;
					if(isdigit(c)) state = 65;
					else
					{
						buf[pos-1] = '\0';
						printbuf(buf);
						printf("ID_TOK");
						fseek(yyin, -1, SEEK_CUR);
						return ID_TOK;
					}

					break;

			case 65:c = getc(yyin);
					buf[pos++] = c;
					if(isdigit(c)) state = 65;
					else 
					{
						state = 66;
						fseek(yyin, -1, SEEK_CUR);
					}
			case 66:buf[pos-1] = '\0';
					printbuf(buf);
					printf("EXPCONST");
					return EXPCONST;

			case 67:buf[pos-1] = '\0';
					printbuf(buf);
					printf("FLOATCONST");
					return FLOATCONST;

			case 68:buf[pos-1] = '\0';
					printbuf(buf);
					printf("INTCONST");
					return INTCONST;
			
			case 69:printbuf(buf);
					printf("LCURLY_TOK");
					return buf[0];

			case 70:printbuf(buf);
					printf("RCURLY_TOK");
					return buf[0];

			case 71:printbuf(buf);
					printf("SQLBKT_TOK");
					return buf[0];

			case 72:printbuf(buf);
					printf("SQRBKT_TOK");
					return buf[0];

			case 73:printbuf(buf);
					printf("LPAREN_TOK");
					return buf[0];

			case 74:printbuf(buf);
					printf("COMMA_TOK");
					return buf[0];

			case 75:printbuf(buf);
					printf("SEMICOLON_TOK");
					return buf[0];

			case 76:printbuf(buf);
					printf("HASH_TOK");
					return buf[0];

			case 77:printbuf(buf);
					printf("DQUOTE_TOK");
					return buf[0];

			case 78:printbuf(buf);
					printf("DOT_TOK");
					return buf[0];

			case 79:printbuf(buf);
					printf("RPAREN_TOK");
					return buf[0];

			default:printbuf(buf);
					printf("UNKNOWN_TOK");
					return 320;
		}
	}
}
	
int main(int argc, char *argv[])
{
	
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

