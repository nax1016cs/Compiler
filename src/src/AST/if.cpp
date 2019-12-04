#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"



using namespace std;
IfNode:: IfNode(uint32_t line, uint32_t col, ExpressionNode* e_t, std::vector<StatementNode*>* vector_of_stat_t, ElseNode* els_t): StatementNode(line,col){
	e = e_t;
    vector_of_stat = vector_of_stat_t;
    els = els_t;
}

void IfNode::printNode(){
    DumpVisitor dvisitor;
	cout << "  ";
    cout << "if statement "<< "<line:" << location.line<<", col:"<< location.col << "> "<<endl;
    cout<<"  ";
    e->accept(dvisitor);
    for(auto it:*vector_of_stat){
    	cout << "    ";
    	it->accept(dvisitor);
    }
    if(els !=NULL) els->accept(dvisitor);
}

IfNode::~IfNode(){
    ;
}

void IfNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
