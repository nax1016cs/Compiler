#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/declaration.hpp"
#include "AST/compound_statement.hpp"



class ASTNodeVisitorBase;

class FunctionNode : public ASTNodeBase
{
public:
  std::string name;
  std::string type = "void";
  CompoundStatementNode* c;
  std::vector<std::string> v_string ;
  std::vector<DeclarationNode*>* d;
  FunctionNode(uint32_t line, uint32_t col, CompoundStatementNode* c,std::vector<DeclarationNode*>* d);
  void printNode();
  ~FunctionNode();
  void accept(ASTNodeVisitorBase &v);
};