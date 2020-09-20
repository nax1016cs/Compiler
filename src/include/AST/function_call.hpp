#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/expression.hpp"



class ASTNodeVisitorBase;

class FunctionCallNode : public ExpressionNode
{
public:
  std::string name;
  std::vector<ExpressionNode*>* vector_of_exp;
  FunctionCallNode(uint32_t line, uint32_t col,std::vector<ExpressionNode*>* vector_of_exp);
  void printNode();
  ~FunctionCallNode();
  void accept(ASTNodeVisitorBase &v);
};