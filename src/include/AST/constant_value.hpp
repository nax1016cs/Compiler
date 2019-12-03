#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/expression.hpp"

class ASTNodeVisitorBase;

class ConstantValueNode : public ExpressionNode
{
public:
	std::string name;
	std::string type;
	ConstantValueNode(uint32_t line, uint32_t col, std::string type);
	void printNode();
	~ConstantValueNode();
	void accept(ASTNodeVisitorBase &v);
};