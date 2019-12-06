#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);

using namespace std;
FunctionCallNode::FunctionCallNode(uint32_t line, uint32_t col, std::vector<ExpressionNode*>* vector_of_exp_t): ExpressionNode(line,col){
	vector_of_exp = vector_of_exp_t;
}

void FunctionCallNode::printNode(){
    DumpVisitor dvisitor;
    print_tab(tab);
    cout << "function call statement "<< "<line: " << location.line<<", col: "<< location.col << "> "<< name <<endl;
    tab++;
    if(vector_of_exp !=NULL){
        for(auto it:*vector_of_exp){
            it->accept(dvisitor);
        }
    }
    tab--;

}

FunctionCallNode::~FunctionCallNode(){
    ;
}

void FunctionCallNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
