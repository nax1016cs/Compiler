#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/function.hpp"
#include "AST/declaration.hpp"
#include "AST/compound_statement.hpp"



class ASTNodeVisitorBase;

class ProgramBodyNode : public ASTNodeBase
{
public:
  std::vector<DeclarationNode*>* d;
  std::vector<FunctionNode*>* f;
  CompoundStatementNode*  c;
  ProgramBodyNode(uint32_t line, uint32_t col);
  void printNode();
  ~ProgramBodyNode();
  void accept(ASTNodeVisitorBase &v);
};