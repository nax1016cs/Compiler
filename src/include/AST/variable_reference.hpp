#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/expression.hpp"


class ASTNodeVisitorBase;

class VariableReferenceNode : public ExpressionNode
{
public:
  std::string name;
  int count = 0;
  ExpressionNode*e ;
  VariableReferenceNode(uint32_t line, uint32_t col, std::string name, ExpressionNode*e );
  void printNode();
  ~VariableReferenceNode();
  void accept(ASTNodeVisitorBase &v);
};