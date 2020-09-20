%{
#include <stdint.h>

#include "core/error.h"
#include "parser.h"

#define YY_USER_ACTION                                                         \
  yylloc.first_line = LineNum;                                                \
  yylloc.first_column = ColNum;                                               \
  ColNum += yyleng;

#define LIST                strCat(yytext)
#define TOKEN(t)            {LIST; if (OptTok) printf("<%s>\n", #t);}
#define TOKEN_CHAR(t)       {LIST; if (OptTok) printf("<%c>\n", (t));}
#define TOKEN_STRING(t, s)  {LIST; if (OptTok) printf("<%s: %s>\n", #t, (s));}
#define MAX_LINE_LENG       512

extern "C" int yylex();

uint32_t LineNum = 1;
uint32_t ColNum = 1;
char Buffer[MAX_LINE_LENG];

static int32_t OptSrc = 1;
static int32_t OptTok = 1;
int  OptSymbol = 1;
long long int count_line[1000] = {0};
long long int  count = 0;
static char StringLiteral[MAX_LINE_LENG];
static char *BufferPtr = Buffer;

static void strCat(const char *Text);

%}

integer 0|[1-9][0-9]*
float {integer}\.(0|[0-9]*[1-9])

%x CCOMMENT

%%
    /* Delimiter */
"," { TOKEN_CHAR(','); count += strlen(yytext); return COMMA; }
";" { TOKEN_CHAR(';'); count += strlen(yytext); return SEMICOLON; }
":" { TOKEN_CHAR(':'); count += strlen(yytext); return COLON; }
"(" { TOKEN_CHAR('('); count += strlen(yytext); return L_PARENTHESIS; }
")" { TOKEN_CHAR(')'); count += strlen(yytext); return R_PARENTHESIS; }
"[" { TOKEN_CHAR('['); count += strlen(yytext); return L_BRACKET; }
"]" { TOKEN_CHAR(']'); count += strlen(yytext); return R_BRACKET; }

    /* Operator */
"+"   { TOKEN_CHAR('+'); yylval.op_type=OP_PLUS;             count += strlen(yytext); return PLUS; }
"-"   { TOKEN_CHAR('-'); yylval.op_type=OP_MINUS;            count += strlen(yytext); return MINUS; }
"*"   { TOKEN_CHAR('*'); yylval.op_type=OP_MULTIPLY;         count += strlen(yytext); return MULTIPLY; }
"/"   { TOKEN_CHAR('/'); yylval.op_type=OP_DIVIDE;           count += strlen(yytext); return DIVIDE; }
"mod" { TOKEN(mod);      yylval.op_type=OP_MOD;              count += strlen(yytext); return MOD; }
":="  { TOKEN(:=);       yylval.op_type=OP_ASSIGN;           count += strlen(yytext); return ASSIGN; }
"<"   { TOKEN_CHAR('<'); yylval.op_type=OP_LESS;             count += strlen(yytext); return LESS; }
"<="  { TOKEN(<=);       yylval.op_type=OP_LESS_OR_EQUAL;    count += strlen(yytext); return LESS_OR_EQUAL; }
"<>"  { TOKEN(<>);       yylval.op_type=OP_NOT_EQUAL;        count += strlen(yytext); return NOT_EQUAL; }
">="  { TOKEN(>=);       yylval.op_type=OP_GREATER_OR_EQUAL; count += strlen(yytext); return GREATER_OR_EQUAL; }
">"   { TOKEN_CHAR('>'); yylval.op_type=OP_GREATER;          count += strlen(yytext); return GREATER; }
"="   { TOKEN_CHAR('='); yylval.op_type=OP_EQUAL;            count += strlen(yytext); return EQUAL; }
"and" { TOKEN(and);      yylval.op_type=OP_AND;              count += strlen(yytext); return AND; }
"or"  { TOKEN(or);       yylval.op_type=OP_OR;               count += strlen(yytext); return OR; }
"not" { TOKEN(not);      yylval.op_type=OP_NOT;              count += strlen(yytext); return NOT; }

    /* Keyword */
"array"   { TOKEN(KWarray);   count += strlen(yytext); return ARRAY; }
"begin"   { TOKEN(KWbegin);   count += strlen(yytext); return BEGIN_; }
"boolean" { TOKEN(KWboolean); count += strlen(yytext); return BOOLEAN; }
"def"     { TOKEN(KWdef);     count += strlen(yytext); return DEF; }
"do"      { TOKEN(KWdo);      count += strlen(yytext); return DO; }
"else"    { TOKEN(KWelse);    count += strlen(yytext); return ELSE; }
"end"     { TOKEN(KWend);     count += strlen(yytext); return END; }
"false"   { TOKEN(KWfalse);   count += strlen(yytext); return FALSE; }
"for"     { TOKEN(KWfor);     count += strlen(yytext); return FOR; }
"integer" { TOKEN(KWinteger); count += strlen(yytext); return INTEGER; }
"if"      { TOKEN(KWif);      count += strlen(yytext); return IF; }
"of"      { TOKEN(KWof);      count += strlen(yytext); return OF; }
"print"   { TOKEN(KWprint);   count += strlen(yytext); return PRINT; }
"read"    { TOKEN(KWread);    count += strlen(yytext); return READ; }
"real"    { TOKEN(KWreal);    count += strlen(yytext); return REAL; }
"string"  { TOKEN(KWstring);  count += strlen(yytext); return STRING; }
"then"    { TOKEN(KWthen);    count += strlen(yytext); return THEN; }
"to"      { TOKEN(KWto);      count += strlen(yytext); return TO; }
"true"    { TOKEN(KWtrue);    count += strlen(yytext); return TRUE; }
"return"  { TOKEN(KWreturn);  count += strlen(yytext); return RETURN; }
"var"     { TOKEN(KWvar);     count += strlen(yytext); return VAR; }
"while"   { TOKEN(KWwhile);   count += strlen(yytext); return WHILE; }

    /* Identifier */
[a-zA-Z][a-zA-Z0-9]* { TOKEN_STRING(id, yytext); yylval.text = strdup(yytext); count += strlen(yytext); return ID; }

    /* Integer (decimal/octal) */
{integer} { TOKEN_STRING(integer, yytext);     yylval.val = atoi(yytext); count += strlen(yytext); return INT_LITERAL; }
0[0-7]+   { TOKEN_STRING(oct_integer, yytext); yylval.val = strtol(yytext, NULL, 8); count += strlen(yytext); return INT_LITERAL; }

    /* Floating-Point */
{float} { TOKEN_STRING(float, yytext); yylval.dval = atof(yytext); count += strlen(yytext); return REAL_LITERAL; }

    /* Scientific Notation [Ee][+-]?[0-9]+ */
({integer}|{float})[Ee][+-]?({integer}) {
    TOKEN_STRING(scientific, yytext);
    yylval.dval = atof(yytext);
    count += strlen(yytext); 
    return REAL_LITERAL;
}

    /* String */
\"([^"\n]|\"\")*\" {
    char *YytextPtr = yytext;
    char *StrPtr = StringLiteral;

    /* Condition guard of the end of string literal
       Check only when *YytextPtr == '"' */
    while (*(YytextPtr + 1) != '\0') {
        ++YytextPtr;

        /* Handle the situation of double quotes */
        if (*YytextPtr == '"' && *(YytextPtr + 1) != '\0')
            *StrPtr++ = *YytextPtr++;

        while (*YytextPtr != '"')
            *StrPtr++ = *YytextPtr++;
    }
    *StrPtr = '\0';
    TOKEN_STRING(string, StringLiteral);
    yylval.text = strdup(yytext);
    count += strlen(yytext); 
    return STRING_LITERAL;
}
    /* Whitespace */
[ \t]+ { LIST; count += strlen(yytext); }

    /* Pseudocomment */
"//&"[STD][+-].* {
    count += strlen(yytext); 
    LIST;
    char option = yytext[3];
    switch (option) {
    case 'S':
        OptSrc = (yytext[4] == '+') ? 1 : 0;
        break;
    case 'T':
        OptTok = (yytext[4] == '+') ? 1 : 0;
        break;
    case 'D':
        OptSymbol = (yytext[4] == '+') ? 1 : 0;
        break;
    }

}

    /* C++ Style Comment */
"//".* { LIST; count += strlen(yytext); }

    /* C Style Comment */
"/*"           { LIST; BEGIN(CCOMMENT); count += strlen(yytext); }
<CCOMMENT>"*/" { LIST; BEGIN(INITIAL); count += strlen(yytext); }
<CCOMMENT>.    { LIST; count += strlen(yytext); }

    /* Newline */
<INITIAL,CCOMMENT>\n {
    count += 1;
    count_line[LineNum] = count;
    if (OptSrc)
        printf("%d: %s\n", LineNum, Buffer);
    ++LineNum;
    ColNum = 1;
    Buffer[0] = '\0';
    BufferPtr = Buffer;
}

    /* Catch the character which is not accepted by rules above */
. {
    printf("Error at line %d: bad character \"%s\"\n", LineNum, yytext);
    exit(-1);
}

%%

static void strCat(const char *Text) {
    while (*Text) {
        *BufferPtr++ = *Text++;
    }
    *BufferPtr = '\0';
}
