#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/statement.hpp"
#include "AST/expression.hpp"




class ASTNodeVisitorBase;

class WhileNode : public StatementNode
{
public:
  std::vector<StatementNode*> vector_of_stat;
  ExpressionNode* e;
  WhileNode(uint32_t line, uint32_t col, ExpressionNode* e , std::vector<StatementNode*> vector_of_stat);
  void printNode();
  ~WhileNode();
  void accept(ASTNodeVisitorBase &v);
};