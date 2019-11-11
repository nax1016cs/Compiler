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
#define mod 292
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    1,    2,    2,    5,    5,    6,    6,    6,    7,
    7,   11,   11,   10,   10,   10,   10,   10,   10,   10,
    9,    9,    3,    3,   12,   12,   13,   13,    4,   15,
   15,   15,   16,   16,   17,   17,   18,   18,   18,   18,
   18,   18,   18,   19,   19,   19,   19,   25,   27,   27,
   26,   26,   28,   28,   28,   28,   20,   29,   29,   21,
   22,   23,   24,   30,   30,   30,   14,   14,   31,   31,
    8,    8,    8,    8,   32,   32,
};
static const short yylen[] = {                            2,
    5,    3,    0,    1,    2,    1,    5,   10,    5,    0,
    1,    3,    1,    1,    1,    1,    1,    1,    1,    1,
    6,    1,    0,    1,    2,    1,   10,    8,    3,    0,
    1,    1,    0,    1,    2,    1,    2,    2,    2,    2,
    2,    2,    2,    3,    2,    2,    2,    2,    0,    4,
    2,    0,    1,    1,    1,    2,    7,    0,    2,    6,
   10,    2,    4,    0,    1,    3,    0,    1,    5,    3,
    1,    1,    1,    1,    1,    1,
};
static const short yydefred[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    6,   13,    0,
    0,    0,    0,    0,    0,   26,    5,    0,    0,    1,
    0,    0,    2,   25,    0,   71,   72,   73,   74,   14,
   15,   16,   17,   18,   19,   20,    0,    0,   12,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   31,
    0,    0,   32,    0,   36,    0,    0,    0,    0,    0,
    0,    0,    0,    7,    9,    0,    0,    0,    0,    0,
   48,    0,    0,    0,    0,   45,   46,   47,   62,    0,
   37,   29,   35,   38,   39,   40,   41,   42,   43,    0,
    0,   70,    0,    0,    0,   65,    0,    0,    0,    0,
   53,   55,   51,    0,    0,   44,    0,    0,    0,    0,
    0,   63,    0,    0,   56,    0,    0,    0,    0,    0,
   69,   66,   50,    0,    0,    0,    0,    0,   22,    0,
   28,    0,    0,   59,    0,   60,    0,    8,    0,    0,
   57,    0,   27,    0,    0,    0,    0,   61,   21,
};
static const short yydgoto[] = {                          2,
    5,    6,   14,   51,    7,    8,   10,  129,  130,   38,
   11,   15,   16,   41,   52,   53,   54,   55,   56,   57,
   58,   59,   60,   61,   62,   74,   71,  103,  126,   97,
   42,    0,
};
static const short yysindex[] = {                      -243,
  -14,    0, -207, -180, -177, -178, -207,    0,    0,   30,
   48, -164,   60, -163, -178,    0,    0, -219, -159,    0,
 -180, -183,    0,    0, -174,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   49,   53,    0,   55,
   73,   71,  -32, -147,   72,  -43, -145,   72,   72,    0,
   75, -148,    0, -167,    0,   62,   63,   64,   65,   66,
   67, -135, -146,    0,    0, -224,  -30, -180,   72,   72,
    0, -134, -206, -144,   40,    0,    0,    0,    0, -133,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   72,
 -149,    0, -163, -224,   76,    0,    2,   42, -143,  -32,
    0,    0,    0, -167, -167,    0, -132, -131,   77, -224,
   72,    0,   40, -130,    0, -127, -126, -235, -122, -163,
    0,    0,    0, -138, -167, -124, -120, -129,    0,   88,
    0, -119, -118,    0, -117,    0, -125,    0, -112, -167,
    0, -123,    0, -114, -116, -110, -235,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0, -214,   99,    0, -105, -247,    0,    0,    0,
  102,    0,    0,    0, -103,    0,    0,    0,    0,    0,
  -26, -106,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  122,  -98,    0, -109,  107,    0,  107,  -99,    0,
    0,    0,    0, -212,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   99,    3,   78,
    0,    0,    0,    0,  109,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  107,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -40,
    0,    0,    0, -200,  -96,    0,    0,    0,    0,    0,
    3,    0,  -41,    0,    0,  -95,    0,    0,    0,    0,
    0,    0,    0,    0,  -96,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -96,
    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
static const short yygindex[] = {                         0,
    0,  147,    0,   -9,    0,  163,  -10,  -12,   27,  103,
    0,    0,  160,    0,    0,  -92,    0,  123,    0,    0,
    0,    0,    0,  105,   23,  -39,  -86,    0,    0,    0,
    0,    0,
};
#define YYTABLESIZE 234
static const short yytable[] = {                         49,
   49,   73,   49,   49,   23,   37,   77,   69,   79,   80,
   40,  116,  117,  115,   67,    4,    4,   49,   49,    1,
    4,  128,   26,   27,   28,   29,  123,   94,   93,   96,
   98,   10,  134,   26,   27,   28,   29,   25,   26,   27,
   28,   29,  112,   52,    3,  111,   52,  144,    3,    3,
  106,   49,   49,   92,   34,   34,  100,   95,   70,   30,
   31,   32,   33,   34,   35,   36,   33,   33,   76,   78,
    4,  122,   30,   31,   32,   33,   34,   35,   36,   43,
   22,  109,    9,  108,   13,   44,   45,   18,   46,   47,
   12,   19,   48,   49,    4,   43,   22,  121,   20,   21,
   22,   44,   45,   39,   46,   47,   63,   64,   48,   49,
  132,   65,   66,   67,   68,   72,   73,   75,   81,   82,
   84,   85,   86,   87,   88,   89,   90,   99,   91,  104,
   70,  107,  105,  110,  113,  120,  119,  114,  118,  125,
  131,  127,  133,  135,  124,  136,  138,  140,  139,  142,
  143,  137,  141,  146,  147,  148,   10,  145,   23,   11,
   24,    3,   68,   49,   52,   52,   52,   49,   50,   17,
   52,   33,   58,  149,   24,  101,   83,  102,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   75,
   49,    0,    0,    0,   49,   49,    0,    0,    0,    0,
    0,    0,   49,   49,
};
static const short yycheck[] = {                         41,
   41,   45,   44,   44,   14,   18,   46,   40,   48,   49,
   21,  104,  105,  100,   41,  263,  264,   59,   59,  263,
  268,  257,  258,  259,  260,  261,  113,   58,   59,   69,
   70,   58,  125,  258,  259,  260,  261,  257,  258,  259,
  260,  261,   41,   41,   59,   44,   44,  140,  263,  264,
   90,   93,   93,   66,  267,  268,  263,   68,   91,  279,
  280,  281,  282,  283,  284,  285,  267,  268,   46,   47,
  278,  111,  279,  280,  281,  282,  283,  284,  285,  263,
  264,   94,  263,   93,  263,  269,  270,   58,  272,  273,
  268,   44,  276,  277,  278,  263,  264,  110,  263,   40,
  264,  269,  270,  263,  272,  273,  281,   59,  276,  277,
  120,   59,   58,   41,   44,  263,   45,  263,   44,  268,
   59,   59,   59,   59,   59,   59,  262,  262,  275,  274,
   91,  281,  266,   58,   93,   59,  268,  281,  271,  267,
  263,  268,  281,  268,  275,  266,   59,  266,  268,  275,
  263,  281,  270,  268,  271,  266,   58,  281,  264,   58,
  264,  268,   41,  262,  274,   59,  266,   59,   22,    7,
   93,  268,  268,  147,   15,   73,   54,   73,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  263,
  262,   -1,   -1,   -1,  266,  266,   -1,   -1,   -1,   -1,
   -1,   -1,  274,  274,
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
"AND","OR","NOT","\"<=\"","\">=\"","\"<>\"","\"mod\"",
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
"expressions_stat : '-' expression_head",
"expressions_stat :",
"expression_head : constant",
"expression_head : ID",
"expression_head : function_invocation_stat",
"expression_head : ID array_reference",
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
#line 149 "parser.y"

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
#line 405 "y.tab.c"

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
