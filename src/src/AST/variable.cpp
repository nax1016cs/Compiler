#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"

using namespace std;
VariableNode::VariableNode(uint32_t line, uint32_t col, string type_t): ASTNodeBase(line,col){
	type = type_t;
}

void VariableNode::printNode(){
    cout << "variable "<< "<line:" << location.line<<", col:"<< location.col << "> "<< name  << " "<<type<<endl;
}

VariableNode::~VariableNode(){
    ;
}

void VariableNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
