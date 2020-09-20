#pragma once
#include <string>
#include <vector>
#include "AST/ast.hpp"
#include "AST/declaration.hpp"
#include "AST/program_body.hpp"



class ASTNodeVisitorBase;

class ProgramNode : public ASTNodeBase
{
public:
  std::string name;
  ProgramBodyNode*  p;
  ProgramNode(uint32_t line, uint32_t col);
  void printNode();
  ~ProgramNode();
  void accept(ASTNodeVisitorBase &v);
};