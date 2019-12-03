#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/expression.hpp"


class ASTNodeVisitorBase;

class VariableReferenceNode : public ExpressionNode
{
public:
  std::string name;
  int count = 0;
  ExpressionNode*e ;
  std::vector<ExpressionNode*> vector_of_exp_arr; // for arr

  VariableReferenceNode(uint32_t line, uint32_t col, std::string name, std::vector<ExpressionNode*> vector_of_exp_arr );
  void printNode();
  ~VariableReferenceNode();
  void accept(ASTNodeVisitorBase &v);
};