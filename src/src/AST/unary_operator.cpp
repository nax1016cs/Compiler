#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);

using namespace std;
UnaryOperatorNode::UnaryOperatorNode(uint32_t line, uint32_t col , std::string name_t , ExpressionNode* e_t): ExpressionNode(line,col){
	name = name_t;
	e = e_t;
}

void UnaryOperatorNode::printNode(){
    DumpVisitor dvisitor;
    print_tab(tab);
    cout << "unary operator "<< "<line:" << location.line<<", col:"<< location.col << "> "<< name <<endl;
    tab++;
    e->accept(dvisitor);
    tab--;
    
}

UnaryOperatorNode::~UnaryOperatorNode(){
    ;
}

void UnaryOperatorNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
