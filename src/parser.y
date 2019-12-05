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


#include "include/core/error.h"
#include "include/visitor/dumpvisitor.hpp"


#include <stdio.h>
#include <stdlib.h>
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
int count_bracket = 0;

std::vector<VariableNode*> vector_of_var;
std::vector<DeclarationNode*> vector_of_dec;
std::vector<ExpressionNode*> vector_of_exp; // for function
std::vector<ExpressionNode*> vector_of_exp_arr; // for arr
std::vector<StatementNode*> vector_of_stat; // for stat
std::vector<StatementNode*> vector_of_stat_pro; // for program statementlist

std::vector<StatementNode*> vector_of_stat_cmp; // for program statementlist
std::vector<DeclarationNode*> vector_of_dec_cmp;

std::vector<StatementNode*> vector_of_stat_t ;









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
CompoundStatementNode*                  s ;



static ProgramNode *root;
// static VariableReferenceNode *s;
// static IfNode* s ;

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
    // int  *num; 
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


    /*FunctionNode*           function_type;
    CompoundStatementNode*  compound_type;
    IfNode*                 if_type;
    */

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
















/*%type<function_type>
%type<compound_type>        CompoundStatement
%type<assign_type>
%type<print_type>
%type<read_type>
%type<var_ref_type>
%type<uop_type>
%type<if_type>              Condition
%type<while_type>           While
%type<for_type>             For
%type<return_type>          Return
%type<function_call_type>   FunctionCall*/



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





%%
    /*
       Program Units
                     */

Program:
    ProgramName SEMICOLON ProgramBody END ProgramName {
        $$ = root = new ProgramNode(@1.first_line, @1.first_column,vector_of_dec);
        vector_of_dec.clear();
        $$->name.assign($1);
    }
;

ProgramName:
    ID
;

ProgramBody:
    DeclarationList FunctionList CompoundStatement
;

DeclarationList:
    Epsilon 		{$$ = NULL;}
    |
    Declarations    {$$ = new std::vector<DeclarationNode* >;  for(auto it: vector_of_dec) $$->emplace_back(it); vector_of_dec.clear();}
;

Declarations:
    Declaration              { vector_of_dec.clear();   vector_of_dec.emplace_back($1); }
    |
    Declarations Declaration {vector_of_dec.emplace_back($2); }
;

FunctionList:
    Epsilon
    |
    Functions
;

Functions:
    FunctionDeclaration
    |
    Functions FunctionDeclaration
;

FunctionDeclaration:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType SEMICOLON
    CompoundStatement
    END FunctionName
;

FunctionName:
    ID
;

FormalArgList:
    Epsilon
    |
    FormalArgs
;

FormalArgs:
    FormalArg
    |
    FormalArgs SEMICOLON FormalArg
;

FormalArg:
    IdList COLON Type
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
    COLON ScalarType
    |
    Epsilon
;

    /*
       Data Types and Declarations
                                   */

// Declaration:
//     VAR IdList COLON TypeOrConstant SEMICOLON{
//         for(it = vector_of_var.begin(); it!=vector_of_var.end(); it++){
//             // std::cout<<(*it)->name<<'\n';
//             (*it)->type = "integer";
//         }
//         s = new DeclarationNode(@1.first_line, @1.first_column,vector_of_var);
// 		vector_of_var.clear();
//     }
// ;

Declaration:
    VAR IdList COLON Type SEMICOLON{
    	for(auto it: vector_of_var){
            // std::cout<<(*it)->name<<'\n';
            it->type = $4;
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

// TypeOrConstant:
//     Type 
//     |
//     LiteralConstant
// ;

Type:
    ScalarType {$$ = $1;}
    |
    ArrType
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
    ArrDecl ScalarType
;

ArrDecl:
    ARRAY INT_LITERAL TO INT_LITERAL OF
    |
    ArrDecl ARRAY INT_LITERAL TO INT_LITERAL OF
;

LiteralConstant:
    INT_LITERAL{$$ =  new ConstantValueNode(@1.first_line, @1.first_column, "integer");  $$->name.assign($1); }
    |
    REAL_LITERAL{ $$ =new ConstantValueNode(@1.first_line, @1.first_column, "real");  $$->name.assign($1); }
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
    CompoundStatement   { $$ = $1;/*vector_of_stat.clear();*/ vector_of_stat_pro.emplace_back($1);}
    |
    Simple              { $$ = $1;/*vector_of_stat.clear();*/ vector_of_stat_pro.emplace_back($1);}
    |
    Condition           { $$ = $1;/*vector_of_stat.clear();*/ vector_of_stat_pro.emplace_back($1);}
    |
    While               { $$ = $1;/*vector_of_stat.clear();*/ vector_of_stat_pro.emplace_back($1);}
    |
    For                 { $$ = $1;/*vector_of_stat.clear();*/vector_of_stat_pro.emplace_back($1);}
    |
    Return              { $$ = $1;/*vector_of_stat.clear();*/ vector_of_stat_pro.emplace_back($1);}
    |
    FunctionInvokation  { $$ = $1;/*vector_of_stat.clear();*/ vector_of_stat_pro.emplace_back($1);}
;

CompoundStatement:
    BEGIN_
    DeclarationList     
    StatementList      
    END                 { $$ = new CompoundStatementNode(@1.first_line, @1.first_column, $2, $3); vector_of_dec.clear(); vector_of_stat.clear(); s = $$; }
;

Simple:
    VariableReference ASSIGN Expression SEMICOLON   {$$ = new AssignmentNode(@2.first_line, @2.first_column, $1, $3);}
    |
    PRINT Expression SEMICOLON                      {$$ = new PrintNode(@1.first_line, @1.first_column, $2);}
    |
    READ VariableReference SEMICOLON                {$$ = new ReadNode(@1.first_line, @1.first_column, $2);}
;

VariableReference:
    ID          { $$ = new VariableReferenceNode(@1.first_line, @1.first_column, $1, vector_of_exp_arr);
                  vector_of_exp_arr.clear();
                  count_bracket = 0;}
    |
    ID ArrForm {  $$ = new VariableReferenceNode(@1.first_line, @1.first_column, $1, vector_of_exp_arr );
                  vector_of_exp_arr.clear();
                  count_bracket = 0;}
;

ArrForm:
    L_BRACKET Expression R_BRACKET { vector_of_exp_arr.emplace_back($2) ; count_bracket += 1;}
    |
    ArrForm L_BRACKET Expression R_BRACKET { vector_of_exp_arr.emplace_back($3) ; count_bracket += 1;}
;

Condition:
    IF Expression THEN 
    StatementList    
    ElseOrNot
    END IF           {  $$ = new IfNode(@1.first_line, @1.first_column, $2,  $4, $5 ); /*vector_of_stat.clear();*/}  
;

ElseOrNot:
    ELSE
    StatementList           { $$ = new ElseNode(@1.first_line, @1.first_column,  $2); }
    |
    Epsilon                 { $$ = NULL;}
;

While:
    WHILE Expression DO
    StatementList
    END DO                  {$$ = new WhileNode(@1.first_line, @1.first_column, $2 , $4);
                        
     /*vector_of_stat.clear();*/ }
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
                                // may have problem
                                varf_temp = new VariableReferenceNode(@2.first_line, @2.first_column, $2, vector_of_exp_arr);
                                ass_temp = new AssignmentNode(@3.first_line, @3.first_column,varf_temp, con_temp);//assignment

                                con_temp = new ConstantValueNode(@6.first_line, @6.first_column, $6); //expression
                                con_temp->name = $6;
                                $$ = new ForNode(@1.first_line, @1.first_column, dec_temp ,ass_temp  ,con_temp  , $8);
                                // s = $$;
                                // vector_of_stat.clear();
                                
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
    Expressions   {$$ = new std::vector<ExpressionNode* >;  for(auto it: vector_of_exp) $$->emplace_back(it); vector_of_exp.clear();}
;

Expressions:
    Expression                      {vector_of_exp.emplace_back($1);}
    |
    Expressions COMMA Expression    {vector_of_exp.emplace_back($3);}
;

StatementList:
    Epsilon      {$$ = NULL; }
    |
    Statements   {$$ = $1;}               
;

Statements:
    Statement                   {$$ = new std::vector<StatementNode* > ; $$->emplace_back($1); /*vector_of_stat.emplace_back($1);*/}
    |
    Statements Statement        {$1->emplace_back($2); $$ = $1; /*vector_of_stat.emplace_back($2);*/}
;

Expression:
    L_PARENTHESIS Expression R_PARENTHESIS { $$ = $2;}
    |
    MINUS Expression %prec UNARY_MINUS  {unary = new UnaryOperatorNode(@1.first_line, @1.first_column, "neg", $2); $$ = unary; }
    |
    Expression MULTIPLY Expression      {binary = new BinaryOperatorNode(@2.first_line, @2.first_column, "*", $1, $3); $$ = binary; }
    |
    Expression DIVIDE Expression        {binary = new BinaryOperatorNode(@2.first_line, @2.first_column, "/", $1, $3); $$ = binary; }
    |
    Expression MOD Expression           {binary = new BinaryOperatorNode(@2.first_line, @2.first_column, "mod", $1, $3); $$ = binary; }
    |
    Expression PLUS Expression          {binary = new BinaryOperatorNode(@2.first_line, @2.first_column, "+", $1, $3); $$ = binary; }
    |
    Expression MINUS Expression         {binary = new BinaryOperatorNode(@2.first_line, @2.first_column, "-", $1, $3); $$ = binary; }
    |
    Expression LESS Expression          {binary = new BinaryOperatorNode(@2.first_line, @2.first_column, "<", $1, $3); $$ = binary; }
    |
    Expression LESS_OR_EQUAL Expression {binary = new BinaryOperatorNode(@2.first_line, @2.first_column, "<=", $1, $3); $$ = binary; }
    |
    Expression GREATER Expression       {binary = new BinaryOperatorNode(@2.first_line, @2.first_column, ">", $1, $3); $$ = binary; }
    |
    Expression GREATER_OR_EQUAL Expression  {binary = new BinaryOperatorNode(@2.first_line, @2.first_column, ">=", $1, $3); $$ = binary; }
    |
    Expression EQUAL Expression         {binary = new BinaryOperatorNode(@2.first_line, @2.first_column, "=", $1, $3); $$ = binary;}
    |
    Expression NOT_EQUAL Expression     {binary = new BinaryOperatorNode(@2.first_line, @2.first_column, "<>", $1, $3); $$ = binary; }
    |
    NOT Expression                  {unary = new UnaryOperatorNode(@1.first_line, @1.first_column, "not", $2); $$ = unary; }
    |
    Expression AND Expression       {binary = new BinaryOperatorNode(@2.first_line, @2.first_column, "and", $1, $3); $$ = binary; }
    |
    Expression OR Expression        {binary = new BinaryOperatorNode(@2.first_line, @2.first_column, "or", $1, $3); $$ = binary; }
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
    CHECK(argc == 2, "Usage: ./parser <filename>\n");

    FILE *fp = fopen(argv[1], "r");

    CHECK(fp != NULL, "fopen() fails.\n");
    yyin = fp;
    yyparse();

    //freeProgramNode(root); 
    DumpVisitor dvisitor;
    root->accept(dvisitor);
    s->accept(dvisitor);
    // read->accept(dvisitor);
    // print->accept(dvisitor);


    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");
    return 0;
}
