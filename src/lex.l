%{
#define LIST                  strcat(buf, yytext)
#define token(t)              {LIST; if (Opt_T) printf("<%s>\n", #t);}
#define tokenChar(t)          {LIST; if (Opt_T) printf("<%c>\n", (t));}
#define tokenInteger(t, i)    {LIST; if (Opt_T) printf("<%s: %s>\n", #t, (i));}
#define tokenOct(t, i)      {LIST; if (Opt_T) printf("<%s: %s>\n", #t, (i));}
#define tokenString(t, s)     {LIST; if (Opt_T) printf("<%s: %s>\n", #t, (s));}
#define tokenScientific(t, s)   {LIST; if (Opt_T) printf("<%s: %s>\n", #t, (s));}
#define tokenFloat(t,ts)        {LIST; if (Opt_T) printf("<%s: %s>\n", #t, (ts));}
#define tokenFloat_NL(t,ts)        { if (Opt_T) printf("<%s: %s>\n", #t, (ts));}
// Define your token macros here
//  for example :
//    #define tokenScientific(t, s)   <definition>
//    #define tokenFloat(ts)          <definition>
//    #define <any other macros you needed>
//  0.0
#define MAX_LINE_LENG      256

int Opt_S = 1;
int Opt_T = 1;
int linenum = 1;
char buf[MAX_LINE_LENG];
%}


digit       [0-9]
letter      [a-zA-Z]
int         (0|[1-9][0-9]*)
oct         [0][0-7]+
floating    {int}[.][0-9]*
scientific_float    ([1-9][0-9]*)[.][0]*[1-9]+[0-9]*[Ee][+-]?{int}
scientific_int       [1-9][0-9]*[Ee][+-]?{int}
%Start COMMENT

%%

<INITIAL>"/*".*    {LIST;BEGIN COMMENT;}
<COMMENT>.         {LIST;}
<COMMENT>.*"*/"    {LIST;BEGIN INITIAL;}
<INITIAL>"//&S+".* {Opt_S=1;LIST;}
<INITIAL>"//&S-".* {Opt_S=0;LIST;}
<INITIAL>"//&T+".* {Opt_T=1;LIST;}
<INITIAL>"//&T-".* {Opt_T=0;LIST;}
<INITIAL>"//".* {LIST;}

<INITIAL>"("    { tokenChar('('); }
<INITIAL>")"    { tokenChar(')'); }
<INITIAL>";"    { tokenChar(';'); }
<INITIAL>":"    { tokenChar(':'); }
<INITIAL>","    { tokenChar(','); }
<INITIAL>"["    { tokenChar('['); }
<INITIAL>"]"    { tokenChar(']'); }
<INITIAL>"+"    { tokenChar('+'); }
<INITIAL>"-"    { tokenChar('-'); }
<INITIAL>"*"    { tokenChar('*'); }
<INITIAL>"/"    { tokenChar('/'); }
<INITIAL>"="    { tokenChar('='); }
<INITIAL>">"    { tokenChar('>'); }
<INITIAL>"<"    { tokenChar('<'); }

<INITIAL>"mod"  {token(mod);}
<INITIAL>":="   {token(:=); }
<INITIAL>"<="   {token(<=); }
<INITIAL>">="   {token(>=); }
<INITIAL>"<>"   {token(<>); }
<INITIAL>"and"  {token(and);}
<INITIAL>"or"   {token(or); }
<INITIAL>"not"  {token(not);}

<INITIAL>"array"    { token(KWarray); }
<INITIAL>"begin"    { token(KWbegin); }
<INITIAL>"boolean"  { token(KWboolean); }
<INITIAL>"def"      { token(KWdef); }
<INITIAL>"do"       { token(KWdo); }
<INITIAL>"else"     { token(KWelse); }
<INITIAL>"end"      { token(KWend); }
<INITIAL>"false"    { token(KWfalse); }
<INITIAL>"for"      { token(KWfor); }
<INITIAL>"integer"  { token(KWinteger); }
<INITIAL>"if"       { token(KWif); }
<INITIAL>"of"       { token(KWof); }
<INITIAL>"print"    { token(KWprint); }
<INITIAL>"read"     { token(KWread); }
<INITIAL>"real"     { token(KWreal); }
<INITIAL>"string"   { token(KWstring); }
<INITIAL>"then"     { token(KWthen); }
<INITIAL>"to"       { token(KWto); }
<INITIAL>"true"     { token(KWtrue); }
<INITIAL>"return"   { token(KWreturn); }
<INITIAL>"var"      { token(KWvar); }
<INITIAL>"while"    { token(KWwhile); }



<INITIAL>{scientific_float}                   {tokenString(scientific,yytext);}
<INITIAL>{scientific_int}                     {tokenString(scientific,yytext);}
<INITIAL>{int}[.][0]*[1-9][0-9]*              {tokenFloat(float,yytext);}
<INITIAL>{oct}                                {tokenOct(oct_integer,yytext);}                              
<INITIAL>{int}                                {tokenInteger(integer,yytext);}
<INITIAL>{letter}({letter}|{digit})*          {tokenString(id,yytext);} 
<INITIAL>\"(\\.|[^\\])*\"                     {
                                                char str[256];
                                                str[0] = '\0';
                                                int count=0;
                                                for(int i=1; i<yyleng-1; i++){
                                                  if(yytext[i] == '"'){
                                                    i++;
                                                  }
                                                  str[count] = yytext[i];
                                                  count++;
                                                }
                                                str[count]='\0';
                                                tokenString(string,str);}
[ \t]                       {LIST;}

\n      {

          if (Opt_S)
            printf("%d: %s\n", linenum, buf);
          linenum++;
          buf[0] = '\0';
        }
.       {
          /* error */
          printf("Error at line %d: bad character \"%s\"\n", linenum, yytext );
          exit(-1);
        }
%%
int main( int argc, char **argv )
{
  if( argc != 2 ) {
    fprintf( stderr, "Usage: ./scanner [filename]\n" );
    exit(0);
  }
  
  FILE *fp = fopen( argv[1], "r" );
  if( fp == NULL ) {
    fprintf( stderr, "Open file error\n" );
    exit(-1);
  }
  
  yyin = fp;

  yylex();

  exit(0);
}