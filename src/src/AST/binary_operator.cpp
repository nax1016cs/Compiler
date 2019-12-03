#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"


using namespace std;
BinaryOperatorNode::BinaryOperatorNode(uint32_t line, uint32_t col , std::string name_t , ExpressionNode* e1_t,ExpressionNode* e2_t): ExpressionNode(line,col){
	name = name_t;
	e1 = e1_t;
	e2 = e2_t;

}

void BinaryOperatorNode::printNode(){
    DumpVisitor dvisitor;
	cout << "  ";
    cout << "binary operator "<< "<line:" << location.line<<", col:"<< location.col << "> "<< name <<endl;
    cout << "    ";
    e1->accept(dvisitor);
    cout << "    ";
    e2->accept(dvisitor);

    
}

BinaryOperatorNode::~BinaryOperatorNode(){
    ;
}

void BinaryOperatorNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
