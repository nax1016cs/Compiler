#include <iostream>
#include "AST/declaration.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"


using namespace std;
DeclarationNode::DeclarationNode(uint32_t line, uint32_t col,std::vector<VariableNode*> temp, ConstantValueNode* cons_temp): ASTNodeBase(line,col){
	t = temp;
	cons = cons_temp;
}

void DeclarationNode::printNode(){
    DumpVisitor dvisitor;
    cout<<"  ";
    cout << "declaration "<< "<line:" << location.line<<", col:"<< location.col << "> "<<endl;
    for(auto it: t){
    	if(cons!=NULL){
    		cout << "    ";
    		it->type = cons->type;
    		// it->printNode();
            it->accept(dvisitor);
    		cout << "      ";
    		cons->printNode();
    	}
    	else{
    		cout << "    ";
    		it->printNode();
    	}
    	//cout << "    "<< "<line:" << (*it)->location.line<<", col:"<< (*it)->location.col << "> "<<(*it)->name <<" " <<(*it)->type <<endl;
    }
}

DeclarationNode::~DeclarationNode(){
    ;
}

void DeclarationNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
