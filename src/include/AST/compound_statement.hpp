#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/declaration.hpp"
#include "AST/statement.hpp"


class ASTNodeVisitorBase;

class CompoundStatementNode : public StatementNode
{
public:
  std::vector<StatementNode*> vector_of_stat;
  std::vector<DeclarationNode*> vector_of_dec;
  CompoundStatementNode(uint32_t line, uint32_t col, std::vector<DeclarationNode*> vector_of_dec, std::vector<StatementNode*> vector_of_stat);
  void printNode();
  ~CompoundStatementNode();
  void accept(ASTNodeVisitorBase &v);
};