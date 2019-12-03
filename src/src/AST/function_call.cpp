#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"

using namespace std;
FunctionCallNode::FunctionCallNode(uint32_t line, uint32_t col): ExpressionNode(line,col){
}

void FunctionCallNode::printNode(){
    //cout << "program "<< "<line:" << location.line<<", col:"<< location.col << "> "<< name  << " void"<<endl;
}

FunctionCallNode::~FunctionCallNode(){
    ;
}

void FunctionCallNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
