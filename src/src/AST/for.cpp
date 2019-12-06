#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);

using namespace std;
ForNode::ForNode(uint32_t line, uint32_t col,DeclarationNode* d_t, AssignmentNode* a_t,ExpressionNode* e_t ,  std::vector<StatementNode*>* vector_of_stat_t): StatementNode(line,col){
	vector_of_stat = vector_of_stat_t;
	e = e_t;
	d = d_t;
	a = a_t;
}

void ForNode::printNode(){
    DumpVisitor dvisitor;
    print_tab( tab);
    cout << "for statement "<< "<line: " << location.line<<", col: "<< location.col << "> "<<endl;
    tab++;
    d->accept(dvisitor);
    a->accept(dvisitor);
    e->accept(dvisitor);
    tab--;
    if(vector_of_stat!=NULL){
        tab++;
        for(auto it:*vector_of_stat){
            it->accept(dvisitor);
        }       
        tab--; 
    }

}

ForNode::~ForNode(){
    ;
}

void ForNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
