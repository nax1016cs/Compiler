#pragma once
#include <string>
#include "AST/ast.hpp"
#include "AST/variable_reference.hpp"
#include "AST/statement.hpp"



class ASTNodeVisitorBase;

class ReadNode : public StatementNode
{
public:
  VariableReferenceNode *e ;
  ReadNode(uint32_t line, uint32_t col,  VariableReferenceNode*e);
  void printNode();
  ~ReadNode();
  void accept(ASTNodeVisitorBase &v);
};