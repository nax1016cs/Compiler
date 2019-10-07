%{
#define LIST               		strcat(buf, yytext)
#define token(t)           		{LIST; if (Opt_T) printf("<%s>\n", #t);}
#define tokenChar(t)       		{LIST; if (Opt_T) printf("<%c>\n", (t));}
#define tokenInteger(t, i) 		{LIST; if (Opt_T) printf("<%s: %d>\n", #t, (i));}
#define tokenOct(t, i) 			{LIST; if (Opt_T) printf("<%s: 00%d>\n", #t, (i));}
#define tokenString(t, s)  		{LIST; if (Opt_T) printf("<%s: %s>\n", #t, (s));}
#define tokenScientific(t, s)   {LIST; if (Opt_T) printf("<%s: %s>\n", #t, (s));}
#define tokenFloat(t,ts)        {LIST; if (Opt_T) printf("<%s: %s>\n", #t, (ts));}
// Define your token macros here
//  for example :
//    #define tokenScientific(t, s)   <definition>
//    #define tokenFloat(ts)          <definition>
//    #define <any other macros you needed>
// 	0.0
#define MAX_LINE_LENG      256

int Opt_S = 1;
int Opt_T = 1;
int linenum = 1;
char buf[MAX_LINE_LENG];
%}


digit 			[0-9]
letter 			[a-zA-Z]
oct_num			[+-]?[0][0]([1-9][0-9]*)?	
floating		[+-]?(0|[1-9][0-9]*)[.][0]*[1-9]+[0-9]*	 | [+-]?[0][0][1-9][0-9]*[.][0]*[1-9]+[0-9]*	
scientific 		([+-]?([1-9][0-9]*)[.][0]*[1-9]+[0-9]*[E][+-]?(0|[1-9][0-9]*))
%%
"("     { tokenChar('('); }
")"		{ tokenChar(')'); }
";"		{ tokenChar(';'); }
":"		{ tokenChar(':'); }
","		{ tokenChar(','); }
"["		{ tokenChar('['); }
"]"		{ tokenChar(']'); }
"+"		{ tokenChar('+'); }
"-"		{ tokenChar('-'); }
"*"		{ tokenChar('*'); }
"/"		{ tokenChar('/'); }
"="		{ tokenChar('='); }
">"		{ tokenChar('>'); }
"<"		{ tokenChar('<'); }

"mod"	{token(mod);}
":="	{token(:=); }
"<="	{token(<=); }
">="	{token(>=); }
"<>"	{token(<>); }
"and"	{token(and);}
"or"	{token(or); }
"not"	{token(not);}

"array" 	{ token(KWarray); }
"begin" 	{ token(KWbegin); }
"boolean" 	{ token(KWboolean); }
"def" 		{ token(KWdef); }
"do"		{ token(KWdo); }
"else" 		{ token(KWelse); }
"end" 		{ token(KWend); }
"false" 	{ token(KWfalse); }
"for" 		{ token(KWfor); }
"integer" 	{ token(KWinteger); }
"if" 		{ token(KWif); }
"of" 		{ token(KWof); }
"print" 	{ token(KWprint); }
"read" 		{ token(KWread); }
"real" 		{ token(KWreal); }
"string" 	{ token(KWstring); }
"then" 		{ token(KWthen); }
"to" 		{ token(KWto); }
"true" 		{ token(KWtrue); }
"return" 	{ token(KWreturn); }
"var" 		{ token(KWvar); }
"while" 	{ token(KWwhile); }


{scientific} 									{tokenString(scientific,yytext);}
([+-]?[1-9][0-9]*[E][+-]?(0|[1-9][0-9]*)) 		{tokenString(scientific,yytext);}
[+-]?(0|[1-9][0-9]*)[.][0]*[1-9][0-9]*			{tokenFloat(float,yytext);}
[+-]?[0][0][1-9][0-9]*[.][0]*[1-9][0-9]*		{
													printf("123456");
													int num_pos = 0;															char oc[256];
													oc[0] = '\0';
													char ft[256];
													ft[0]='\0';
													int i;
													for(i=0; i<yyleng; i++){
														if(yytext[i]=='.'){
															num_pos = i;
															break;
														}
														oc[i] = yytext[i];
													}
													oc[i-1] = '\0';
													int s=0;
													for(int j=i-1; j<yyleng; j++){															ft[s++] = yytext[j];
														ft[s++] = yytext[j];
													}
													ft[s]='\0';
													printf("123456789");
													tokenOct(oct_integer,atoi(oc));
													tokenFloat(float,s);
												}
{oct_num}											{tokenOct(oct_integer,atoi(yytext));}															 
[+-]?(0|[1-9][0-9]*)								{tokenInteger(integer,atoi(yytext));}
{letter}({letter}|{digit})* 						{tokenString(id,yytext);} 
\"(\\.|[^\\])*\"									{
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
[ \t] 												{LIST;}

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