#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"


using namespace std;
ReturnNode::ReturnNode(uint32_t line, uint32_t col, ExpressionNode* e_t): StatementNode(line,col){
	e = e_t;
}

void ReturnNode::printNode(){
	DumpVisitor dvisitor;
	cout<<"  ";
    cout << "return statement "<< "<line:" << location.line<<", col:"<< location.col << "> "<<endl;
    cout<<"    ";
    e->accept(dvisitor);
}

ReturnNode::~ReturnNode(){
    ;
}

void ReturnNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
