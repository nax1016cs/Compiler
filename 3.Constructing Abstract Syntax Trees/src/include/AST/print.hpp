#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/statement.hpp"



class ASTNodeVisitorBase;

class PrintNode : public StatementNode
{
public:
  ExpressionNode*e ;
  PrintNode(uint32_t line, uint32_t col,  ExpressionNode*e);
  void printNode();
  ~PrintNode();
  void accept(ASTNodeVisitorBase &v);
};