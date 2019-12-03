#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"


using namespace std;
VariableReferenceNode::VariableReferenceNode(uint32_t line, uint32_t col , std::string name_t , ExpressionNode* e_t): ExpressionNode(line,col){
	name = name_t;
	e = e_t;
}

void VariableReferenceNode::printNode(){
    DumpVisitor dvisitor;
	cout << "  ";
    cout << "variable reference "<< "<line:" << location.line<<", col:"<< location.col << "> "<< name <<endl;
    if(e !=NULL){
    	cout<<"  [\n";
    	cout<<"    ";
    	e->accept(dvisitor);
    	cout<<"  ]\n";
    }
    
}

VariableReferenceNode::~VariableReferenceNode(){
    ;
}

void VariableReferenceNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
