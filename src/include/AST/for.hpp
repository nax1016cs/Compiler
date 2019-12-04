#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/statement.hpp"
#include "AST/expression.hpp"
#include "AST/assignment.hpp"
#include "AST/declaration.hpp"






class ASTNodeVisitorBase;

class ForNode : public StatementNode
{
public:
  std::vector<StatementNode*> vector_of_stat;
  ExpressionNode* e;
  DeclarationNode* d;
  AssignmentNode* a;
  ForNode(uint32_t line, uint32_t col,DeclarationNode* d, AssignmentNode* a, ExpressionNode* e , std::vector<StatementNode*> vector_of_stat);
  void printNode();
  ~ForNode();
  void accept(ASTNodeVisitorBase &v);
};