#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"



using namespace std;
ElseNode::ElseNode(uint32_t line, uint32_t col, std::vector<StatementNode*> vector_of_stat_t): StatementNode(line,col){
	vector_of_stat = vector_of_stat_t;
}

void ElseNode::printNode(){
    DumpVisitor dvisitor;
	cout << "  ";
    cout << "else "<< "<line:" << location.line<<", col:"<< location.col << "> "<<endl;
    for(auto it:vector_of_stat){
    	cout << "    ";
    	it->accept(dvisitor);
    }
}

ElseNode::~ElseNode(){
    ;
}

void ElseNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
