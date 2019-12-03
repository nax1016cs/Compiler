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







static ProgramNode *root;
// static VariableReferenceNode *s;
static ReturnNode* s ;

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


    /*FunctionNode*           function_type;
    CompoundStatementNode*  compound_type;
    AssignmentNode*         assign_type;
    IfNode*                 if_type;
    WhileNode*              while_type;
    ForNode*                for_type;
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
    Epsilon
    |
    Declarations
;

Declarations:
    Declaration {vector_of_dec.emplace_back($1);}
    |
    Declarations Declaration {vector_of_dec.emplace_back($2);}
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
    CompoundStatement
    |
    Simple
    |
    Condition
    |
    While
    |
    For
    |
    Return
    |
    FunctionInvokation
;

CompoundStatement:
    BEGIN_
    DeclarationList
    StatementList
    END
;

Simple:
    VariableReference ASSIGN Expression SEMICOLON   {assign = new AssignmentNode(@1.first_line, @1.first_column, $1, $3);}
    |
    PRINT Expression SEMICOLON                      {print = new PrintNode(@1.first_line, @1.first_column, $2);}
    |
    READ VariableReference SEMICOLON                {read = new ReadNode(@1.first_line, @1.first_column, $2);}
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
    END IF
;

ElseOrNot:
    ELSE
    StatementList
    |
    Epsilon
;

While:
    WHILE Expression DO
    StatementList
    END DO
;

For:
    FOR ID ASSIGN INT_LITERAL TO INT_LITERAL DO
    StatementList
    END DO
;

Return:
    RETURN Expression SEMICOLON   {s = $$ = new ReturnNode(@1.first_line, @1.first_column,$2);}
;

FunctionInvokation:
    FunctionCall SEMICOLON
;

FunctionCall:
    ID L_PARENTHESIS ExpressionList R_PARENTHESIS { $$ = new FunctionCallNode(@1.first_line, @1.first_column,vector_of_exp);
                                                    vector_of_exp.clear();
                                                    $$->name.assign($1);
                                                  }

;
ExpressionList:
    Epsilon
    |
    Expressions
;

Expressions:
    Expression                      {vector_of_exp.emplace_back($1);}
    |
    Expressions COMMA Expression    {vector_of_exp.emplace_back($3);}
;

StatementList:
    Epsilon
    |
    Statements
;

Statements:
    Statement
    |
    Statements Statement
;

Expression:
    L_PARENTHESIS Expression R_PARENTHESIS { $$ = $2;}
    |
    MINUS Expression %prec UNARY_MINUS  {unary = new UnaryOperatorNode(@1.first_line, @1.first_column, "neg", $2); $$ = unary; }
    |
    Expression MULTIPLY Expression      {binary = new BinaryOperatorNode(@1.first_line, @1.first_column, "*", $1, $3); $$ = binary; }
    |
    Expression DIVIDE Expression        {binary = new BinaryOperatorNode(@1.first_line, @1.first_column, "/", $1, $3); $$ = binary; }
    |
    Expression MOD Expression           {binary = new BinaryOperatorNode(@1.first_line, @1.first_column, "mod", $1, $3); $$ = binary; }
    |
    Expression PLUS Expression          {binary = new BinaryOperatorNode(@1.first_line, @1.first_column, "+", $1, $3); $$ = binary; }
    |
    Expression MINUS Expression         {binary = new BinaryOperatorNode(@1.first_line, @1.first_column, "-", $1, $3); $$ = binary; }
    |
    Expression LESS Expression          {binary = new BinaryOperatorNode(@1.first_line, @1.first_column, "<", $1, $3); $$ = binary; }
    |
    Expression LESS_OR_EQUAL Expression {binary = new BinaryOperatorNode(@1.first_line, @1.first_column, "<=", $1, $3); $$ = binary; }
    |
    Expression GREATER Expression       {binary = new BinaryOperatorNode(@1.first_line, @1.first_column, ">", $1, $3); $$ = binary; }
    |
    Expression GREATER_OR_EQUAL Expression  {binary = new BinaryOperatorNode(@1.first_line, @1.first_column, ">=", $1, $3); $$ = binary; }
    |
    Expression EQUAL Expression         {binary = new BinaryOperatorNode(@1.first_line, @1.first_column, "=", $1, $3); $$ = binary;}
    |
    Expression NOT_EQUAL Expression     {binary = new BinaryOperatorNode(@1.first_line, @1.first_column, "<>", $1, $3); $$ = binary; }
    |
    NOT Expression                  {unary = new UnaryOperatorNode(@1.first_line, @1.first_column, "not", $2); $$ = unary; }
    |
    Expression AND Expression       {binary = new BinaryOperatorNode(@1.first_line, @1.first_column, "and", $1, $3); $$ = binary; }
    |
    Expression OR Expression        {binary = new BinaryOperatorNode(@1.first_line, @1.first_column, "or", $1, $3); $$ = binary; }
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

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");
    return 0;
}
