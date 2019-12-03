#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/expression.hpp"


class ASTNodeVisitorBase;

class BinaryOperatorNode : public ExpressionNode
{
public:
  std::string name;
  ExpressionNode*e1 ;
  ExpressionNode*e2 ;
  BinaryOperatorNode(uint32_t line, uint32_t col, std::string name, ExpressionNode*e1, ExpressionNode*e2);
  void printNode();
  ~BinaryOperatorNode();
  void accept(ASTNodeVisitorBase &v);
};