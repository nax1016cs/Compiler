#include <iostream>
#include <vector>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);


using namespace std;
ProgramNode::ProgramNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void ProgramNode::printNode(){
    DumpVisitor dvisitor;
    cout << "program "<< "<line:" << location.line<<", col:"<< location.col << "> "<< name  << " void"<<endl;
    tab++;
    p->accept(dvisitor);
    tab--;
}

ProgramNode::~ProgramNode(){
    ;
}

void ProgramNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
