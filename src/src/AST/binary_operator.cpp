#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"

using namespace std;
BinaryOperatorNode::BinaryOperatorNode(uint32_t line, uint32_t col, std::string op_temp): ASTNodeBase(line,col){
	op = op_temp;
}

void BinaryOperatorNode::printNode(){
    cout << "binary operator "<< "<line:" << location.line<<", col:"<< location.col << "> "<< op  <<endl;
  

}

BinaryOperatorNode::~BinaryOperatorNode(){
    ;
}

void BinaryOperatorNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
