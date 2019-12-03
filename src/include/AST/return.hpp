#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/expression.hpp"


class ASTNodeVisitorBase;

class ReturnNode : public ASTNodeBase
{
public:
  ExpressionNode* e;
  ReturnNode(uint32_t line, uint32_t col, ExpressionNode* e);
  void printNode();
  ~ReturnNode();
  void accept(ASTNodeVisitorBase &v);
};