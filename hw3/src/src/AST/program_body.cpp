#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);

using namespace std;
ProgramBodyNode::ProgramBodyNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void ProgramBodyNode::printNode(){
    DumpVisitor dvisitor;
    if(d!=NULL){
        for(auto it :*d){
            it->accept(dvisitor);
        }
    }
    if(f!=NULL){
        for(auto it :*f){
            it->accept(dvisitor);
        }
    }
    c->accept(dvisitor);
    

}

ProgramBodyNode::~ProgramBodyNode(){
    ;
}

void ProgramBodyNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
