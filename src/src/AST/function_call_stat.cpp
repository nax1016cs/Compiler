#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);

using namespace std;
FunctionCallStatNode::FunctionCallStatNode(uint32_t line, uint32_t col, std::vector<ExpressionNode*>* vector_of_exp_t): StatementNode(line,col){
	vector_of_exp = vector_of_exp_t;
}

void FunctionCallStatNode::printNode(){
    DumpVisitor dvisitor;
    print_tab(tab);
    cout << "function call statement "<< "<line:" << location.line<<", col:"<< location.col << "> "<< name <<endl;
    tab++;
    if(vector_of_exp !=NULL){
        for(auto it:*vector_of_exp){
            it->accept(dvisitor);
        }
    }
    tab--;
}

FunctionCallStatNode::~FunctionCallStatNode(){
    ;
}

void FunctionCallStatNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
