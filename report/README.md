# 作業 3 報告

> 學生：蔣傑名
>
> 學號：0516097
> 

## Change in scanner.l
- Add `yylval.str=strdup(yytext);` to each token, so `parser.y` can get the string from scanner.l.



## Change in parser.l
- Include the sub-nodes I need.
```cpp= #include "include/AST/ast.hpp"
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
```
- Declare the type in parser.
```cpp= 
%union {
    char *str;
    ProgramNode*                    program_type;
    DeclarationNode*                declaration_type;
    ConstantValueNode*              constant_type;
    VariableNode*                   variable_type;
    BinaryOperatorNode*             bop_type;
    ExpressionNode* 	             exp_type;
    FunctionCallNode*               function_call_type;
    VariableReferenceNode*          var_ref_type;
    ReturnNode*                     return_type;
    StatementNode*                  statement_type;
    WhileNode*                      while_type;
    ForNode*                        for_type;
    CompoundStatementNode*          cmp_type;
    IfNode*                         if_type;
    ElseNode*                       else_type;
    std::vector<StatementNode*>*    vector_stat_type; 
    std::vector<ExpressionNode*>*   vector_exp_type; 
    std::vector<DeclarationNode*>*  vector_of_dec_type;
    FunctionNode*                   function_type;
    std::vector<FunctionNode*>*     vector_of_fun_type;
    ProgramBodyNode*                program_body_type;
}
```
- Declare the type of non-terminals and terminals
```cpp=
%type<program_type>         Program
%type<declaration_type>     Declaration
%type<constant_type>        LiteralConstant
%type<variable_type>        IdList
%type<exp_type>             Expression
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
%type<function_type>        FunctionDeclaration
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
```

- Create the node as below and create the whole AST.
```cpp=
Program:
    ProgramName SEMICOLON ProgramBody END ProgramName {
        $$ = root = new ProgramNode(@1.first_line, @1.first_column);
        $$->p = $3;
        $$->name.assign($1);
    }
;
```


## Ability of my AST

- My AST can recognize : 
    - Program node
    - Compound statement node
    - Assignment node
    - Print node
    - Read node
    - If node
    - While node
    - For node
    - Return node
    - Function call node
    - Binary operator node
    - Unary operator node
    - Constant value node
    - Variable reference node
    - Function call node

- With the Nodes created above, My AST could recognize the P language



## Use visitor pattern

- The codes below are how I traverse in `print node`. The other nodes are implemented in the same way.

```cpp=
void PrintNode::printNode(){
    DumpVisitor dvisitor;
    print_tab(tab);
    cout << "print statement "<< "<line: " << location.line<<", col: "<< location.col << "> "<<endl;
    tab++;
    e->accept(dvisitor);
    tab--;
}

```

## Result 
![imgur](https://imgur.com/b08KUnn.jpg)