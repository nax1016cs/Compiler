#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/expression.hpp"


class ASTNodeVisitorBase;

class FunctionCallNode : public ExpressionNode
{
public:
  FunctionCallNode(uint32_t line, uint32_t col);
  void printNode();
  ~FunctionCallNode();
  void accept(ASTNodeVisitorBase &v);
};