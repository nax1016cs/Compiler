#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"



using namespace std;
CompoundStatementNode::CompoundStatementNode(uint32_t line, uint32_t col, std::vector<DeclarationNode*> vector_of_dec_t, std::vector<StatementNode*> vector_of_stat_t): StatementNode(line,col){
	vector_of_dec = vector_of_dec_t;
	vector_of_stat = vector_of_stat_t;
}

void CompoundStatementNode::printNode(){
    DumpVisitor dvisitor;
	cout << "  ";
    cout << "compound statement "<< "<line:" << location.line<<", col:"<< location.col << "> "<<endl;
    for(auto it:vector_of_dec){
    	cout << "    ";
    	it->accept(dvisitor);
    }
    for(auto it:vector_of_stat){
    	cout << "    ";
    	it->accept(dvisitor);
    }
}

CompoundStatementNode::~CompoundStatementNode(){
    ;
}

void CompoundStatementNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
