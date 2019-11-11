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
   24,   24,   24,   24,   24,   24,   24,   24,   24,   24,
   18,   18,   18,   25,   26,   26,   19,   27,   27,   20,
   21,   22,   23,   28,   28,   28,   14,   14,   29,   29,
    8,    8,    8,    8,
};
static const short yylen[] = {                            2,
    5,    3,    0,    1,    2,    1,    5,   10,    5,    0,
    1,    3,    1,    1,    1,    1,    1,    1,    1,    1,
    6,    1,    0,    1,    2,    1,   10,    8,    4,    0,
    1,    2,    1,    2,    2,    1,    1,    1,    2,    2,
    3,    3,    2,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    2,    3,    1,    1,    1,    1,
    3,    2,    2,    2,    0,    4,    7,    0,    2,    6,
   10,    2,    4,    0,    1,    3,    0,    1,    5,    3,
    1,    1,    1,    1,
};
static const short yydefred[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    6,   13,    0,
    0,    0,    0,    0,    0,   26,    5,    0,    0,    1,
    0,    0,    2,   25,    0,   81,   82,   83,   84,   14,
   15,   16,   17,   18,   19,   20,    0,    0,   12,    0,
    0,    0,    0,    0,    7,    9,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   33,
    0,   36,   37,   38,    0,    0,    0,    0,   80,    0,
    0,    0,    0,    0,   64,    0,    0,    0,    0,    0,
   57,   59,    0,   60,    0,    0,   63,    0,    0,   34,
   29,   32,   35,   39,   40,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   43,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   79,    0,   73,    0,
    0,   56,    0,   41,   42,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   22,    0,
   28,    0,    0,   66,    0,    0,    0,    0,    0,    8,
    0,    0,   69,    0,   70,    0,   27,    0,   67,    0,
    0,    0,    0,   21,   71,
};
static const short yydgoto[] = {                          2,
    5,    6,   14,   57,    7,    8,   10,  149,  150,   81,
   11,   15,   16,   41,   58,   59,   60,   61,   62,   63,
   64,   65,   82,   83,   84,   75,  157,  102,   42,
};
static const short yysindex[] = {                      -249,
  -35,    0, -237, -219, -222, -212, -237,    0,    0,    2,
    9, -205,   40, -157, -212,    0,    0,  206, -148,    0,
 -219, -237,    0,    0, -155,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   74,   85,    0,   84,
  121,  127,   93, -102,    0,    0,  -30,  -36, -219,  -28,
  -84,  196,  196,  -82,  196,  196,  142,  -77,   93,    0,
  138,    0,    0,    0,  143,  145,  -56,  -74,    0, -157,
  -30,  150,  196,  196,    0,  -48,  -28,  196,  196,  196,
    0,    0,  221,    0,  285,  124,    0,  285,  248,    0,
    0,    0,    0,    0,    0,  196,  -54,  -45,  165,  -30,
  285,   64,  411,  -55,    0, -208,  158,   93,  196,  196,
  196,  196,  196,  196,  196,  196,  196,  196,  196,  196,
  196,   93,  285,   13,  -26, -157,    0,  196,    0,  124,
  -40,    0,  -25,    0,    0, -208, -208, -208, -208, -208,
 -208, -208, -208, -208, -208, -208,  -29,  -22,    0,  188,
    0,   -8,  285,    0,  -16,   93,   -1,   10,   19,    0,
   12,   22,    0,   28,    0,   18,    0,   93,    0,   29,
   33,   13,   36,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0, -177,  245,    0,   41,  315,    0,    0,    0,
  249,    0,    0,    0,   47,    0,    0,    0,    0,    0,
  -24,  326,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  275,   49,    0,    0,    0,    0,    0,  245,   61,
    0,    0,    0,    0,    0,    0,    0,    0, -117,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   83,    0,    0,    0,  -34,    0,    0,    0,
    0,    0,    0,    0,  265,  270,    0,  272,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   99,    0,    0,    0,    0,  -12,    0,  -78,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   49,  276,    0,    0,    0,    0,    0,    0,  -41,
    0,    0,   68,    0,    0,   -5,   23,   30,   52,   59,
   87,   94,  116,  123,  151,  377,    0,    0,    0,    0,
    0,    0,  128,    0,    0,   49,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   49,    0,    0,
    0,    0,    0,    0,    0,
};
static const short yygindex[] = {                         0,
    0,  312,    0,   -9,    0,  330,   -6,   -2,  166,  321,
    0,    0,  339,    0,  -46,    0,  296,    0,    0,    0,
    0,    0,   66,  445,  184,  228,    0,    0,    0,
};
#define YYTABLESIZE 703
static const short yytable[] = {                         65,
   65,   65,   65,   65,   23,   65,   58,   58,   58,   58,
   58,   73,   58,    1,   40,   37,   77,   65,   65,   65,
   65,   71,   70,    3,   58,   58,   58,   58,   55,   55,
   55,   55,   55,   10,   55,   54,   54,   54,   54,   54,
    4,   54,   72,    9,   69,   12,   55,   55,   55,   55,
   13,   65,   19,   54,   54,   54,   54,   20,   58,   18,
   98,  133,   74,   53,   53,   53,   53,   53,   99,   53,
   52,   52,   52,   52,   52,  147,   52,  109,  110,   21,
   55,   53,   53,   53,   53,    3,    3,   54,   52,   52,
   52,   52,   50,   50,   50,   50,   50,  127,   50,   48,
   48,   48,   48,   48,  129,   48,   22,  128,   66,  163,
   50,   50,   50,   50,   39,   53,  152,   48,   48,   48,
   48,  171,   52,   74,   66,   44,   74,   49,   49,   49,
   49,   49,   45,   49,   47,   47,   47,   47,   47,   75,
   47,   47,   75,   46,   50,   49,   49,   49,   49,   31,
   31,   48,   47,   47,   47,   47,   46,   46,   46,   46,
   46,   48,   46,   45,   45,   45,   45,   45,   76,   45,
   49,   76,   68,   66,   46,   46,   46,   46,   76,   49,
   86,   45,   45,   45,   45,   90,   47,   66,   30,   30,
   91,   44,   44,   44,   44,   44,   93,   44,  132,  113,
  111,   94,  112,   95,  114,   96,   97,  100,   46,   44,
   44,   44,   44,  104,   74,   45,  124,  116,  117,  115,
   65,   66,  125,  126,   65,  131,   67,   26,   27,   28,
   29,   58,   65,   66,  155,   80,  151,   87,  158,   58,
   79,  156,   67,   44,   65,   65,  160,   65,   65,   65,
   65,   58,   58,   55,   58,   58,   58,   58,  159,  161,
   54,   55,  113,  111,  162,  112,  164,  114,   54,  148,
   26,   27,   28,   29,  167,  165,   55,   55,   55,   55,
  116,  117,  115,   54,   54,   54,   54,  168,   53,  113,
  111,   67,  112,  166,  114,   52,   53,  169,  170,  172,
  173,  175,   10,   52,   23,   67,   11,  116,  117,  115,
   24,   53,   53,   53,   53,   78,   30,   50,   52,   52,
   52,   52,   65,   62,   48,   50,  113,  111,   65,  112,
   72,  114,   48,   43,   61,   68,   17,  174,   38,   67,
   50,   50,   50,   50,  116,  117,  115,   48,   48,   48,
   48,   67,   49,   24,   92,   50,   22,  154,    0,   47,
   49,   51,   52,    0,   53,   54,    0,   47,   55,   56,
    0,    0,    0,    0,    0,   49,   49,   49,   49,    0,
    0,   46,   47,   47,   47,   47,    0,    0,   45,   46,
    0,    0,    0,    0,    0,    0,   45,    0,    0,    0,
    0,    0,    0,    0,   46,   46,   46,   46,    0,    0,
    0,   45,   45,   45,   45,    0,   44,   51,   51,   51,
   51,   51,    0,   51,   44,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   51,   51,   51,   51,   44,
   44,   44,   44,  109,  110,    0,  118,  119,  120,  121,
    0,    0,  113,  111,    0,  112,    0,  114,   77,    0,
    0,    0,   25,   26,   27,   28,   29,    0,    0,   51,
  116,  117,  115,    0,   30,   31,   32,   33,   34,   35,
   36,    0,    0,   78,   30,   31,   32,   33,   34,   35,
   36,    0,    0,    0,  108,    0,    0,   85,    0,   88,
   89,    0,    0,  130,    0,    0,  109,  110,    0,  118,
  119,  120,  121,  122,    0,    0,    0,  101,  103,    0,
    0,    0,  105,  106,  107,    0,    0,    0,    0,    0,
    0,    0,    0,  109,  110,    0,  118,  119,  120,  121,
  123,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  134,  135,  136,  137,  138,  139,  140,
  141,  142,  143,  144,  145,  146,    0,    0,    0,    0,
  109,  110,  153,  118,  119,  120,  121,    4,    4,    0,
    0,    0,    4,    4,    4,    0,    4,    4,    3,    3,
    4,    4,    0,    3,    3,    3,    0,    3,    3,    0,
    0,    3,    3,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   51,    0,    0,    0,    0,    0,    0,    0,
   51,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   51,   51,   51,   51,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  109,  110,    0,  118,
  119,  120,  121,
};
static const short yycheck[] = {                         41,
   42,   43,   44,   45,   14,   47,   41,   42,   43,   44,
   45,   40,   47,  263,   21,   18,   41,   59,   60,   61,
   62,   58,   59,   59,   59,   60,   61,   62,   41,   42,
   43,   44,   45,   58,   47,   41,   42,   43,   44,   45,
  278,   47,   49,  263,   47,  268,   59,   60,   61,   62,
  263,   93,   44,   59,   60,   61,   62,  263,   93,   58,
   70,  108,   91,   41,   42,   43,   44,   45,   71,   47,
   41,   42,   43,   44,   45,  122,   47,  286,  287,   40,
   93,   59,   60,   61,   62,  263,  264,   93,   59,   60,
   61,   62,   41,   42,   43,   44,   45,  100,   47,   41,
   42,   43,   44,   45,   41,   47,  264,   44,   43,  156,
   59,   60,   61,   62,  263,   93,  126,   59,   60,   61,
   62,  168,   93,   41,   59,  281,   44,   41,   42,   43,
   44,   45,   59,   47,   41,   42,   43,   44,   45,   41,
   47,   58,   44,   59,   93,   59,   60,   61,   62,  267,
  268,   93,   59,   60,   61,   62,   41,   42,   43,   44,
   45,   41,   47,   41,   42,   43,   44,   45,   41,   47,
   44,   44,  275,  108,   59,   60,   61,   62,  263,   93,
  263,   59,   60,   61,   62,   44,   93,  122,  267,  268,
  268,   41,   42,   43,   44,   45,   59,   47,   41,   42,
   43,   59,   45,   59,   47,  262,  281,   58,   93,   59,
   60,   61,   62,  262,   91,   93,  271,   60,   61,   62,
  262,  156,  268,   59,  266,  281,   43,  258,  259,  260,
  261,  266,  274,  168,  275,   40,  263,   54,  268,  274,
   45,  267,   59,   93,  286,  287,   59,  289,  290,  291,
  292,  286,  287,  266,  289,  290,  291,  292,  281,  268,
  266,  274,   42,   43,  281,   45,  268,   47,  274,  257,
  258,  259,  260,  261,  263,  266,  289,  290,  291,  292,
   60,   61,   62,  289,  290,  291,  292,  266,  266,   42,
   43,  108,   45,  275,   47,  266,  274,  270,  281,  271,
  268,  266,   58,  274,  264,  122,   58,   60,   61,   62,
  264,  289,  290,  291,  292,   41,  268,  266,  289,  290,
  291,  292,  262,   59,  266,  274,   42,   43,   59,   45,
   59,   47,  274,   22,   59,  268,    7,  172,   18,  156,
  289,  290,  291,  292,   60,   61,   62,  289,  290,  291,
  292,  168,  266,   15,   59,  263,  264,  130,   -1,  266,
  274,  269,  270,   -1,  272,  273,   -1,  274,  276,  277,
   -1,   -1,   -1,   -1,   -1,  289,  290,  291,  292,   -1,
   -1,  266,  289,  290,  291,  292,   -1,   -1,  266,  274,
   -1,   -1,   -1,   -1,   -1,   -1,  274,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  289,  290,  291,  292,   -1,   -1,
   -1,  289,  290,  291,  292,   -1,  266,   41,   42,   43,
   44,   45,   -1,   47,  274,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   59,   60,   61,   62,  289,
  290,  291,  292,  286,  287,   -1,  289,  290,  291,  292,
   -1,   -1,   42,   43,   -1,   45,   -1,   47,  263,   -1,
   -1,   -1,  257,  258,  259,  260,  261,   -1,   -1,   93,
   60,   61,   62,   -1,  279,  280,  281,  282,  283,  284,
  285,   -1,   -1,  288,  279,  280,  281,  282,  283,  284,
  285,   -1,   -1,   -1,  274,   -1,   -1,   53,   -1,   55,
   56,   -1,   -1,   93,   -1,   -1,  286,  287,   -1,  289,
  290,  291,  292,  266,   -1,   -1,   -1,   73,   74,   -1,
   -1,   -1,   78,   79,   80,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  286,  287,   -1,  289,  290,  291,  292,
   96,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  109,  110,  111,  112,  113,  114,  115,
  116,  117,  118,  119,  120,  121,   -1,   -1,   -1,   -1,
  286,  287,  128,  289,  290,  291,  292,  263,  264,   -1,
   -1,   -1,  268,  269,  270,   -1,  272,  273,  263,  264,
  276,  277,   -1,  268,  269,  270,   -1,  272,  273,   -1,
   -1,  276,  277,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  266,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  274,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  289,  290,  291,  292,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  286,  287,   -1,  289,
  290,  291,  292,
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
"stm : conditional_stat",
"stm : while_stat",
"stm : for_stat",
"stm : return_stat ';'",
"stm : function_invocation_stat ';'",
"expressions_stat : expressions_stat AND expressions_stat",
"expressions_stat : expressions_stat OR expressions_stat",
"expressions_stat : NOT expressions_stat",
"expressions_stat : expressions_stat NE expressions_stat",
"expressions_stat : expressions_stat GE expressions_stat",
"expressions_stat : expressions_stat LE expressions_stat",
"expressions_stat : expressions_stat '=' expressions_stat",
"expressions_stat : expressions_stat '>' expressions_stat",
"expressions_stat : expressions_stat '<' expressions_stat",
"expressions_stat : expressions_stat '/' expressions_stat",
"expressions_stat : expressions_stat MOD expressions_stat",
"expressions_stat : expressions_stat '*' expressions_stat",
"expressions_stat : expressions_stat '-' expressions_stat",
"expressions_stat : expressions_stat '+' expressions_stat",
"expressions_stat : '-' expressions_stat",
"expressions_stat : '(' expressions_stat ')'",
"expressions_stat : constant",
"expressions_stat : ID",
"expressions_stat : function_invocation_stat",
"expressions_stat : variable_reference",
"simple_stat : variable_reference ASSIGN expressions_stat",
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
#line 161 "parser.y"

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
#line 519 "y.tab.c"

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
