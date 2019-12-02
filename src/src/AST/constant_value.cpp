#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"

using namespace std;
ConstantValueNode::ConstantValueNode(uint32_t line, uint32_t col,std::string type_temp): ASTNodeBase(line,col){
	type = type_temp;
}

void ConstantValueNode::printNode(){
    cout << "constant "<< "<line:" << location.line<<", col:"<< location.col << "> "<<name <<endl;
}

ConstantValueNode::~ConstantValueNode(){
    ;
}

void ConstantValueNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
