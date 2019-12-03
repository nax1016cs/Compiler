#pragma once
#include <string>
#include "AST/ast.hpp"

class ASTNodeVisitorBase;

class AssignmentNode : public ASTNodeBase
{
public:
	VariableReferenceNode * v;
	ExpressionNode * e;
  	AssignmentNode(uint32_t line, uint32_t col,VariableReferenceNode * v ,ExpressionNode * e);
  	void printNode();
  	~AssignmentNode();
  	void accept(ASTNodeVisitorBase &v);
};