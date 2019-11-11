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
   15,   15,   16,   16,   17,   17,   18,   18,   18,   18,
   18,   18,   18,   19,   19,   19,   19,   25,   27,   27,
   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,
   26,   26,   26,   26,   26,   26,   26,   20,   28,   28,
   21,   22,   23,   24,   29,   29,   29,   14,   14,   30,
   30,    8,    8,    8,    8,   31,   31,
};
static const short yylen[] = {                            2,
    5,    3,    0,    1,    2,    1,    5,   10,    5,    0,
    1,    3,    1,    1,    1,    1,    1,    1,    1,    1,
    6,    1,    0,    1,    2,    1,   10,    8,    3,    0,
    1,    1,    0,    1,    2,    1,    2,    2,    2,    2,
    2,    2,    2,    3,    2,    2,    2,    2,    0,    4,
    3,    3,    2,    3,    3,    3,    3,    3,    3,    3,
    3,    2,    3,    1,    1,    1,    1,    7,    0,    2,
    6,   10,    2,    4,    0,    1,    3,    0,    1,    5,
    3,    1,    1,    1,    1,    1,    1,
};
static const short yydefred[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    6,   13,    0,
    0,    0,    0,    0,    0,   26,    5,    0,    0,    1,
    0,    0,    2,   25,    0,   82,   83,   84,   85,   14,
   15,   16,   17,   18,   19,   20,    0,    0,   12,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   31,
    0,    0,   32,    0,   36,    0,    0,    0,    0,    0,
    0,    0,    0,    7,    9,    0,    0,    0,    0,    0,
   48,    0,    0,    0,    0,    0,   64,   66,    0,   67,
    0,   45,    0,    0,   47,    0,    0,   37,   29,   35,
   38,   39,   40,   41,   42,   43,    0,    0,   81,    0,
    0,    0,    0,    0,    0,    0,   53,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   74,    0,    0,
   63,    0,   51,   52,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   80,    0,   50,    0,
    0,    0,    0,    0,   22,    0,   28,    0,    0,   70,
    0,   71,    0,    8,    0,    0,   68,    0,   27,    0,
    0,    0,    0,   72,   21,
};
static const short yydgoto[] = {                          2,
    5,    6,   14,   51,    7,    8,   10,  155,  156,   77,
   11,   15,   16,   41,   52,   53,   54,   55,   56,   57,
   58,   59,   60,   78,   62,   79,   80,  152,  104,   42,
    0,
};
static const short yysindex[] = {                      -222,
  -11,    0, -228, -208, -203, -193, -228,    0,    0,   18,
   41, -176,   63, -158, -193,    0,    0,  311, -166,    0,
 -208,  210,    0,    0, -164,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   72,   76,    0,   84,
  108,  112,  -35, -102,  243,  269,  -91,  243,  243,    0,
  129,  -94,    0,  228,    0,  118,  120,  122,  123,  125,
  132,  -68,  -79,    0,    0,   39,  -31, -208,  243,  243,
    0,  -64,  161,  243,  243,  243,    0,    0,  115,    0,
  -35,    0,  157,  114,    0,  157,  133,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  243,  -78,    0, -158,
   39,  152,  157,  -20,  143,  -73,    0, -172,  -12,  228,
  243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
  228,  157,  -59,  -53,  160,   39,  243,    0,  114,  -55,
    0,  -51,    0,    0, -172, -172, -172, -172, -172, -172,
 -172, -172,  -44, -167,  -37, -158,    0,  157,    0,  -52,
  228,  -40,  -32,  -50,    0,  178,    0,  -30,  -25,    0,
  -28,    0,  -21,    0,  -19,  228,    0,  -38,    0,    4,
   10,   16, -167,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0, -130,  231,    0,   26, -206,    0,    0,    0,
  244,    0,    0,    0,   43,    0,    0,    0,    0,    0,
   -7,   33,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  264,   44,    0,  164,  171,    0,  171,  224,    0,
    0,    0,    0, -123,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  231,   85,  180,
    0,    0,  -34,  -27,  -27,  105,    0,    0,    0,    0,
  150,    0,  249,  251,    0,  253,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  171,    0,    0,    0,
    0,    0,   19,    0,    0,    0,    0,   -5,    0, -114,
  -27,  -27,  -27,  -27,  -27,  -27,  -27,  -27,  -27,  -27,
   45,  256,    0,    0,    0,    0,   85,    0,  -41,    0,
    0,   48,    0,    0,    2,   30,   37,   57,   66,   77,
   96,  124,    0,    0,    0,    0,    0,   42,    0,    0,
   45,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   45,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
static const short yygindex[] = {                         0,
    0,  295,    0,    5,    0,  317,    1,  169,  145,  307,
    0,    0,  315,    0,    0,  -98,    0,  279,    0,    0,
    0,    0,    0,  423,  117,  489,  -17,    0,    0,    0,
    0,
};
#define YYTABLESIZE 616
static const short yytable[] = {                         49,
   49,   49,   49,   49,   69,   49,   65,   65,   65,   65,
   65,  132,   65,   49,   49,   49,   49,   49,   23,   49,
  128,   40,  143,  127,   65,   71,  101,  100,  131,  115,
  113,   49,  114,   78,  116,   62,   62,   62,   62,   62,
    1,   62,   58,   58,   58,   58,   58,    3,   58,    4,
   10,   49,  160,   62,    9,   70,    4,    4,   65,   76,
   58,    4,   76,   71,   12,   49,   71,  170,  102,   13,
   57,   57,   57,   57,   57,   18,   57,   56,   56,   56,
   56,   56,   77,   56,   19,   77,   20,   62,   57,  154,
   26,   27,   28,   29,   58,   56,   39,   54,   54,   54,
   54,   54,   21,   54,  124,   22,   61,   61,   61,   61,
   61,  149,   61,  111,  112,   54,   63,   60,   60,   60,
   60,   60,   57,   60,   61,   49,   49,   49,   49,   56,
   64,   49,    3,    3,   65,   60,   59,   59,   59,   59,
   59,   66,   59,   34,   34,   49,   49,   49,   67,   54,
  158,   49,   33,   33,   59,   68,  115,  113,   61,  114,
   72,  116,   82,   85,   55,   55,   55,   55,   55,   60,
   55,   84,   88,   89,  115,  113,   91,  114,   92,  116,
   93,   94,   55,   95,  115,  113,   37,  114,   59,  116,
   96,   65,   65,   97,   65,   98,   65,  106,  115,  113,
   69,  114,  123,  116,   70,   49,   49,  130,   49,  126,
   49,  144,   49,   49,  145,  151,   55,   49,  146,  150,
   49,   49,   49,  153,   49,  157,   49,  161,  159,   49,
  163,   65,   49,  162,   99,  129,  164,  165,   49,   65,
  166,  167,  171,  169,   49,   49,   49,   49,   49,   49,
   49,   65,   65,  168,   65,   65,   65,   65,   49,   49,
   62,   49,   49,   49,   49,   49,   49,   58,   62,  125,
   49,  172,   49,  111,  112,   58,  117,  118,  119,  120,
  173,  174,   76,   62,   62,   62,   62,   75,   10,   23,
   58,   58,   58,   58,  147,   57,   26,   27,   28,   29,
    3,   11,   56,   57,   79,   49,   24,   46,   76,   49,
   56,   73,   33,   75,   44,   69,   50,  175,   57,   57,
   57,   57,   54,   17,   38,   56,   56,   56,   56,   24,
   54,   61,   90,   70,    0,    0,    0,    0,    0,   61,
    0,    0,   60,    0,    0,   54,   54,   54,   54,    0,
   60,    0,    0,    0,   61,   61,   61,   61,    0,   70,
    0,   59,    0,    0,    0,   60,   60,   60,   60,   59,
   49,   49,    0,   49,   49,   49,   49,    0,    0,    0,
    0,    0,    0,    0,   59,   59,   59,   59,  110,   55,
   49,   49,    0,   49,   49,   49,   49,   55,  121,    0,
  111,  112,    0,  117,  118,  119,  120,    0,    0,    0,
    0,    0,   55,   55,   55,   55,    0,    0,  111,  112,
    0,  117,  118,  119,  120,    0,    0,    0,  111,  112,
    0,  117,  118,  119,  120,   65,   65,   49,   65,   65,
   65,   65,  111,  112,   61,  117,  118,  119,  120,   49,
   49,    0,   49,   49,   49,   49,   49,   49,    0,   49,
   49,   49,   49,    0,    0,   49,   49,    0,   49,   49,
   49,   49,   43,   22,    0,    0,   61,    0,   44,   45,
    0,   46,   47,    0,    0,   48,   49,    4,    0,   49,
   43,   22,    0,    0,    0,    0,   44,   45,    0,   46,
   47,    0,    0,   48,   49,   73,    0,    0,    0,   49,
   49,    0,   49,   49,   49,   49,    0,    0,    0,    0,
    0,   30,   31,   32,   33,   34,   35,   36,    0,    0,
   74,   81,   61,    0,   83,    0,   86,   87,    0,    0,
    0,    0,    0,   61,    0,    0,    0,   30,   31,   32,
   33,   34,   35,   36,    0,    0,   74,  103,  105,    0,
    0,    0,  107,  108,  109,    0,    0,   25,   26,   27,
   28,   29,    0,   61,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  122,    0,    0,   61,   30,
   31,   32,   33,   34,   35,   36,    0,    0,    0,  133,
  134,  135,  136,  137,  138,  139,  140,  141,  142,    0,
    0,    0,    0,    0,    0,  148,
};
static const short yycheck[] = {                         41,
   42,   43,   44,   45,   40,   47,   41,   42,   43,   44,
   45,  110,   47,   41,   42,   43,   44,   59,   14,   47,
   41,   21,  121,   44,   59,   43,   58,   59,   41,   42,
   43,   59,   45,   41,   47,   41,   42,   43,   44,   45,
  263,   47,   41,   42,   43,   44,   45,   59,   47,  278,
   58,   93,  151,   59,  263,   91,  263,  264,   93,   41,
   59,  268,   44,   81,  268,   93,   84,  166,   68,  263,
   41,   42,   43,   44,   45,   58,   47,   41,   42,   43,
   44,   45,   41,   47,   44,   44,  263,   93,   59,  257,
  258,  259,  260,  261,   93,   59,  263,   41,   42,   43,
   44,   45,   40,   47,  100,  264,   41,   42,   43,   44,
   45,  129,   47,  286,  287,   59,  281,   41,   42,   43,
   44,   45,   93,   47,   59,   41,   42,   43,   44,   93,
   59,   47,  263,  264,   59,   59,   41,   42,   43,   44,
   45,   58,   47,  267,  268,   41,   42,   43,   41,   93,
  146,   47,  267,  268,   59,   44,   42,   43,   93,   45,
  263,   47,   46,   47,   41,   42,   43,   44,   45,   93,
   47,  263,   44,  268,   42,   43,   59,   45,   59,   47,
   59,   59,   59,   59,   42,   43,   18,   45,   93,   47,
   59,   42,   43,  262,   45,  275,   47,  262,   42,   43,
   40,   45,  281,   47,   91,   42,   43,  281,   59,   58,
   47,  271,   42,   43,  268,  267,   93,   47,   59,  275,
  262,   42,   43,  268,  266,  263,   47,  268,  281,   59,
  281,  266,  274,  266,   66,   93,   59,  268,  266,  274,
  266,  270,  281,  263,  286,  287,  274,  289,  290,  291,
  292,  286,  287,  275,  289,  290,  291,  292,  286,  287,
  266,  289,  290,  291,  292,   42,   43,  266,  274,  101,
   47,  268,   93,  286,  287,  274,  289,  290,  291,  292,
  271,  266,   40,  289,  290,  291,  292,   45,   58,  264,
  289,  290,  291,  292,  126,  266,  258,  259,  260,  261,
  268,   58,  266,  274,   41,  262,  264,   59,   40,   59,
  274,   59,  268,   45,   59,  268,   22,  173,  289,  290,
  291,  292,  266,    7,   18,  289,  290,  291,  292,   15,
  274,  266,   54,   91,   -1,   -1,   -1,   -1,   -1,  274,
   -1,   -1,  266,   -1,   -1,  289,  290,  291,  292,   -1,
  274,   -1,   -1,   -1,  289,  290,  291,  292,   -1,   91,
   -1,  266,   -1,   -1,   -1,  289,  290,  291,  292,  274,
  286,  287,   -1,  289,  290,  291,  292,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  289,  290,  291,  292,  274,  266,
  286,  287,   -1,  289,  290,  291,  292,  274,  266,   -1,
  286,  287,   -1,  289,  290,  291,  292,   -1,   -1,   -1,
   -1,   -1,  289,  290,  291,  292,   -1,   -1,  286,  287,
   -1,  289,  290,  291,  292,   -1,   -1,   -1,  286,  287,
   -1,  289,  290,  291,  292,  286,  287,  274,  289,  290,
  291,  292,  286,  287,   22,  289,  290,  291,  292,  286,
  287,   -1,  289,  290,  291,  292,  286,  287,   -1,  289,
  290,  291,  292,   -1,   -1,  286,  287,   -1,  289,  290,
  291,  292,  263,  264,   -1,   -1,   54,   -1,  269,  270,
   -1,  272,  273,   -1,   -1,  276,  277,  278,   -1,  266,
  263,  264,   -1,   -1,   -1,   -1,  269,  270,   -1,  272,
  273,   -1,   -1,  276,  277,  263,   -1,   -1,   -1,  286,
  287,   -1,  289,  290,  291,  292,   -1,   -1,   -1,   -1,
   -1,  279,  280,  281,  282,  283,  284,  285,   -1,   -1,
  288,  263,  110,   -1,   46,   -1,   48,   49,   -1,   -1,
   -1,   -1,   -1,  121,   -1,   -1,   -1,  279,  280,  281,
  282,  283,  284,  285,   -1,   -1,  288,   69,   70,   -1,
   -1,   -1,   74,   75,   76,   -1,   -1,  257,  258,  259,
  260,  261,   -1,  151,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   97,   -1,   -1,  166,  279,
  280,  281,  282,  283,  284,  285,   -1,   -1,   -1,  111,
  112,  113,  114,  115,  116,  117,  118,  119,  120,   -1,
   -1,   -1,   -1,   -1,   -1,  127,
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
"compound_stat : BGN compound_body END",
"compound_body :",
"compound_body : var_dec",
"compound_body : statements",
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
"simple_stat : variable_reference ASSIGN expressions_stat",
"simple_stat : PRINT variable_reference",
"simple_stat : PRINT expressions_stat",
"simple_stat : READ variable_reference",
"variable_reference : ID array_reference",
"array_reference :",
"array_reference : '[' expressions_stat ']' array_reference",
"expressions_stat : expressions_stat AND expressions_stat",
"expressions_stat : expressions_stat OR expressions_stat",
"expressions_stat : NOT expressions_stat",
"expressions_stat : expressions_stat '/' expressions_stat",
"expressions_stat : expressions_stat MOD expressions_stat",
"expressions_stat : expressions_stat '*' expressions_stat",
"expressions_stat : expressions_stat '-' expressions_stat",
"expressions_stat : expressions_stat '+' expressions_stat",
"expressions_stat : expressions_stat NE expressions_stat",
"expressions_stat : expressions_stat GE expressions_stat",
"expressions_stat : expressions_stat LE expressions_stat",
"expressions_stat : '-' expressions_stat",
"expressions_stat : '(' expressions_stat ')'",
"expressions_stat : constant",
"expressions_stat : ID",
"expressions_stat : function_invocation_stat",
"expressions_stat : array_reference",
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
"BOOLEAN_VALUE : TRUE",
"BOOLEAN_VALUE : FALSE",

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
#line 160 "parser.y"

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
#line 506 "y.tab.c"

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
