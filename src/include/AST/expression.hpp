#pragma once
#include <string>
#include "AST/ast.hpp"

class ASTNodeVisitorBase;

class ExpressionNode : public ASTNodeBase
{
public:
  void accept(ASTNodeVisitorBase &v);
};