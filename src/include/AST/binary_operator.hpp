#pragma once
#include <string>
#include "AST/ast.hpp"

class ASTNodeVisitorBase;

class BinaryOperatorNode : public ASTNodeBase
{
public:
  std::string op;
  BinaryOperatorNode(uint32_t line, uint32_t col, std::string op );
  void printNode();
  ~BinaryOperatorNode();
  void accept(ASTNodeVisitorBase &v);
};