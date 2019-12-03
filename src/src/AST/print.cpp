#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"


using namespace std;
PrintNode::PrintNode(uint32_t line, uint32_t col , ExpressionNode* e_t): ASTNodeBase(line,col){
	e = e_t;
}

void PrintNode::printNode(){
    DumpVisitor dvisitor;
	cout << "  ";
    cout << "print statement "<< "<line:" << location.line<<", col:"<< location.col << "> "<<endl;
    cout << "    ";
    e->accept(dvisitor);
}

PrintNode::~PrintNode(){
    ;
}

void PrintNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
