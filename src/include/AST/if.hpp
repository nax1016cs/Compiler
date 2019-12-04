#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/statement.hpp"
#include "AST/expression.hpp"
#include "AST/else.hpp"




class ASTNodeVisitorBase;

class IfNode : public StatementNode
{
public:
  std::vector<StatementNode*> vector_of_stat;
  ExpressionNode* e;
  ElseNode* els;
  IfNode(uint32_t line, uint32_t col, ExpressionNode* e, std::vector<StatementNode*> vector_of_stat, ElseNode* els);
  void printNode();
  ~IfNode();
  void accept(ASTNodeVisitorBase &v);
};