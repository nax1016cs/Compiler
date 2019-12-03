#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"


using namespace std;
ReadNode::ReadNode(uint32_t line, uint32_t col , VariableReferenceNode* e_t): StatementNode(line,col){
	e = e_t;
}

void ReadNode::printNode(){
    DumpVisitor dvisitor;
	cout << "  ";
    cout << "read statement "<< "<line:" << location.line<<", col:"<< location.col << "> "<<endl;
    cout << "    ";
    e->accept(dvisitor);
}

ReadNode::~ReadNode(){
    ;
}

void ReadNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
