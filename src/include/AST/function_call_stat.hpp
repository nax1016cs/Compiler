#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/statement.hpp"
#include "AST/expression.hpp"



class ASTNodeVisitorBase;

class FunctionCallStatNode : public StatementNode
{
public:
  std::string name;
  std::vector<ExpressionNode*> vector_of_exp;
  FunctionCallStatNode(uint32_t line, uint32_t col,std::vector<ExpressionNode*> vector_of_exp);
  void printNode();
  ~FunctionCallStatNode();
  void accept(ASTNodeVisitorBase &v);
};