#include <iostream>
#include <vector>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"



using namespace std;
ProgramNode::ProgramNode(uint32_t line, uint32_t col,std::vector<DeclarationNode*> vector_of_dec_t): ASTNodeBase(line,col){
	vector_of_dec = vector_of_dec_t;
}

void ProgramNode::printNode(){
    DumpVisitor dvisitor;
    cout << "program "<< "<line:" << location.line<<", col:"<< location.col << "> "<< name  << " void"<<endl;
    for (auto it:vector_of_dec){
    	it->accept(dvisitor);
    }
}

ProgramNode::~ProgramNode(){
    ;
}

void ProgramNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
