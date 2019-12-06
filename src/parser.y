%{

#include "include/AST/ast.hpp"
#include "include/AST/program.hpp"
#include "include/AST/declaration.hpp"
#include "include/AST/constant_value.hpp"
#include "include/AST/binary_operator.hpp"
#include "include/AST/expression.hpp"
#include "include/AST/function_call.hpp"
#include "include/AST/variable_reference.hpp"
#include "include/AST/unary_operator.hpp"
#include "include/AST/print.hpp"
#include "include/AST/assignment.hpp"
#include "include/AST/return.hpp"
#include "include/AST/statement.hpp"
#include "include/AST/while.hpp"
#include "include/AST/for.hpp"
#include "include/AST/compound_statement.hpp"
#include "include/AST/if.hpp"
#include "include/AST/else.hpp"
#include "include/AST/function.hpp"
#include "include/AST/program_body.hpp"



#include "include/core/error.h"
#include "include/visitor/dumpvisitor.hpp"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include <vector>

#define YYLTYPE yyltype

typedef struct YYLTYPE {
    uint32_t first_line;
    uint32_t first_column;
    uint32_t last_line;
    uint32_t last_column;
} yyltype;

/* Declared by scanner.l */
extern int32_t LineNum;
extern char Buffer[512];
/*create a vector for idlist*/

std::vector<VariableNode*> vector_of_var;
std::vector<ExpressionNode*> vector_of_exp; // for function
std::vector<ExpressionNode*> vector_of_exp_arr; // for arr
std::vector<std::string> vector_of_string ;


int tab = 0;
void print_tab(int tab){
    for(int i=0; i<tab*2; i++){
        std::cout<<" ";
    }
}

/* Declared by lex */
extern FILE *yyin;
extern char *yytext;

extern "C" int yylex(void);
extern "C" int yyparse();
static void yyerror(const char *msg);

UnaryOperatorNode* unary ;
BinaryOperatorNode* binary ;
PrintNode* print ;
ReadNode* read ;
AssignmentNode* assign ;
FunctionCallStatNode* fun_stat ;

DeclarationNode*        dec_temp ;
AssignmentNode*         ass_temp ;
VariableNode*           var_temp ;
VariableReferenceNode*  varf_temp ;
ExpressionNode*         exp_temp ;
ConstantValueNode*      con_temp ;



static ProgramNode *root;


%}

%locations
%code requires{ #include "AST/program.hpp" }
%code requires{ #include "AST/declaration.hpp"}
%code requires{ #include "AST/constant_value.hpp"}
%code requires{ #include "AST/variable.hpp"}
%code requires{ #include "AST/binary_operator.hpp"}
%code requires{ #include "AST/expression.hpp"}
%code requires{ #include "AST/function_call.hpp"}
%code requires{ #include "AST/variable_reference.hpp"}
%code requires{ #include "AST/unary_operator.hpp"}
%code requires{ #include "AST/print.hpp"}
%code requires{ #include "AST/assignment.hpp"}
%code requires{ #include "AST/return.hpp"}
%code requires{ #include "AST/statement.hpp"}
%code requires{ #include "AST/function_call_stat.hpp"}
%code requires{ #include "AST/while.hpp"}
%code requires{ #include "AST/for.hpp"}
%code requires{ #include "AST/compound_statement.hpp"}
%code requires{ #include "AST/if.hpp"}
%code requires{ #include "AST/else.hpp"}
%code requires{ #include "AST/function.hpp"}
%code requires{ #include "AST/program_body.hpp"}


    /* Delimiter */
%token COMMA SEMICOLON COLON
%token L_PARENTHESIS R_PARENTHESIS
%token L_BRACKET R_BRACKET

    /* Operator */
%token ASSIGN
%left OR
%left AND
%right NOT
%left LESS LESS_OR_EQUAL EQUAL GREATER GREATER_OR_EQUAL NOT_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%right UNARY_MINUS

    /* Keyword */
%token ARRAY BOOLEAN INTEGER REAL STRING
%token END BEGIN_ /* Use BEGIN_ since BEGIN is a keyword in lex */
%token DO ELSE FOR IF THEN WHILE
%token DEF OF TO RETURN VAR
%token FALSE TRUE
%token PRINT READ

    /* Identifier */
%token ID

    /* Literal */
%token INT_LITERAL
%token REAL_LITERAL
%token STRING_LITERAL

%union {
    char *str;
    ProgramNode*            program_type;
    DeclarationNode*        declaration_type;
    ConstantValueNode*      constant_type;
    VariableNode*           variable_type;
    BinaryOperatorNode*     bop_type;
    ExpressionNode* 		exp_type;
    FunctionCallNode*       function_call_type;
    VariableReferenceNode*  var_ref_type;
    ReturnNode*             return_type;
    StatementNode*          statement_type;
    WhileNode*              while_type;
    ForNode*                for_type;
    CompoundStatementNode*  cmp_type;
    IfNode*                 if_type;
    ElseNode*               else_type;
    std::vector<StatementNode*>* vector_stat_type; // for stat
    std::vector<ExpressionNode*>* vector_exp_type; // for stat
	std::vector<DeclarationNode*>* vector_of_dec_type;
	FunctionNode*           function_type;
    std::vector<FunctionNode*>* vector_of_fun_type;
    ProgramBodyNode*        program_body_type;


}
%type<program_type>         Program
%type<declaration_type>     Declaration
%type<constant_type>        LiteralConstant
%type<variable_type>        IdList
%type<exp_type>		        Expression
%type<function_call_type>   FunctionCall
%type<var_ref_type>         VariableReference
%type<exp_type>             ArrForm
%type<return_type>          Return
%type<statement_type>       FunctionInvokation
%type<statement_type>       Simple
%type<while_type>           While
%type<statement_type>       Statement
%type<for_type>             For
%type<cmp_type>             CompoundStatement
%type<if_type>              Condition
%type<else_type>            ElseOrNot
%type<vector_stat_type>     StatementList
%type<vector_exp_type>      ExpressionList
%type<vector_of_dec_type>   DeclarationList
%type<vector_stat_type>     Statements
%type<vector_exp_type>      Expressions
%type<vector_of_dec_type>   Declarations
%type<function_type>   		FunctionDeclaration
%type<vector_of_dec_type>   FormalArgs
%type<vector_of_dec_type>   FormalArgList
%type<declaration_type>     FormalArg
%type<vector_of_fun_type>   Functions
%type<vector_of_fun_type>   FunctionList
%type<program_body_type>    ProgramBody


%type<str> ProgramName
%type<str> INT_LITERAL
%type<str> REAL_LITERAL
%type<str> STRING_LITERAL
%type<str> TRUE
%type<str> FALSE
%type<str> ID
%type<str> Type
%type<str> ScalarType
%type<str> INTEGER
%type<str> REAL
%type<str> STRING
%type<str> BOOLEAN
%type<str> ArrType
%type<str> ArrDecl
%type<str> ReturnType
%type<str> FunctionName



%%
    /*
       Program Units
                     */

Program:
    ProgramName SEMICOLON ProgramBody END ProgramName {
        $$ = root = new ProgramNode(@1.first_line, @1.first_column);
        $$->p = $3;
        $$->name.assign($1);
    }
;

ProgramName:
    ID
;

ProgramBody:
    DeclarationList FunctionList CompoundStatement {$$ = new ProgramBodyNode(0,0);
                                                    $$->d = $1;
                                                    $$->f = $2;
                                                    $$->c = $3;
                                                        }
;

DeclarationList:
    Epsilon 		{$$ = NULL;}
    |
    Declarations    {$$ = $1;}
;

Declarations:
    Declaration              { $$ = new std::vector<DeclarationNode* >;$$->emplace_back($1); }
    |
    Declarations Declaration { $1->emplace_back($2); $$ = $1; }
;

FunctionList:
    Epsilon     {$$ = NULL;}
    |
    Functions   {$$ = $1;}
;

Functions:
    FunctionDeclaration           { $$ = new std::vector<FunctionNode* >;$$->emplace_back($1); }
    |
    Functions FunctionDeclaration { $1->emplace_back($2); $$ = $1; }
;

FunctionDeclaration:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType SEMICOLON
    CompoundStatement
    END FunctionName    {
    					 $$ = new FunctionNode(@1.first_line, @1.first_column,$7,$3);
    					 $$->name.assign($1);
    					 $$->type.assign($5); 
    					 $$->v_string =vector_of_string;
    					 vector_of_string.clear();}
;

FunctionName:
    ID
;

FormalArgList:
    Epsilon 			{vector_of_string.clear(); $$ = NULL; }
    |
    FormalArgs          {$$ = $1;}
;

FormalArgs:
    FormalArg                       {$$ = new std::vector<DeclarationNode* > ; $$->emplace_back($1);vector_of_var.clear();}
    |
    FormalArgs SEMICOLON FormalArg  {$1->emplace_back($3); $$ = $1;vector_of_var.clear();}
;

FormalArg:
    IdList COLON Type     { for(auto it: vector_of_var){
                			    it->type = $3 ;
                                std::string temp,result;
                                result.clear();
                                temp.clear();
                                temp.assign($3);
                                int get = 1;
                                for(unsigned int i=0; i<temp.size(); i++){
                                    if(get){
                                        result += temp[i];
                                    }
                                    if(i>0 &&  temp[i-1]=='['){
                                        get = 0;
                                    }
                                    if(temp[i+1]==']'){
                                        get = 1;
                                    }

                                }
            				    vector_of_string.push_back(result);
                                $$ = new DeclarationNode(@1.first_line, @1.first_column,vector_of_var,NULL);
        				}

   					 }
;

IdList:
    ID {
        $$ = new VariableNode(@1.first_line, @1.first_column,"");
        $$->name.assign($1);
        vector_of_var.emplace_back($$);
    }
    |
    IdList COMMA ID {
        $$ = new VariableNode(@3.first_line, @3.first_column,"");
        $$->name.assign($3);
        vector_of_var.emplace_back($$);
    }
;

ReturnType:
    COLON ScalarType { $$ = $2;}
    |
    Epsilon           {$$ = "";}
;


Declaration:
    VAR IdList COLON Type SEMICOLON{
    	for(auto it: vector_of_var){
            it->type = $4 ;
        }
        $$ = new DeclarationNode(@1.first_line, @1.first_column,vector_of_var,NULL);
		vector_of_var.clear();
	}
    |
    VAR IdList COLON LiteralConstant SEMICOLON{
        $$ = new DeclarationNode(@1.first_line, @1.first_column,vector_of_var,$4);
		vector_of_var.clear();
	}

;


Type:
    ScalarType {$$ = $1;}
    |
    ArrType     { $$ = $1;}
;

ScalarType:
    INTEGER  {$$ = $1;}
    |
    REAL  	 {$$ = $1;}
    |
    STRING   {$$ = $1;}
    |
    BOOLEAN  {$$ = $1;}
;

ArrType:
    ArrDecl ScalarType   {  $$ = new char [100];
                            std::string temp1, temp2, result;
                            result.clear();
                            temp1.clear();
                            temp2.clear();
                            temp1.assign($2);
                            temp2.assign($1);
                            result +=   temp1 + temp2;
                            for(unsigned int i=0; i<result.size(); i++){
                                $$[i] = result[i];
                            }
                         }
;

ArrDecl: 
    ARRAY INT_LITERAL TO INT_LITERAL OF {   
    										$$ = new char [100];
    										std::string temp1, temp2, result;
    										result.clear();
    										temp1.clear();
    										temp2.clear();
    										temp1.assign($2);
    										temp2.assign($4);
    										result += "[" + temp1 + "..." + temp2 + "]";
    										for( unsigned int i=0; i<result.size(); i++){
    											$$[i] = result[i];
    										}
    									}
    |
    ArrDecl ARRAY INT_LITERAL TO INT_LITERAL OF { 
    												$$ = new char [100];
    												std::string temp1, temp2,temp3, result;
    												result.clear();
    												temp1.clear();
    												temp2.clear();
    												temp3.clear();

    												temp1.assign($1);
    												temp2.assign($3);
    												temp3.assign($5);
    												result += temp1 +"[" + temp2 + "..." + temp3 + "]";
    												for(unsigned int i=0; i<result.size(); i++){
    													$$[i] = result[i];
    												}                                       
                                                }
;

LiteralConstant:
    INT_LITERAL         {$$ =  new ConstantValueNode(@1.first_line, @1.first_column, "integer"); 
                         if($1[0]!='0')$$->name.assign($1);
                         else{
                              int number = std::stoi($1, 0, 8);
                              $$->name = std::to_string(number);
                            } 
                        }
    |
    REAL_LITERAL{ $$ =new ConstantValueNode(@1.first_line, @1.first_column, "real"); double z =atof($1);  $$->name = std::to_string(z); }
    |
    STRING_LITERAL{$$ = new ConstantValueNode(@1.first_line, @1.first_column, "string");  $$->name.assign($1); }
    |
    TRUE{ $$ =new ConstantValueNode(@1.first_line, @1.first_column,"boolean");  $$->name.assign($1); }
    |
    FALSE{ $$ =new ConstantValueNode(@1.first_line, @1.first_column,"boolean");  $$->name.assign($1); }
;

    /*
       Statements
                  */

Statement:
    CompoundStatement   { $$ = $1;}
    |
    Simple              { $$ = $1;}
    |
    Condition           { $$ = $1;}
    |
    While               { $$ = $1;}
    |
    For                 { $$ = $1;}
    |
    Return              { $$ = $1;}
    |
    FunctionInvokation  { $$ = $1;}
;

CompoundStatement:
    BEGIN_
    DeclarationList     
    StatementList      
    END                 { $$ = new CompoundStatementNode(@1.first_line, @1.first_column, $2, $3);}
;

Simple:
    VariableReference ASSIGN Expression SEMICOLON   {$$ = new AssignmentNode(@2.first_line, @2.first_column, $1, $3);}
    |
    PRINT Expression SEMICOLON                      {$$ = new PrintNode(@1.first_line, @1.first_column, $2);}
    |
    READ VariableReference SEMICOLON                {$$ = new ReadNode(@1.first_line, @1.first_column, $2);}
;

VariableReference:
    ID            { $$ = new VariableReferenceNode(@1.first_line, @1.first_column, $1, vector_of_exp_arr);
                    vector_of_exp_arr.clear();}
    |
    ID ArrForm    {  $$ = new VariableReferenceNode(@1.first_line, @1.first_column, $1, vector_of_exp_arr );
                  vector_of_exp_arr.clear();}
;

ArrForm:
    L_BRACKET Expression R_BRACKET          { vector_of_exp_arr.emplace_back($2) ; }
    |
    ArrForm L_BRACKET Expression R_BRACKET  { vector_of_exp_arr.emplace_back($3) ; }
;

Condition:
    IF Expression THEN 
    StatementList    
    ElseOrNot
    END IF                  { $$ = new IfNode(@1.first_line, @1.first_column, $2,  $4, $5 );}  
;

ElseOrNot:
    ELSE
    StatementList           { $$ = new ElseNode(@1.first_line, @1.first_column, $2); }
    |
    Epsilon                 { $$ = NULL;}
;

While:
    WHILE Expression DO
    StatementList
    END DO                  {$$ = new WhileNode(@1.first_line, @1.first_column, $2 , $4);}
;

For:
    FOR ID ASSIGN INT_LITERAL TO INT_LITERAL DO
    StatementList
    END DO                  {   var_temp = new VariableNode(@2.first_line, @2.first_column, "integer");
                                var_temp->name = $2;
                                vector_of_var.emplace_back(var_temp);
                                dec_temp = new DeclarationNode(@2.first_line, @2.first_column,vector_of_var, NULL );//dec ok
                                vector_of_var.clear();
                                
                                con_temp = new ConstantValueNode(@4.first_line, @4.first_column, "");
                                con_temp->name = $4;

                                varf_temp = new VariableReferenceNode(@2.first_line, @2.first_column, $2, vector_of_exp_arr);
                                ass_temp = new AssignmentNode(@3.first_line, @3.first_column,varf_temp, con_temp);//assignment

                                con_temp = new ConstantValueNode(@6.first_line, @6.first_column, $6); //expression
                                con_temp->name = $6;
                                $$ = new ForNode(@1.first_line, @1.first_column, dec_temp ,ass_temp  ,con_temp  , $8);
                            }
;

Return:
    RETURN Expression SEMICOLON   {$$ = new ReturnNode(@1.first_line, @1.first_column,$2);}
;

FunctionInvokation:
    FunctionCall SEMICOLON        {$$ = fun_stat; }
;

FunctionCall:
    ID L_PARENTHESIS ExpressionList R_PARENTHESIS { $$ = new FunctionCallNode(@1.first_line, @1.first_column,$3);
                                                    fun_stat =  new FunctionCallStatNode(@1.first_line, @1.first_column,$3);
                                                    vector_of_exp.clear();
                                                    $$->name.assign($1);
                                                    fun_stat->name.assign($1);
                                                  }

;
ExpressionList:
    Epsilon       {$$ = NULL;}
    |
    Expressions   {$$ = $1;}
;

Expressions:
    Expression                      {$$ = new std::vector<ExpressionNode* >; $$->emplace_back($1);}
    |
    Expressions COMMA Expression    {$1->emplace_back($3); $$ = $1;}
;

StatementList:
    Epsilon      {$$ = NULL; }
    |
    Statements   {$$ = $1;}               
;

Statements:
    Statement                   {$$ = new std::vector<StatementNode* > ; $$->emplace_back($1); }
    |
    Statements Statement        {$1->emplace_back($2); $$ = $1; }
;

Expression:
    L_PARENTHESIS Expression R_PARENTHESIS { $$ = $2;}
    |
    MINUS Expression %prec UNARY_MINUS  {$$ = new UnaryOperatorNode(@1.first_line, @1.first_column, "neg", $2);  }
    |
    Expression MULTIPLY Expression      {$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "*", $1, $3);  }
    |
    Expression DIVIDE Expression        {$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "/", $1, $3);  }
    |
    Expression MOD Expression           {$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "mod", $1, $3);  }
    |
    Expression PLUS Expression          {$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "+", $1, $3);  }
    |
    Expression MINUS Expression         {$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "-", $1, $3); }
    |
    Expression LESS Expression          {$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "<", $1, $3);  }
    |
    Expression LESS_OR_EQUAL Expression {$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "<=", $1, $3);  }
    |
    Expression GREATER Expression       {$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, ">", $1, $3);  }
    |
    Expression GREATER_OR_EQUAL Expression  {$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, ">=", $1, $3); }
    |
    Expression EQUAL Expression         {$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "=", $1, $3); }
    |
    Expression NOT_EQUAL Expression     {$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "<>", $1, $3);  }
    |
    NOT Expression                  {$$ = new UnaryOperatorNode(@1.first_line, @1.first_column, "not", $2);  }
    |
    Expression AND Expression       {$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "and", $1, $3);  }
    |
    Expression OR Expression        {$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "or", $1, $3);  }
    |
    LiteralConstant					{$$ = $1; }
    |
    VariableReference               {$$ = $1; }
    |
    FunctionCall                    {$$ = $1; }
;

    /*
       misc
            */
Epsilon:
;
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
    DumpVisitor dvisitor;

    CHECK(argc >= 2, "Usage: ./parser <filename>\n");

    FILE *fp = fopen(argv[1], "r");

    CHECK(fp != NULL, "fopen() fails.\n");
    yyin = fp;
    yyparse();

    //freeProgramNode(root); 
    root->accept(dvisitor);


    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");
    return 0;
}
