#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"


using namespace std;
AssignmentNode::AssignmentNode(uint32_t line, uint32_t col, VariableReferenceNode * v_t ,ExpressionNode * e_t): StatementNode(line,col){
	v = v_t;
	e = e_t;
}

void AssignmentNode::printNode(){
    DumpVisitor dvisitor;
	cout<<"  ";
    cout << "assignment statement "<< "<line:" << location.line<<", col:"<< location.col << "> " <<endl;
	cout<<"  ";
    v->accept(dvisitor);
    cout<<"    ";
    e->accept(dvisitor);


}

AssignmentNode::~AssignmentNode(){
    ;
}

void AssignmentNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
