#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"
#include "visitor/dumpvisitor.hpp"
extern int tab;
extern void print_tab(int tab);

using namespace std;
AssignmentNode::AssignmentNode(uint32_t line, uint32_t col, VariableReferenceNode * v_t ,ExpressionNode * e_t): StatementNode(line,col){
	v = v_t;
	e = e_t;
}

void AssignmentNode::printNode(){
    DumpVisitor dvisitor;
    print_tab(tab);
    cout << "assignment statement "<< "<line:" << location.line<<", col:"<< location.col << "> " <<endl;
    tab++;
    v->accept(dvisitor);
    e->accept(dvisitor);
    tab--;


}

AssignmentNode::~AssignmentNode(){
    ;
}

void AssignmentNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
