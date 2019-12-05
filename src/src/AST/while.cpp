#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"


using namespace std;
WhileNode::WhileNode(uint32_t line, uint32_t col,ExpressionNode* e_t ,  std::vector<StatementNode*>* vector_of_stat_t): StatementNode(line,col){
	vector_of_stat = vector_of_stat_t;
	e = e_t;
}

void WhileNode::printNode(){
    DumpVisitor dvisitor;
	cout << "  ";
    cout << "while statement "<< "<line:" << location.line<<", col:"<< location.col << "> "<<endl;
    e->accept(dvisitor);
    if(vector_of_stat!=NULL){
        for(auto it:*vector_of_stat){
            cout << "    ";
            it->accept(dvisitor);
        }        
    }
}

WhileNode::~WhileNode(){
    ;
}

void WhileNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
