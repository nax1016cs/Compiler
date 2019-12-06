#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);

using namespace std;
PrintNode::PrintNode(uint32_t line, uint32_t col , ExpressionNode* e_t): StatementNode(line,col){
	e = e_t;
}

void PrintNode::printNode(){
    DumpVisitor dvisitor;
    print_tab(tab);
    cout << "print statement "<< "<line: " << location.line<<", col: "<< location.col << "> "<<endl;
    tab++;
    e->accept(dvisitor);
    tab--;
}

PrintNode::~PrintNode(){
    ;
}

void PrintNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
