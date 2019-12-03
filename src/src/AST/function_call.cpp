#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"


using namespace std;
FunctionCallNode::FunctionCallNode(uint32_t line, uint32_t col, std::vector<ExpressionNode*> vector_of_exp_t): ExpressionNode(line,col){
	vector_of_exp = vector_of_exp_t;
}

void FunctionCallNode::printNode(){
    DumpVisitor dvisitor;
	cout << "  ";
    cout << "function call statement "<< "<line:" << location.line<<", col:"<< location.col << "> "<< name <<endl;
    for(auto it:vector_of_exp){
    	cout << "    ";
    	it->accept(dvisitor);
    }
}

FunctionCallNode::~FunctionCallNode(){
    ;
}

void FunctionCallNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
