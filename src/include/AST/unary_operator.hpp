#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/expression.hpp"


class ASTNodeVisitorBase;

class UnaryOperatorNode : public ExpressionNode
{
public:
  std::string name;
  ExpressionNode*e ;
  UnaryOperatorNode(uint32_t line, uint32_t col, std::string name, ExpressionNode*e );
  void printNode();
  ~UnaryOperatorNode();
  void accept(ASTNodeVisitorBase &v);
};