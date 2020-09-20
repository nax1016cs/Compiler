#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/statement.hpp"


class ASTNodeVisitorBase;

class ElseNode : public StatementNode
{
public:
  std::vector<StatementNode*>* vector_of_stat;
  ElseNode(uint32_t line, uint32_t col, std::vector<StatementNode*>* vector_of_stat);
  void printNode();
  ~ElseNode();
  void accept(ASTNodeVisitorBase &v);
};