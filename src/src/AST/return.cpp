#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);

using namespace std;
ReturnNode::ReturnNode(uint32_t line, uint32_t col, ExpressionNode* e_t): StatementNode(line,col){
	e = e_t;
}

void ReturnNode::printNode(){
	DumpVisitor dvisitor;
	print_tab(tab);
    cout <<"return statement "<< "<line: " << location.line<<", col: "<< location.col << "> "<<endl;
    tab++;
    e->accept(dvisitor);
    tab--;
}

ReturnNode::~ReturnNode(){
    ;
}

void ReturnNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
