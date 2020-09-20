#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);

using namespace std;
ReadNode::ReadNode(uint32_t line, uint32_t col , VariableReferenceNode* e_t): StatementNode(line,col){
	e = e_t;
}

void ReadNode::printNode(){
    DumpVisitor dvisitor;
    print_tab(tab);
    cout << "read statement "<< "<line: " << location.line<<", col: "<< location.col << "> "<<endl;
    tab++;
    e->accept(dvisitor);
    tab--;
}

ReadNode::~ReadNode(){
    ;
}

void ReadNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
