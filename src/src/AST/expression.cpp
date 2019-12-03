#include <iostream>
#include "AST/declaration.hpp"
#include "visitor/visitor.hpp"

using namespace std;

ExpressionNode::ExpressionNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void ExpressionNode::printNode(){
 
}

ExpressionNode::~ExpressionNode(){
    ;
}

void ExpressionNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
