#pragma once
#include <string>
#include "AST/ast.hpp"


class ASTNodeVisitorBase;

class VariableNode : public ASTNodeBase
{
public:
  std::string name;
  std::string type;
  VariableNode(uint32_t line, uint32_t col,std::string type);
  void printNode();
  ~VariableNode();
  void accept(ASTNodeVisitorBase &v);
};