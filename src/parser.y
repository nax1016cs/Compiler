%{
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
%}

%token ARRAY BOOLEAN INTEGER REAL STRING 
%token ASSIGN ID BGN DEF DO ELSE END FOR IF OF PRINT READ THEN TO RETURN WHILE VAR
%token TRUE FALSE INT OCT FLOAT SCIENTIFIC STR
%token AND OR NOT 

%left '+' '-' '*' '/' '>' '<' '=' LE GE NE MOD
%left AND OR NOT
// %right NOT "=" 

%%

program:            ID ';' program_body END ID;


program_body :      var_dec func_dec compound_stat;


var_dec: 
                    | non_empty_var_dec;
                    

non_empty_var_dec:  non_empty_var_dec variable | variable;



variable         :VAR id_list ':' TYPE ';'
                |VAR id_list ':' ARRAY INT TO INT OF array_type ';'
                |VAR id_list ':' constant ';';
                

id_list:         
                |non_empty_id_list;
                


non_empty_id_list   :non_empty_id_list ',' ID
                    |ID;
                    

constant:       TRUE |FALSE |INT |OCT |FLOAT |SCIENTIFIC |STR;


array_type     :ARRAY INT TO INT OF array_type
                | TYPE;
                
func_dec: 
                    | non_empty_func_dec;
                    

non_empty_func_dec:  non_empty_func_dec function | function;


function    : ID  '('  arguments  ')'  ':'  TYPE  ';'  compound_stat  END  ID 
         | ID '(' arguments ')' ';' compound_stat END ID ;
         

compound_stat: BGN var_dec statements END;


statements:         
                |non_empty_statements;

non_empty_statements:  non_empty_statements stm
                        | stm;


stm:                compound_stat ','
                    |simple_stat ';'
                    | conditional_stat 
                    | while_stat 
                    | for_stat 
                    | return_stat ';'
                    | function_invocation_stat ';' ;


expressions_stat:   expressions_stat AND expressions_stat
                    | expressions_stat OR expressions_stat
                    | NOT expressions_stat
                    | expressions_stat NE expressions_stat
                    | expressions_stat GE expressions_stat
                    | expressions_stat LE expressions_stat
                    | expressions_stat '=' expressions_stat
                    | expressions_stat '>' expressions_stat
                    | expressions_stat '<' expressions_stat
                    | expressions_stat '/' expressions_stat
                    | expressions_stat MOD expressions_stat
                    | expressions_stat '*' expressions_stat
                    | expressions_stat '-' expressions_stat
                    | expressions_stat '+' expressions_stat


                    | '-' expressions_stat
                    | '(' expressions_stat ')'
                    | constant
                    | ID 
                    | function_invocation_stat
                    | variable_reference;


simple_stat:        variable_reference  ASSIGN expressions_stat 
                    //| PRINT variable_reference 
                    | PRINT expressions_stat 
                    | READ variable_reference ;

variable_reference: ID array_reference;

array_reference:    
                    |'[' expressions_stat ']' array_reference;


conditional_stat: IF expressions_stat THEN statements condition_body END IF;

condition_body: 
                | ELSE statements;

while_stat: WHILE expressions_stat DO statements END DO;

for_stat: FOR ID ASSIGN INT TO INT DO statements END DO;

return_stat: RETURN expressions_stat;

function_invocation_stat: ID '(' expression_list ')'

expression_list :
                    |expressions_stat
                    |expression_list ',' expressions_stat;
                    

arguments:          
                    | non_empty_arg;

non_empty_arg:      non_empty_arg ',' id_list ':' TYPE 
                    | id_list ':' TYPE;

TYPE : BOOLEAN 
       | INTEGER 
       | REAL 
       | STRING;
       




%%

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
