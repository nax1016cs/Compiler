#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/statement.hpp"


class ASTNodeVisitorBase;

class AssignmentNode : public StatementNode
{
public:
	VariableReferenceNode * v;
	ExpressionNode * e;
  	AssignmentNode(uint32_t line, uint32_t col,VariableReferenceNode * v ,ExpressionNode * e);
  	void printNode();
  	~AssignmentNode();
  	void accept(ASTNodeVisitorBase &v);
};