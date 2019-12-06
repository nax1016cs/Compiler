#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);

using namespace std;
FunctionNode::FunctionNode(uint32_t line, uint32_t col,CompoundStatementNode* c_t,std::vector<DeclarationNode*>* d_t): ASTNodeBase(line,col){
	c = c_t;
	d = d_t;
}

void FunctionNode::printNode(){
    DumpVisitor dvisitor;
    std::vector<std::string> ::iterator it ;
	if(type == ""){
        type = "void";
    }
	int ct =0;
    print_tab(tab);
    cout << "function declaration "<< "<line:" << location.line<<", col:"<< location.col << "> "<< name  <<" "<< type <<" (";
    if(v_string.size()!=0){
   		for(it = v_string.begin(); it!=v_string.end(); it++){
	    	cout<<*it;
	    	ct++;
	    	if(ct!=v_string.size()){
	    		cout<<", ";
	    	}
    	} 	
    }
    cout<<")";
    cout<<endl;
    if(d!=NULL){
        tab++;
    	for(auto it :*d){
            it->accept(dvisitor);
        }
        tab--;
    }
    tab++;
    c->accept(dvisitor);
    tab--;

    

}

FunctionNode::~FunctionNode(){
    ;
}

void FunctionNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
