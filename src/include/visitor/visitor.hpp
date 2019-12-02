#pragma once
#include "AST/ast.hpp"
#include "AST/program.hpp"
#include "AST/declaration.hpp"
#include "AST/constant_value.hpp"
#include "AST/variable.hpp"
#include "AST/binary_operator.hpp"
#include "AST/expression.hpp"



class ASTNodeVisitorBase
{
public:
    virtual void visit(ProgramNode *e) = 0;
	virtual void visit(DeclarationNode *e) =0;
	virtual void visit(ConstantValueNode *e) =0;
	virtual void visit(VariableNode *e) =0;
	virtual void visit(BinaryOperatorNode *e) =0;
	virtual void visit(ExpressionNode *e) =0;
	
};