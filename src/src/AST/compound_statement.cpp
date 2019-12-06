#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);


using namespace std;
CompoundStatementNode::CompoundStatementNode(uint32_t line, uint32_t col, std::vector<DeclarationNode*>* vector_of_dec_t, std::vector<StatementNode*>* vector_of_stat_t): StatementNode(line,col){
	vector_of_dec = vector_of_dec_t;
	vector_of_stat = vector_of_stat_t;
}

void CompoundStatementNode::printNode(){
    DumpVisitor dvisitor;
    print_tab(tab);
    cout << "compound statement "<< "<line:" << location.line<<", col:"<< location.col << "> "<<endl;
    if(vector_of_dec!= NULL){
        tab++;
        for(auto it:*vector_of_dec){
            it->accept(dvisitor);
        }  
        tab--;      
    }

    if(vector_of_stat!=NULL){
        tab++;
        for(auto it:*vector_of_stat){
            it->accept(dvisitor);
        }        
        tab--;
    }

}

CompoundStatementNode::~CompoundStatementNode(){
    ;
}

void CompoundStatementNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
