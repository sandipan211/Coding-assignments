/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    WHILE_TOK = 258,
    DO_TOK = 259,
    IF_TOK = 260,
    ELSE_TOK = 261,
    SWITCH_TOK = 262,
    FOR_TOK = 263,
    CONST_TOK = 264,
    DOUBLE_TOK = 265,
    INT_TOK = 266,
    FLOAT_TOK = 267,
    VOID_TOK = 268,
    CHAR_TOK = 269,
    RETURN_TOK = 270,
    CASE_TOK = 271,
    DEFAULT_TOK = 272,
    BREAK_TOK = 273,
    INC_TOK = 274,
    DEC_TOK = 275,
    EQUAL_TOK = 276,
    NOTEQUAL_TOK = 277,
    GTEQ_TOK = 278,
    LTEQ_TOK = 279,
    AND_TOK = 280,
    OR_TOK = 281,
    LSHIFT_TOK = 282,
    RSHIFT_TOK = 283,
    PLUSEQ_TOK = 284,
    MINUSEQ_TOK = 285,
    MULTEQ_TOK = 286,
    DIVEQ_TOK = 287,
    MODEQ_TOK = 288,
    ID_TOK = 289,
    INTCONST = 290,
    FLOATCONST = 291,
    STRING_LITERAL = 292,
    LPAREN_TOK = 293,
    RPAREN_TOK = 294,
    LCURLY_TOK = 295,
    RCURLY_TOK = 296,
    SQLBKT_TOK = 297,
    SQRBKT_TOK = 298,
    COMMA_TOK = 299,
    GT_TOK = 300,
    LT_TOK = 301,
    ASSIGN_TOK = 302,
    MINUS_TOK = 303,
    PLUS_TOK = 304,
    POWER_TOK = 305,
    SEMICOLON_TOK = 306,
    NOT_TOK = 307,
    XOR_TOK = 308,
    HASH_TOK = 309,
    DOT_TOK = 310,
    DIV_TOK = 311,
    MULT_TOK = 312,
    MODULO_TOK = 313,
    BITAND_TOK = 314,
    BITOR_TOK = 315,
    COLON_TOK = 316
  };
#endif
/* Tokens.  */
#define WHILE_TOK 258
#define DO_TOK 259
#define IF_TOK 260
#define ELSE_TOK 261
#define SWITCH_TOK 262
#define FOR_TOK 263
#define CONST_TOK 264
#define DOUBLE_TOK 265
#define INT_TOK 266
#define FLOAT_TOK 267
#define VOID_TOK 268
#define CHAR_TOK 269
#define RETURN_TOK 270
#define CASE_TOK 271
#define DEFAULT_TOK 272
#define BREAK_TOK 273
#define INC_TOK 274
#define DEC_TOK 275
#define EQUAL_TOK 276
#define NOTEQUAL_TOK 277
#define GTEQ_TOK 278
#define LTEQ_TOK 279
#define AND_TOK 280
#define OR_TOK 281
#define LSHIFT_TOK 282
#define RSHIFT_TOK 283
#define PLUSEQ_TOK 284
#define MINUSEQ_TOK 285
#define MULTEQ_TOK 286
#define DIVEQ_TOK 287
#define MODEQ_TOK 288
#define ID_TOK 289
#define INTCONST 290
#define FLOATCONST 291
#define STRING_LITERAL 292
#define LPAREN_TOK 293
#define RPAREN_TOK 294
#define LCURLY_TOK 295
#define RCURLY_TOK 296
#define SQLBKT_TOK 297
#define SQRBKT_TOK 298
#define COMMA_TOK 299
#define GT_TOK 300
#define LT_TOK 301
#define ASSIGN_TOK 302
#define MINUS_TOK 303
#define PLUS_TOK 304
#define POWER_TOK 305
#define SEMICOLON_TOK 306
#define NOT_TOK 307
#define XOR_TOK 308
#define HASH_TOK 309
#define DOT_TOK 310
#define DIV_TOK 311
#define MULT_TOK 312
#define MODULO_TOK 313
#define BITAND_TOK 314
#define BITOR_TOK 315
#define COLON_TOK 316

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 56 "a6_symtab.y" /* yacc.c:1909  */


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

#line 194 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
