%{

#include "include/AST/ast.hpp"
#include "include/AST/program.hpp"
#include "include/AST/declaration.hpp"
#include "include/AST/constant_value.hpp"
#include "include/AST/binary_operator.hpp"
#include "include/AST/expression.hpp"


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
std::vector<VariableNode*> vector_of_var;
std::vector<VariableNode*> ::iterator it;

/* Declared by lex */
extern FILE *yyin;
extern char *yytext;

extern "C" int yylex(void);
extern "C" int yyparse();
static void yyerror(const char *msg);

static ProgramNode *root;
static DeclarationNode *s;

%}

%locations
%code requires{ #include "AST/program.hpp" }
%code requires{ #include "AST/declaration.hpp"}
%code requires{ #include "AST/constant_value.hpp"}
%code requires{ #include "AST/variable.hpp"}
%code requires{ #include "AST/binary_operator.hpp"}
%code requires{ #include "AST/expression.hpp"}



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
    //int  *num; 
    ProgramNode*            program_type;
    DeclarationNode*        declaration_type;
    ConstantValueNode*      constant_type;
    VariableNode*           variable_type;
    BinaryOperatorNode*     bop_type;
    ExpressionNode* 		exp_type;
    /*FunctionNode*           function_type;
    CompoundStatementNode*  compound_type;
    AssignmentNode*         assign_type;
    PrintNode*              print_type;
    ReadNode*               read_type;
    VariableReferenceNode*  var_ref_type;
    UnaryOperatorNode*      uop_type;
    IfNode*                 if_type;
    WhileNode*              while_type;
    ForNode*                for_type;
    ReturnNode*             return_type;
    FunctionCallNode*       function_call_type;*/

}
%type<program_type>         Program
%type<declaration_type>     Declaration
%type<constant_type>        LiteralConstant
%type<variable_type>        IdList
%type<ExpressionNode>		Expression
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
        $$ = root = new ProgramNode(@1.first_line, @1.first_column);
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
    Declaration
    |
    Declarations Declaration
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
        s = $$ = new DeclarationNode(@1.first_line, @1.first_column,vector_of_var,NULL);
		vector_of_var.clear();
	}
    |
    VAR IdList COLON LiteralConstant SEMICOLON{
        s = $$ = new DeclarationNode(@1.first_line, @1.first_column,vector_of_var,$4);
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
    VariableReference ASSIGN Expression SEMICOLON
    |
    PRINT Expression SEMICOLON
    |
    READ VariableReference SEMICOLON
;

VariableReference:
    ID
    |
    ID ArrForm
;

ArrForm:
    L_BRACKET Expression R_BRACKET
    |
    ArrForm L_BRACKET Expression R_BRACKET
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
    RETURN Expression SEMICOLON
;

FunctionInvokation:
    FunctionCall SEMICOLON
;

FunctionCall:
    ID L_PARENTHESIS ExpressionList R_PARENTHESIS
;

ExpressionList:
    Epsilon
    |
    Expressions
;

Expressions:
    Expression
    |
    Expressions COMMA Expression
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
    L_PARENTHESIS Expression R_PARENTHESIS
    |
    MINUS Expression %prec UNARY_MINUS 
    |
    Expression MULTIPLY Expression 
    |
    Expression DIVIDE Expression
    |
    Expression MOD Expression
    |
    Expression PLUS Expression
    |
    Expression MINUS Expression
    |
    Expression LESS Expression
    |
    Expression LESS_OR_EQUAL Expression
    |
    Expression GREATER Expression
    |
    Expression GREATER_OR_EQUAL Expression
    |
    Expression EQUAL Expression
    |
    Expression NOT_EQUAL Expression
    |
    NOT Expression
    |
    Expression AND Expression
    |
    Expression OR Expression
    |
    LiteralConstant					
    |
    VariableReference
    |
    FunctionCall
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
