#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"

using namespace std;
ProgramNode::ProgramNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void ProgramNode::printNode(){
    cout << "program "<< "<line:" << location.line<<", col:"<< location.col << "> "<< name  << " void"<<endl;
}

ProgramNode::~ProgramNode(){
    ;
}

void ProgramNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
