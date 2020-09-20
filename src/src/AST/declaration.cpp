#include <iostream>
#include "AST/declaration.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);

using namespace std;
DeclarationNode::DeclarationNode(uint32_t line, uint32_t col,std::vector<VariableNode*> temp, ConstantValueNode* cons_temp): ASTNodeBase(line,col){
	t = temp;
	cons = cons_temp;
}

void DeclarationNode::printNode(){
    DumpVisitor dvisitor;
    print_tab(tab);
    cout << "declaration "<< "<line: " << location.line<<", col: "<< location.col << "> "<<endl;
    tab++;
    for(auto it: t){
    	if(cons!=NULL){
            print_tab( tab);
    		it->type = cons->type;
            it->accept(dvisitor);
            tab++;
    		cons->printNode();
            tab--;
    	}
    	else{
            print_tab( tab);
    		it->printNode();
    	}
    }
    tab--;
}

DeclarationNode::~DeclarationNode(){
    ;
}

void DeclarationNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
