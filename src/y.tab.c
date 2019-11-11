#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20130304

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "error.h"

extern int32_t LineNum;   /* declared in scanner.l */
extern char Buffer[512];  /* declared in scanner.l */
extern FILE *yyin;        /* declared by lex */
extern char *yytext;      /* declared by lex */

extern int yylex(void); 
static void yyerror(const char *msg);
#line 33 "y.tab.c"

#ifndef YYSTYPE
typedef int YYSTYPE;
#endif

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define ARRAY 257
#define BOOLEAN 258
#define INTEGER 259
#define REAL 260
#define STRING 261
#define ASSIGN 262
#define ID 263
#define BGN 264
#define DEF 265
#define DO 266
#define ELSE 267
#define END 268
#define FOR 269
#define IF 270
#define OF 271
#define PRINT 272
#define READ 273
#define THEN 274
#define TO 275
#define RETURN 276
#define WHILE 277
#define VAR 278
#define TRUE 279
#define FALSE 280
#define INT 281
#define OCT 282
#define FLOAT 283
#define SCIENTIFIC 284
#define STR 285
#define AND 286
#define OR 287
#define NOT 288
#define LE 289
#define GE 290
#define NE 291
#define MOD 292
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    1,    2,    2,    5,    5,    6,    6,    6,    7,
    7,   11,   11,   10,   10,   10,   10,   10,   10,   10,
    9,    9,    3,    3,   12,   12,   13,   13,    4,   15,
   15,   16,   16,   17,   17,   17,   17,   17,   17,   17,
   24,   24,   24,   24,   24,   24,   24,   24,   24,   24,
   24,   24,   24,   24,   24,   24,   24,   24,   18,   18,
   18,   18,   25,   26,   26,   19,   27,   27,   20,   21,
   22,   23,   28,   28,   28,   14,   14,   29,   29,    8,
    8,    8,    8,
};
static const short yylen[] = {                            2,
    5,    3,    0,    1,    2,    1,    5,   10,    5,    0,
    1,    3,    1,    1,    1,    1,    1,    1,    1,    1,
    6,    1,    0,    1,    2,    1,   10,    8,    4,    0,
    1,    2,    1,    2,    2,    2,    2,    2,    2,    2,
    3,    3,    2,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    2,    3,    1,    1,    1,    1,    3,    1,
    2,    2,    2,    0,    4,    7,    0,    2,    6,   10,
    2,    4,    0,    1,    3,    0,    1,    5,    3,    1,
    1,    1,    1,
};
static const short yydefred[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    6,   13,    0,
    0,    0,    0,    0,    0,   26,    5,    0,    0,    1,
    0,    0,    2,   25,    0,   80,   81,   82,   83,   14,
   15,   16,   17,   18,   19,   20,    0,    0,   12,    0,
    0,    0,    0,    0,    7,    9,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   33,
    0,    0,    0,    0,    0,    0,    0,    0,   79,    0,
    0,    0,    0,    0,   63,    0,    0,    0,    0,    0,
   55,   57,    0,   58,    0,    0,   62,    0,    0,   34,
   29,   32,   35,   36,   37,   38,   39,   40,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   43,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   78,    0,   72,
    0,    0,   54,    0,   41,   42,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   22,    0,   28,
    0,    0,   65,    0,    0,    0,    0,    0,    8,    0,
    0,   68,    0,   69,    0,   27,    0,   66,    0,    0,
    0,    0,   21,   70,
};
static const short yydgoto[] = {                          2,
    5,    6,   14,   57,    7,    8,   10,  148,  149,   81,
   11,   15,   16,   41,   58,   59,   60,   61,   62,   63,
   64,   65,   82,   83,   84,   75,  156,  105,   42,
};
static const short yysindex[] = {                      -240,
  -31,    0, -234, -212, -208, -201, -234,    0,    0,   11,
   32, -183,   43, -177, -201,    0,    0,  231, -166,    0,
 -212, -234,    0,    0, -159,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   45,   56,    0,   66,
   84,   82,  -35, -143,    0,    0, -152,  -37, -212,  -28,
 -124,  191,  191, -122,  191,  191,   98, -125,  -35,    0,
   87,   89,   90,   91,   94,  101,  -95, -112,    0, -177,
 -152,  119,  191,  191,    0,  -84,  -28,  191,  191,  191,
    0,    0,  149,    0,  157,   92,    0,  157,  142,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  191,  -90,
  -80,  134, -152,  157,  -27,  166,  -86,    0, -229,  129,
  -35,  191,  191,  191,  191,  191,  191,  191,  191,  191,
  191,  191,  -35,  157,    6,  -66, -177,    0,  191,    0,
   92,  -74,    0,  -69,    0,    0, -229, -229, -229, -229,
 -229, -229, -229, -229, -229,  -63,  -75,    0,  153,    0,
  -53,  157,    0,  -65,  -35,  -51,  -47,  -55,    0,  -40,
  -44,    0,  -46,    0,  -42,    0,  -35,    0,  -45,  -38,
    6,  -23,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0, -178,  186,    0,   -4,  232,    0,    0,    0,
  189,    0,    0,    0,    7,    0,    0,    0,    0,    0,
  -17,  269,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  227,    2,    0,    0,    0,    0,    0,  186,   10,
    0,    0,  214,    0,    0,    0,    0,    0, -154,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -25,    0,    0,    0,  -34,    0,    0,    0,
    0,    0,    0,    0,  215,  216,    0,  217,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    4,    0,    0,    0,    0,  -12,    0,
 -147,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    2,  222,    0,    0,    0,    0,    0,    0,
  -41,    0,    0,   14,    0,    0,   -5,   23,   30,   51,
   58,   86,   93,  114,  121,    0,    0,    0,    0,    0,
    0,    9,    0,    0,    2,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    2,    0,    0,    0,
    0,    0,    0,    0,
};
static const short yygindex[] = {                         0,
    0,  261,    0,   -9,    0,  281,   -6,    8,  120,  274,
    0,    0,  278,    0,  -77,    0,  235,    0,    0,    0,
    0,    0,  275,  407,  247,  164,    0,    0,    0,
};
#define YYTABLESIZE 546
static const short yytable[] = {                         64,
   64,   64,   64,   64,   23,   64,   56,   56,   56,   56,
   56,   73,   56,  130,   40,   73,  129,   64,   73,   64,
   71,   70,    1,   76,   56,   37,   56,    3,   53,   53,
   53,   53,   53,  134,   53,   48,   48,   48,   48,   48,
   10,   48,   72,    4,   74,  146,   53,   74,   53,   75,
    9,   64,   75,   48,   69,   48,  112,  113,   56,   12,
  101,   13,   74,   47,   47,   47,   47,   47,   18,   47,
   46,   46,   46,   46,   46,   19,   46,  162,  102,   20,
   53,   47,   21,   47,    3,    3,   22,   48,   46,  170,
   46,   44,   44,   44,   44,   44,   39,   44,   49,   49,
   49,   49,   49,   45,   49,   26,   27,   28,   29,   44,
  128,   44,   31,   31,   46,   47,   49,  151,   49,   30,
   30,   44,   46,   47,   48,   49,   52,   52,   52,   52,
   52,   68,   52,   51,   51,   51,   51,   51,   76,   51,
   86,   90,   91,   44,   52,   93,   52,   94,   95,   96,
   49,   51,   97,   51,   50,   50,   50,   50,   50,   98,
   50,   45,   45,   45,   45,   45,   99,   45,  100,  133,
  116,  114,   50,  115,   50,  117,  103,  107,   52,   45,
  125,   45,   74,  116,  114,   51,  115,  126,  117,  118,
  116,  114,  127,  115,  132,  117,  150,  155,  116,  114,
  154,  115,  118,  117,  157,  158,   50,  116,  114,  118,
  115,  159,  117,   45,  160,  161,  163,  118,  164,  165,
   64,  167,  166,  168,   64,  171,  118,   50,   22,  172,
   80,   56,   64,   51,   52,   79,   53,   54,  169,   56,
   55,   56,  174,   10,   64,   64,   11,   64,   64,   64,
   64,   56,   56,   53,   56,   56,   56,   56,  131,   23,
   48,   53,  147,   26,   27,   28,   29,   77,   48,   30,
   24,   64,   60,   61,   64,   71,   53,   53,   53,   53,
   59,   67,   43,   48,   48,   48,   48,   17,   47,   67,
  173,   38,   24,   92,  153,   46,   47,    0,    0,    0,
   87,    0,    0,   46,    0,   67,    0,    0,    0,    0,
    0,   47,   47,   47,   47,    0,   44,   66,   46,   46,
   46,   46,    0,   49,   44,    0,    0,    0,    0,    0,
    0,   49,    0,   66,    0,    0,    0,    0,    0,   44,
   44,   44,   44,    0,    0,    0,   49,   49,   49,   49,
    0,   52,    0,    0,    0,    0,    0,   67,   51,   52,
    0,    0,    0,    0,    0,    0,   51,    0,    0,   67,
    0,    0,    0,    0,   52,   52,   52,   52,    0,   50,
    0,   51,   51,   51,   51,   66,   45,   50,    0,    0,
    0,    0,    0,    0,   45,    0,    0,   66,    0,    0,
    0,   67,   50,   50,   50,   50,    0,  123,    0,   45,
   45,   45,   45,   67,  112,  113,    0,  119,  120,  121,
  122,    0,  111,    0,    0,    0,    0,  112,  113,   66,
  119,  120,  121,  122,  112,  113,    0,  119,  120,  121,
  122,   66,  112,  113,    0,  119,  120,  121,  122,    0,
    0,  112,  113,   77,  119,  120,  121,  122,    0,   85,
    0,   88,   89,    0,    0,    0,    0,    0,    0,   30,
   31,   32,   33,   34,   35,   36,    0,    0,   78,  104,
  106,    0,    0,    0,  108,  109,  110,   25,   26,   27,
   28,   29,    0,    0,    4,    4,    0,    0,    0,    4,
    4,    4,    0,    4,    4,  124,    0,    4,    4,   30,
   31,   32,   33,   34,   35,   36,    0,    0,  135,  136,
  137,  138,  139,  140,  141,  142,  143,  144,  145,    0,
    0,    3,    3,    0,    0,  152,    3,    3,    3,    0,
    3,    3,    0,    0,    3,    3,
};
static const short yycheck[] = {                         41,
   42,   43,   44,   45,   14,   47,   41,   42,   43,   44,
   45,   40,   47,   41,   21,   41,   44,   59,   44,   61,
   58,   59,  263,   41,   59,   18,   61,   59,   41,   42,
   43,   44,   45,  111,   47,   41,   42,   43,   44,   45,
   58,   47,   49,  278,   41,  123,   59,   44,   61,   41,
  263,   93,   44,   59,   47,   61,  286,  287,   93,  268,
   70,  263,   91,   41,   42,   43,   44,   45,   58,   47,
   41,   42,   43,   44,   45,   44,   47,  155,   71,  263,
   93,   59,   40,   61,  263,  264,  264,   93,   59,  167,
   61,   41,   42,   43,   44,   45,  263,   47,   41,   42,
   43,   44,   45,   59,   47,  258,  259,  260,  261,   59,
  103,   61,  267,  268,   59,   93,   59,  127,   61,  267,
  268,  281,   93,   58,   41,   44,   41,   42,   43,   44,
   45,  275,   47,   41,   42,   43,   44,   45,  263,   47,
  263,   44,  268,   93,   59,   59,   61,   59,   59,   59,
   93,   59,   59,   61,   41,   42,   43,   44,   45,   59,
   47,   41,   42,   43,   44,   45,  262,   47,  281,   41,
   42,   43,   59,   45,   61,   47,   58,  262,   93,   59,
  271,   61,   91,   42,   43,   93,   45,  268,   47,   61,
   42,   43,   59,   45,  281,   47,  263,  267,   42,   43,
  275,   45,   61,   47,  268,  281,   93,   42,   43,   61,
   45,   59,   47,   93,  268,  281,  268,   61,  266,  275,
  262,  266,  263,  270,  266,  271,   61,  263,  264,  268,
   40,  266,  274,  269,  270,   45,  272,  273,  281,  274,
  276,  277,  266,   58,  286,  287,   58,  289,  290,  291,
  292,  286,  287,  266,  289,  290,  291,  292,   93,  264,
  266,  274,  257,  258,  259,  260,  261,   41,  274,  268,
  264,  262,   59,   59,   59,   59,  289,  290,  291,  292,
   59,  268,   22,  289,  290,  291,  292,    7,  266,   43,
  171,   18,   15,   59,  131,  266,  274,   -1,   -1,   -1,
   54,   -1,   -1,  274,   -1,   59,   -1,   -1,   -1,   -1,
   -1,  289,  290,  291,  292,   -1,  266,   43,  289,  290,
  291,  292,   -1,  266,  274,   -1,   -1,   -1,   -1,   -1,
   -1,  274,   -1,   59,   -1,   -1,   -1,   -1,   -1,  289,
  290,  291,  292,   -1,   -1,   -1,  289,  290,  291,  292,
   -1,  266,   -1,   -1,   -1,   -1,   -1,  111,  266,  274,
   -1,   -1,   -1,   -1,   -1,   -1,  274,   -1,   -1,  123,
   -1,   -1,   -1,   -1,  289,  290,  291,  292,   -1,  266,
   -1,  289,  290,  291,  292,  111,  266,  274,   -1,   -1,
   -1,   -1,   -1,   -1,  274,   -1,   -1,  123,   -1,   -1,
   -1,  155,  289,  290,  291,  292,   -1,  266,   -1,  289,
  290,  291,  292,  167,  286,  287,   -1,  289,  290,  291,
  292,   -1,  274,   -1,   -1,   -1,   -1,  286,  287,  155,
  289,  290,  291,  292,  286,  287,   -1,  289,  290,  291,
  292,  167,  286,  287,   -1,  289,  290,  291,  292,   -1,
   -1,  286,  287,  263,  289,  290,  291,  292,   -1,   53,
   -1,   55,   56,   -1,   -1,   -1,   -1,   -1,   -1,  279,
  280,  281,  282,  283,  284,  285,   -1,   -1,  288,   73,
   74,   -1,   -1,   -1,   78,   79,   80,  257,  258,  259,
  260,  261,   -1,   -1,  263,  264,   -1,   -1,   -1,  268,
  269,  270,   -1,  272,  273,   99,   -1,  276,  277,  279,
  280,  281,  282,  283,  284,  285,   -1,   -1,  112,  113,
  114,  115,  116,  117,  118,  119,  120,  121,  122,   -1,
   -1,  263,  264,   -1,   -1,  129,  268,  269,  270,   -1,
  272,  273,   -1,   -1,  276,  277,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 292
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,
"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,"ARRAY","BOOLEAN","INTEGER","REAL","STRING","ASSIGN",
"ID","BGN","DEF","DO","ELSE","END","FOR","IF","OF","PRINT","READ","THEN","TO",
"RETURN","WHILE","VAR","TRUE","FALSE","INT","OCT","FLOAT","SCIENTIFIC","STR",
"AND","OR","NOT","LE","GE","NE","MOD",
};
static const char *yyrule[] = {
"$accept : program",
"program : ID ';' program_body END ID",
"program_body : var_dec func_dec compound_stat",
"var_dec :",
"var_dec : non_empty_var_dec",
"non_empty_var_dec : non_empty_var_dec variable",
"non_empty_var_dec : variable",
"variable : VAR id_list ':' TYPE ';'",
"variable : VAR id_list ':' ARRAY INT TO INT OF array_type ';'",
"variable : VAR id_list ':' constant ';'",
"id_list :",
"id_list : non_empty_id_list",
"non_empty_id_list : non_empty_id_list ',' ID",
"non_empty_id_list : ID",
"constant : TRUE",
"constant : FALSE",
"constant : INT",
"constant : OCT",
"constant : FLOAT",
"constant : SCIENTIFIC",
"constant : STR",
"array_type : ARRAY INT TO INT OF array_type",
"array_type : TYPE",
"func_dec :",
"func_dec : non_empty_func_dec",
"non_empty_func_dec : non_empty_func_dec function",
"non_empty_func_dec : function",
"function : ID '(' arguments ')' ':' TYPE ';' compound_stat END ID",
"function : ID '(' arguments ')' ';' compound_stat END ID",
"compound_stat : BGN var_dec statements END",
"statements :",
"statements : non_empty_statements",
"non_empty_statements : non_empty_statements stm",
"non_empty_statements : stm",
"stm : compound_stat ','",
"stm : simple_stat ';'",
"stm : conditional_stat ';'",
"stm : while_stat ';'",
"stm : for_stat ';'",
"stm : return_stat ';'",
"stm : function_invocation_stat ';'",
"expressions_stat : expressions_stat AND expressions_stat",
"expressions_stat : expressions_stat OR expressions_stat",
"expressions_stat : NOT expressions_stat",
"expressions_stat : expressions_stat '/' expressions_stat",
"expressions_stat : expressions_stat MOD expressions_stat",
"expressions_stat : expressions_stat '*' expressions_stat",
"expressions_stat : expressions_stat '-' expressions_stat",
"expressions_stat : expressions_stat '+' expressions_stat",
"expressions_stat : expressions_stat '=' expressions_stat",
"expressions_stat : expressions_stat NE expressions_stat",
"expressions_stat : expressions_stat GE expressions_stat",
"expressions_stat : expressions_stat LE expressions_stat",
"expressions_stat : '-' expressions_stat",
"expressions_stat : '(' expressions_stat ')'",
"expressions_stat : constant",
"expressions_stat : ID",
"expressions_stat : function_invocation_stat",
"expressions_stat : variable_reference",
"simple_stat : variable_reference ASSIGN expressions_stat",
"simple_stat : PRINT",
"simple_stat : PRINT expressions_stat",
"simple_stat : READ variable_reference",
"variable_reference : ID array_reference",
"array_reference :",
"array_reference : '[' expressions_stat ']' array_reference",
"conditional_stat : IF expressions_stat THEN statements condition_body END IF",
"condition_body :",
"condition_body : ELSE statements",
"while_stat : WHILE expressions_stat DO statements END DO",
"for_stat : FOR ID ASSIGN INT TO INT DO statements END DO",
"return_stat : RETURN expressions_stat",
"function_invocation_stat : ID '(' expression_list ')'",
"expression_list :",
"expression_list : expressions_stat",
"expression_list : expression_list ',' expressions_stat",
"arguments :",
"arguments : non_empty_arg",
"non_empty_arg : non_empty_arg ',' id_list ':' TYPE",
"non_empty_arg : id_list ':' TYPE",
"TYPE : BOOLEAN",
"TYPE : INTEGER",
"TYPE : REAL",
"TYPE : STRING",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 158 "parser.y"

void yyerror(const char *msg) {
    fprintf(stderr,
            "\n"
            "|-----------------------------------------------------------------"
            "---------\n"
            "| Error found in Line #%d: %s\n"
            "|\n"
            "| Unmatched token: %s\n"
            "|-----------------------------------------------------------------"
            "---------\n",
            LineNum, Buffer, yytext);
    exit(-1);
}

int main(int argc, const char *argv[]) {
    CHECK(argc == 2, "Usage: ./parser <filename>\n");

    FILE *fp = fopen(argv[1], "r");
    CHECK(fp != NULL, "fopen() fails.\n");
    yyin = fp;
    yyparse();

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");
    return 0;
}
#line 486 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 60:
#line 114 "parser.y"
	{printf("123");}
break;
case 61:
#line 115 "parser.y"
	{printf("456");}
break;
#line 700 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
