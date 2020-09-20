#pragma once
#include <string>
#include <vector>
#include "AST/ast.hpp"
#include "variable.hpp"
#include "constant_value.hpp"


class ASTNodeVisitorBase;

class DeclarationNode : public ASTNodeBase
{
public:
	std::vector<VariableNode*> t;
	ConstantValueNode* cons;
  	DeclarationNode(uint32_t line, uint32_t col, std::vector<VariableNode*> t, ConstantValueNode* cons);
  	void printNode();
  	~DeclarationNode();
  	void accept(ASTNodeVisitorBase &v);
};