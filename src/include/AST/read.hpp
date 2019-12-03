#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/variable_reference.hpp"



class ASTNodeVisitorBase;

class ReadNode : public ASTNodeBase
{
public:
  VariableReferenceNode *e ;
  ReadNode(uint32_t line, uint32_t col,  VariableReferenceNode*e);
  void printNode();
  ~ReadNode();
  void accept(ASTNodeVisitorBase &v);
};