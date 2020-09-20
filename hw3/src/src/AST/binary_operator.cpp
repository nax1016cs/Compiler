#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);

using namespace std;
BinaryOperatorNode::BinaryOperatorNode(uint32_t line, uint32_t col , std::string name_t , ExpressionNode* e1_t,ExpressionNode* e2_t): ExpressionNode(line,col){
	name = name_t;
	e1 = e1_t;
	e2 = e2_t;

}

void BinaryOperatorNode::printNode(){
    DumpVisitor dvisitor;
    print_tab(tab);
    cout << "binary operator "<< "<line: " << location.line<<", col: "<< location.col << "> "<< name <<endl;
    tab++;
    e1->accept(dvisitor);
    e2->accept(dvisitor);
    tab--;

    
}

BinaryOperatorNode::~BinaryOperatorNode(){
    ;
}

void BinaryOperatorNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
