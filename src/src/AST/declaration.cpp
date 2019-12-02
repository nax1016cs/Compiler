#include <iostream>
#include "AST/declaration.hpp"
#include "visitor/visitor.hpp"

using namespace std;
DeclarationNode::DeclarationNode(uint32_t line, uint32_t col,std::vector<VariableNode*> temp, ConstantValueNode* cons_temp): ASTNodeBase(line,col){
	t = temp;
	cons = cons_temp;
}

void DeclarationNode::printNode(){
	std::vector<VariableNode*> ::iterator it;
    cout << "declaration "<< "<line:" << location.line<<", col:"<< location.col << "> "<<endl;
    for(it = t.begin(); it !=t.end(); it++){
    	if(cons!=NULL){
    		cout << "    ";
    		(*it)->type = cons->type;
    		(*it)->printNode();
    		cout << "        ";
    		cons->printNode();
    	}
    	else{
    		cout << "    ";
    		(*it)->printNode();
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
