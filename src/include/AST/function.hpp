#pragma once
#include <string>
#include "AST/ast.hpp"

class ASTNodeVisitorBase;

class FunctionNode : public ASTNodeBase
{
public:
  std::string name;
  std::string type = "void";
  CompoundStatementNode* c;
  DeclarationNode* d;
  std::vector<std::string> v_string ;
  FunctionNode(uint32_t line, uint32_t col, CompoundStatementNode* c,DeclarationNode* d);
  void printNode();
  ~FunctionNode();
  void accept(ASTNodeVisitorBase &v);
};