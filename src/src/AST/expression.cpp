#include <iostream>
#include "AST/declaration.hpp"
#include "visitor/visitor.hpp"

using namespace std;

void ExpressionNode::accept(ASTNodeVisitorBase &v){
    v.visit(this);
}
