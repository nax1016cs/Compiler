#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);

using namespace std;
VariableReferenceNode::VariableReferenceNode(uint32_t line, uint32_t col , std::string name_t , std::vector<ExpressionNode*> vector_of_exp_arr_t): ExpressionNode(line,col){
	name = name_t;
	vector_of_exp_arr = vector_of_exp_arr_t;
}

void VariableReferenceNode::printNode(){
    DumpVisitor dvisitor;
    print_tab(tab);
    cout << "variable reference "<< "<line:" << location.line<<", col:"<< location.col << "> "<< name <<endl;
    for(int i =0; i<vector_of_exp_arr.size(); i++){
        print_tab(tab);
        cout<<"[\n";
        tab++;
        vector_of_exp_arr[i]->accept(dvisitor);
        tab--;
        print_tab(tab);
        cout<<"]\n";
    }
    
}

VariableReferenceNode::~VariableReferenceNode(){
    ;
}

void VariableReferenceNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
