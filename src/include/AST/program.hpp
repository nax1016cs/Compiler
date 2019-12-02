#pragma once
#include <string>
#include <vector>
#include "AST/ast.hpp"
#include "AST/declaration.hpp"


class ASTNodeVisitorBase;

class ProgramNode : public ASTNodeBase
{
public:
  std::string name;
  std::vector<DeclarationNode*> vector_of_dec;
  ProgramNode(uint32_t line, uint32_t col,std::vector<DeclarationNode*> vector_of_dec);
  void printNode();
  ~ProgramNode();
  void accept(ASTNodeVisitorBase &v);
};