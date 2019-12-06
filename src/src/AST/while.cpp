#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);

using namespace std;
WhileNode::WhileNode(uint32_t line, uint32_t col,ExpressionNode* e_t ,  std::vector<StatementNode*>* vector_of_stat_t): StatementNode(line,col){
	vector_of_stat = vector_of_stat_t;
	e = e_t;
}

void WhileNode::printNode(){
    DumpVisitor dvisitor;
    print_tab(tab);
    cout << "while statement "<< "<line:" << location.line<<", col:"<< location.col << "> "<<endl;
    tab++;
    e->accept(dvisitor);
    if(vector_of_stat!=NULL){
        for(auto it:*vector_of_stat){
            it->accept(dvisitor);
        }        
    }
    tab--;
}

WhileNode::~WhileNode(){
    ;
}

void WhileNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
