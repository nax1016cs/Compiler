#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);


using namespace std;
ElseNode::ElseNode(uint32_t line, uint32_t col, std::vector<StatementNode*>* vector_of_stat_t): StatementNode(line,col){
	vector_of_stat = vector_of_stat_t;
}

void ElseNode::printNode(){
    DumpVisitor dvisitor;
    print_tab(tab);
    cout << "else\n";
    tab++;
    for(auto it:*vector_of_stat){
    	it->accept(dvisitor);
    }
    tab--;
}

ElseNode::~ElseNode(){
    ;
}

void ElseNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
