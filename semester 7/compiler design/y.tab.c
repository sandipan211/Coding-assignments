/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "a6_symtab.y" /* yacc.c:339  */

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
	void invalidate_scope_var(int target_scope);
	void initialize_symb_table();

#line 108 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 56 "a6_symtab.y" /* yacc.c:355  */


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

#line 288 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 305 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   385

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  197

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   316

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    82,    82,    83,    85,    84,    91,    90,    97,   102,
     106,   101,   111,   112,   115,   116,   119,   120,   121,   122,
     125,   129,   123,   137,   138,   139,   143,   144,   147,   148,
     149,   153,   154,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   171,   172,   173,   174,   176,   178,   179,   183,
     192,   192,   196,   199,   200,   206,   211,   216,   222,   224,
     225,   226,   227,   228,   229,   231,   237,   246,   247,   248,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   263,
     264,   267,   268,   269,   270,   274,   275,   276,   277,   281,
     287,   290,   297,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   314,   317,   318,   319
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WHILE_TOK", "DO_TOK", "IF_TOK",
  "ELSE_TOK", "SWITCH_TOK", "FOR_TOK", "CONST_TOK", "DOUBLE_TOK",
  "INT_TOK", "FLOAT_TOK", "VOID_TOK", "CHAR_TOK", "RETURN_TOK", "CASE_TOK",
  "DEFAULT_TOK", "BREAK_TOK", "INC_TOK", "DEC_TOK", "EQUAL_TOK",
  "NOTEQUAL_TOK", "GTEQ_TOK", "LTEQ_TOK", "AND_TOK", "OR_TOK",
  "LSHIFT_TOK", "RSHIFT_TOK", "PLUSEQ_TOK", "MINUSEQ_TOK", "MULTEQ_TOK",
  "DIVEQ_TOK", "MODEQ_TOK", "ID_TOK", "INTCONST", "FLOATCONST",
  "STRING_LITERAL", "LPAREN_TOK", "RPAREN_TOK", "LCURLY_TOK", "RCURLY_TOK",
  "SQLBKT_TOK", "SQRBKT_TOK", "COMMA_TOK", "GT_TOK", "LT_TOK",
  "ASSIGN_TOK", "MINUS_TOK", "PLUS_TOK", "POWER_TOK", "SEMICOLON_TOK",
  "NOT_TOK", "XOR_TOK", "HASH_TOK", "DOT_TOK", "DIV_TOK", "MULT_TOK",
  "MODULO_TOK", "BITAND_TOK", "BITOR_TOK", "COLON_TOK", "$accept", "S",
  "$@1", "$@2", "block", "$@3", "$@4", "blocks", "STATEMENTS", "stmt",
  "$@5", "$@6", "entry_ctrl_loop", "cases", "if_else_ladder", "expression",
  "datatype", "function_args", "int_arg", "declaration", "$@7",
  "assign_stmt", "assign_ops", "id_token", "data", "relational_expression",
  "op", "logi_operator", "unary_expression", "logic_expression",
  "arith_expression", "arith_operator", "call_fn", "call_args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316
};
# endif

#define YYPACT_NINF -111

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-111)))

#define YYTABLE_NINF -67

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      82,  -111,  -111,  -111,  -111,     8,   -22,   -35,  -111,   127,
     -19,   -14,    82,  -111,  -111,  -111,  -111,  -111,     3,     2,
    -111,     9,    18,    22,  -111,  -111,  -111,    25,   -21,  -111,
      33,    45,    48,  -111,  -111,    13,  -111,  -111,  -111,    34,
    -111,  -111,  -111,    92,   206,  -111,  -111,  -111,  -111,    38,
    -111,    46,  -111,  -111,    82,    40,  -111,  -111,  -111,  -111,
     206,  -111,   289,    50,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,   206,   206,  -111,   206,  -111,    82,
      46,  -111,    82,    53,    60,  -111,  -111,  -111,  -111,  -111,
    -111,    82,  -111,   206,  -111,   168,  -111,  -111,    65,    46,
      68,    72,    73,   206,   334,  -111,  -111,  -111,  -111,    46,
      62,    80,  -111,   -19,    -4,  -111,  -111,  -111,    98,   112,
      98,   206,    87,  -111,   164,   168,    88,  -111,  -111,   181,
      98,    89,    42,    99,    91,   100,    96,  -111,  -111,  -111,
     107,  -111,   206,   206,   206,   206,   206,   206,    98,    46,
     113,   206,    -4,  -111,  -111,  -111,  -111,  -111,  -111,   108,
     148,  -111,   104,    98,   111,     1,  -111,    10,    98,  -111,
    -111,   129,  -111,   142,   120,  -111,   133,    98,   124,  -111,
     145,   299,   152,  -111,   219,  -111,   153,    46,   270,   144,
    -111,   148,   146,  -111,  -111,    10,  -111
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       8,    44,    42,    43,    45,     0,     0,     0,     1,    66,
      52,    50,     8,    60,    61,    63,    62,    64,    46,     0,
      59,     0,     0,     0,    51,     3,     4,     0,     0,    48,
       0,     0,     0,    81,    82,    80,    67,    68,    69,     0,
      83,    84,    79,    57,     0,    56,    55,    54,    58,     0,
      65,     0,    49,     6,     0,     0,    87,    88,    85,    86,
     106,    80,     0,     0,    99,   100,    94,    93,    98,    95,
      96,    97,   102,   101,     0,     0,    90,     0,     9,     8,
       0,    47,     8,   104,     0,    92,    89,    91,    53,    15,
       5,     8,     2,   106,   103,    13,     7,   105,     0,     0,
       0,     0,     0,     0,    80,    16,    15,    10,    14,     0,
       0,    35,    36,    37,     0,    38,    40,    41,    78,     0,
      78,     0,     0,    25,     0,    13,     0,    23,    17,    33,
      78,     0,     0,     0,     0,     0,     0,    39,    12,    11,
       0,    27,     0,     0,     0,     0,     0,     0,    78,     0,
       0,     0,    76,    72,    73,    74,    75,    70,    71,     0,
      18,    20,     0,    78,     0,     0,    19,    30,    78,    77,
      24,     0,    32,     0,     0,    21,     0,    78,     0,    15,
       0,     0,     0,    15,     0,    22,     0,     0,     0,     0,
      26,     0,     0,    29,    31,    30,    28
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -111,    -1,  -111,  -111,   -49,  -111,  -111,    71,   -99,  -111,
    -111,  -111,  -111,    11,    16,    28,   -18,  -111,   161,   -86,
    -111,    -2,  -111,  -111,  -111,  -110,   -20,   -40,   197,   -16,
     193,  -111,   214,   143
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,    51,    80,   106,    89,   126,   107,    95,   108,
     167,   180,   109,   175,   166,   110,     6,    28,    29,     7,
      24,   113,    21,    11,    42,   131,   132,    44,   115,   116,
      47,    75,   117,    84
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      27,    43,    79,    74,    10,    46,   171,   125,     8,   112,
     134,    25,     9,     1,     2,     3,    12,     4,    53,    62,
     140,    33,    34,    54,    76,    22,   173,   174,    31,    32,
      23,    91,    58,    59,    33,    34,    27,    30,   159,   112,
      83,    78,    26,    35,    36,    37,    38,    39,    40,    41,
     119,    60,    49,   169,    86,    87,    50,    88,   176,    52,
     127,    40,    41,   142,   143,   144,   145,   182,    61,    36,
      37,    38,    39,    83,    74,   114,    55,   111,    90,    56,
     184,    92,    57,   123,   188,    77,    78,   146,   147,    85,
      96,    82,     1,     2,     3,   112,     4,    93,   112,    94,
     160,   135,   112,   118,   114,   114,   120,   111,   137,    10,
     121,   122,   163,   128,   129,   133,   172,    33,    34,    64,
      65,   136,   153,   154,   155,   156,   157,   158,   141,   139,
     149,   162,    61,    36,    37,    38,   130,   148,   191,   150,
      66,    67,    68,   151,    40,    41,   152,   164,    69,    70,
      71,    72,    73,   161,   165,   168,    13,    14,    15,    16,
      17,   114,   170,   111,   114,    18,   111,   177,   114,    19,
     111,    98,    99,   100,    20,   101,   102,   178,     1,     2,
       3,   179,     4,   103,   181,   183,   185,    31,    32,    33,
      34,   187,   190,    33,    34,   193,   138,   195,    61,    36,
      37,    38,   104,    36,    37,    38,   196,   194,    78,   186,
      13,    14,    15,    16,    17,    81,    40,    41,    45,   105,
      40,    41,    98,    99,   100,   -66,   101,   102,    20,     1,
       2,     3,    63,     4,   103,    48,    97,   189,    31,    32,
      61,    36,    37,    38,    33,    34,     0,     0,     0,     0,
       0,     0,     0,   104,    36,    37,    38,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,    40,    41,    98,    99,   100,     0,   101,   102,     0,
       1,     2,     3,     0,     4,   103,     0,     0,   192,    31,
      32,     0,     0,     0,     0,    33,    34,     0,     0,     0,
       0,     0,     0,     0,   104,    36,    37,    38,     0,     1,
       2,     3,     0,     4,     0,     0,    64,    65,    31,    32,
       0,   105,    40,    41,    33,    34,     0,     0,     0,     0,
       0,     0,     0,   104,    36,    37,    38,    66,    67,    68,
       0,     0,     0,     0,     0,    69,    70,    71,    72,    73,
       0,    40,    41,    58,    59,   124,     0,     0,     0,     0,
       0,     0,     0,    13,    14,    15,    16,    17,     0,     0,
       0,     0,    60,   -34,     0,     0,     0,     0,     0,     0,
       0,    20,     0,     0,     0,   -34
};

static const yytype_int16 yycheck[] =
{
      18,    21,    51,    43,     6,    21,     5,   106,     0,    95,
     120,    12,    34,    10,    11,    12,    51,    14,    39,    39,
     130,    25,    26,    44,    44,    44,    16,    17,    19,    20,
      44,    80,    19,    20,    25,    26,    54,    35,   148,   125,
      60,    40,    39,    34,    35,    36,    37,    38,    52,    53,
      99,    38,    34,   163,    74,    75,    34,    77,   168,    34,
     109,    52,    53,    21,    22,    23,    24,   177,    34,    35,
      36,    37,    38,    93,   114,    95,    43,    95,    79,    34,
     179,    82,    34,   103,   183,    47,    40,    45,    46,    39,
      91,    51,    10,    11,    12,   181,    14,    44,   184,    39,
     149,   121,   188,    38,   124,   125,    38,   125,   124,   111,
      38,    38,   152,    51,    34,     3,   165,    25,    26,    27,
      28,    34,   142,   143,   144,   145,   146,   147,    39,    41,
      39,   151,    34,    35,    36,    37,    38,    38,   187,    39,
      48,    49,    50,    47,    52,    53,    39,    39,    56,    57,
      58,    59,    60,    40,     6,    51,    29,    30,    31,    32,
      33,   181,    51,   181,   184,    38,   184,    38,   188,    42,
     188,     3,     4,     5,    47,     7,     8,    35,    10,    11,
      12,    61,    14,    15,    51,    61,    41,    19,    20,    25,
      26,    39,    39,    25,    26,    51,   125,    51,    34,    35,
      36,    37,    34,    35,    36,    37,   195,   191,    40,   181,
      29,    30,    31,    32,    33,    54,    52,    53,    21,    51,
      52,    53,     3,     4,     5,    44,     7,     8,    47,    10,
      11,    12,    39,    14,    15,    21,    93,    18,    19,    20,
      34,    35,    36,    37,    25,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    52,    53,     3,     4,     5,    -1,     7,     8,    -1,
      10,    11,    12,    -1,    14,    15,    -1,    -1,    18,    19,
      20,    -1,    -1,    -1,    -1,    25,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    -1,    10,
      11,    12,    -1,    14,    -1,    -1,    27,    28,    19,    20,
      -1,    51,    52,    53,    25,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    48,    49,    50,
      -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,
      -1,    52,    53,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    51
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    11,    12,    14,    63,    78,    81,     0,    34,
      83,    85,    51,    29,    30,    31,    32,    33,    38,    42,
      47,    84,    44,    44,    82,    63,    39,    78,    79,    80,
      35,    19,    20,    25,    26,    34,    35,    36,    37,    38,
      52,    53,    86,    88,    89,    90,    91,    92,    94,    34,
      34,    64,    34,    39,    44,    43,    34,    34,    19,    20,
      38,    34,    88,    92,    27,    28,    48,    49,    50,    56,
      57,    58,    59,    60,    89,    93,    88,    47,    40,    66,
      65,    80,    51,    88,    95,    39,    88,    88,    88,    67,
      63,    66,    63,    44,    39,    70,    63,    95,     3,     4,
       5,     7,     8,    15,    34,    51,    66,    69,    71,    74,
      77,    78,    81,    83,    88,    90,    91,    94,    38,    66,
      38,    38,    38,    88,    21,    70,    68,    66,    51,    34,
      38,    87,    88,     3,    87,    88,    34,    91,    69,    41,
      87,    39,    21,    22,    23,    24,    45,    46,    38,    39,
      39,    47,    39,    88,    88,    88,    88,    88,    88,    87,
      66,    40,    88,    89,    39,     6,    76,    72,    51,    87,
      51,     5,    66,    16,    17,    75,    87,    38,    35,    61,
      73,    51,    87,    61,    70,    41,    77,    39,    70,    18,
      39,    66,    18,    51,    76,    51,    75
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    63,    64,    63,    65,    63,    63,    67,
      68,    66,    69,    69,    70,    70,    71,    71,    71,    71,
      72,    73,    71,    71,    71,    71,    74,    74,    75,    75,
      75,    76,    76,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    78,    78,    78,    78,    79,    79,    79,    80,
      82,    81,    81,    83,    83,    83,    83,    83,    83,    84,
      84,    84,    84,    84,    84,    85,    85,    86,    86,    86,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    88,
      88,    89,    89,    89,    89,    90,    90,    90,    90,    91,
      91,    92,    92,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    94,    95,    95,    95
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     7,     3,     0,     7,     0,     8,     0,     0,
       0,     6,     3,     0,     2,     0,     1,     2,     5,     6,
       0,     0,     9,     2,     7,     2,    10,     4,     7,     5,
       0,     7,     2,     2,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     0,     3,     1,     2,
       0,     3,     2,     5,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     5,     0,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     3,
       2,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     1,     3,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 85 "a6_symtab.y" /* yacc.c:1646  */
    {
			function_number++;
			if(DEBUG_INFO)
				printf("\nFn. no. %d : Main Function found; line no: %d\n",function_number,yylineno);
		}
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 91 "a6_symtab.y" /* yacc.c:1646  */
    {
			function_number++;
			if(DEBUG_INFO)
				printf("\nFn. no. %d : User-defined Function found; line no: %d\n",function_number,yylineno);
		}
#line 1581 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 102 "a6_symtab.y" /* yacc.c:1646  */
    { gscope += 1; 
					  printf("\n Scope increased by 1 - new scope= %d",gscope);
					}
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 106 "a6_symtab.y" /* yacc.c:1646  */
    { gscope -= 1; 
		 			  printf("\n Scope decreased by 1 - new scope= %d",gscope);
		 			}
#line 1597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 125 "a6_symtab.y" /* yacc.c:1646  */
    { gscope += 1; 
			  printf("\n Scope increased by 1 - new scope= %d",gscope);
			}
#line 1605 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 129 "a6_symtab.y" /* yacc.c:1646  */
    {
				check_scope_declaration((yyvsp[-4].n).name,gscope);
				{ gscope -= 1; 
				  printf("\n Scope decreased by 1 - new scope= %d",gscope);
				}
			}
#line 1616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 171 "a6_symtab.y" /* yacc.c:1646  */
    {(yyval.t).i_type=1;}
#line 1622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 172 "a6_symtab.y" /* yacc.c:1646  */
    {(yyval.t).i_type=2;}
#line 1628 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 173 "a6_symtab.y" /* yacc.c:1646  */
    {(yyval.t).i_type=3;}
#line 1634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 174 "a6_symtab.y" /* yacc.c:1646  */
    {(yyval.t).i_type=4;}
#line 1640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 183 "a6_symtab.y" /* yacc.c:1646  */
    {
          	printf("\nvarsingle insert symb: %s",(yyvsp[0].n).name);
	      	insert_symbol((yyvsp[0].n).name);
	      	var_buffer[var_buffer_index++] = (yyvsp[0].n).name[0];
	      	assign_type((yyvsp[-1].t).i_type,1);
	      }
#line 1651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 192 "a6_symtab.y" /* yacc.c:1646  */
    {printf("\nDeclared inside");}
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 193 "a6_symtab.y" /* yacc.c:1646  */
    {
				assign_type((yyvsp[-2].t).i_type,1);									// char a, b, c
			}
#line 1665 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 201 "a6_symtab.y" /* yacc.c:1646  */
    {
						//printf("\nvar: %s",$1.name);
						check_scope_declaration((yyvsp[-2].n).name,gscope);
						assign_stmt_type_check((yyvsp[-2].n).name,(yyvsp[0].p).i_type,gscope);
					}
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 207 "a6_symtab.y" /* yacc.c:1646  */
    {
						check_scope_declaration((yyvsp[-2].n).name,gscope);
						assign_stmt_type_check((yyvsp[-2].n).name,(yyvsp[0].p).i_type,gscope);
					}
#line 1684 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 212 "a6_symtab.y" /* yacc.c:1646  */
    {
						check_scope_declaration((yyvsp[-2].n).name,gscope);
						assign_stmt_type_check((yyvsp[-2].n).name,(yyvsp[0].p).i_type,gscope);
					}
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 217 "a6_symtab.y" /* yacc.c:1646  */
    {
						check_scope_declaration((yyvsp[-2].n).name,gscope);
						check_scope_declaration((yyvsp[0].n).name,gscope);			//working fine till here
						check_type((yyvsp[-2].n).name,(yyvsp[0].n).name);
					}
#line 1703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 232 "a6_symtab.y" /* yacc.c:1646  */
    {
	      	//printf("\nvarmulti: %s",$3.name);
	      	insert_symbol((yyvsp[0].n).name);
	      	var_buffer[var_buffer_index++] = (yyvsp[0].n).name[0];		//store the new variable name encountered
	      }
#line 1713 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 238 "a6_symtab.y" /* yacc.c:1646  */
    {
          	//printf("\nvarsingle: %s",$1.name);
	      	insert_symbol((yyvsp[0].n).name);
	      	var_buffer[var_buffer_index++] = (yyvsp[0].n).name[0];
	      }
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 251 "a6_symtab.y" /* yacc.c:1646  */
    {check_scope_declaration((yyvsp[-2].n).name,gscope);}
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 252 "a6_symtab.y" /* yacc.c:1646  */
    {check_scope_declaration((yyvsp[-2].n).name,gscope);}
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 253 "a6_symtab.y" /* yacc.c:1646  */
    {check_scope_declaration((yyvsp[-2].n).name,gscope);}
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 254 "a6_symtab.y" /* yacc.c:1646  */
    {check_scope_declaration((yyvsp[-2].n).name,gscope);}
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 255 "a6_symtab.y" /* yacc.c:1646  */
    {check_scope_declaration((yyvsp[-2].n).name,gscope);}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 256 "a6_symtab.y" /* yacc.c:1646  */
    {check_scope_declaration((yyvsp[-2].n).name,gscope);}
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 274 "a6_symtab.y" /* yacc.c:1646  */
    {check_scope_declaration((yyvsp[-1].n).name,gscope);}
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 275 "a6_symtab.y" /* yacc.c:1646  */
    {check_scope_declaration((yyvsp[-1].n).name,gscope);}
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 276 "a6_symtab.y" /* yacc.c:1646  */
    {check_scope_declaration((yyvsp[0].n).name,gscope);}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 277 "a6_symtab.y" /* yacc.c:1646  */
    {check_scope_declaration((yyvsp[0].n).name,gscope);}
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 282 "a6_symtab.y" /* yacc.c:1646  */
    {
							check_scope_declaration((yyvsp[-2].n).name,gscope);
							check_scope_declaration((yyvsp[0].n).name,gscope);
							(yyval.p).i_type = check_type((yyvsp[-2].n).name,(yyvsp[0].n).name);
						}
#line 1793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 291 "a6_symtab.y" /* yacc.c:1646  */
    {

							check_scope_declaration((yyvsp[-2].n).name,gscope);
							check_scope_declaration((yyvsp[0].n).name,gscope);
							(yyval.p).i_type = check_type((yyvsp[-2].n).name,(yyvsp[0].n).name);
						}
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 297 "a6_symtab.y" /* yacc.c:1646  */
    {}
#line 1810 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1814 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 324 "a6_symtab.y" /* yacc.c:1906  */


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
	//printf("yyerror: %s\n",s);
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
		//printf("\nCurrent scope inside check_scope_declaration() for %s is:  %d in line no: %d\n",name,gscope,yylineno);
	
	//printf("\nname = %s",name);		
	if(found(name))										/*if variable is already in symbol table,
														  its scope can be obtained */
	{
		//printf("\nscope = %d",symbol_table[function_number][name[0]].type[scope]);
		if (is_number(name) || symbol_table[function_number][name[0]].type[scope] != 0)
			return;										// if variable is present in current scope
		
		else
		{									// if variable is present in any of the scopes until present scope
			for(int i = 0; i < scope ; i++)
			{
				if(symbol_table[function_number][name[0]].type[i] != 0)
					return;
				
			}
			yyerror("Un-declared till now1");
		}
		yyerror("Un-declared till now2");
	}
	yyerror("Un-declared till now3");
}


/* search for the variable name in the current symbol table. The variable is present in the table if either:
	1. the array pos. with the ascii value of first char of var_name as index is not empty
	2. if it is a var_name, length >1
	3. it is a number
*/ 
int found(char *name)									
{
	return symbol_table[function_number][name[0]].entry_index != -1  || strlen(name) >= 1 || is_number(name);
}


void assign_stmt_type_check(char *name,int type,int scope)
{
	if(DEBUG_INFO)
		//printf("\nCurrent scope inside assign_stmt_type_check() is: %d in lineno: %d\n",gscope,yylineno);
	
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
		//printf("\nCurrent scope inside check_type() for %s, %s is: %d in line_no: %d\n",name1,name2,gscope,yylineno);
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
		//printf("%s === %s\n",name1,name2);
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

	//printf("\nvar: %s",name);
	int index = name[0];
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
		//printf("\nvb[i]: %d", var_buffer[i]);
		if(var_buffer[i] >= 0)
		{
			node = symbol_table[function_number][var_buffer[i]];
			//printf("\nnode.varname = %c, temp_table[var_buffer[i]].var_name = %c",node.var_name,temp_table[var_buffer[i]].var_name);
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
						strncpy(decision,(char*)"Float",5);
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
				printf("| index: %d name: %c scope: %d type = %s in the scope %d line_no: %d \t   |\n",symbol_table[table_index][i].entry_index,symbol_table[table_index][i].var_name,symbol_table[table_index][i].scope_array_index,decision,symbol_table[table_index][i].scope[j],symbol_table[table_index][i].line_no[symbol_table[table_index][i].scope[j]]);
				free(decision);
			}
			printf("----------------------------------------------------------------------------------------------------\n");
		}
	}
}
