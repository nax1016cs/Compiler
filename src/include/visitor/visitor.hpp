#pragma once
#include "AST/ast.hpp"
#include "AST/program.hpp"
#include "AST/declaration.hpp"
#include "AST/constant_value.hpp"
#include "AST/variable.hpp"
#include "AST/binary_operator.hpp"
#include "AST/expression.hpp"
#include "AST/function_call.hpp"
#include "AST/variable_reference.hpp"
#include "AST/unary_operator.hpp"
#include "AST/print.hpp"
#include "AST/read.hpp"
#include "AST/assignment.hpp"
#include "AST/return.hpp"
#include "AST/statement.hpp"
#include "AST/function_call_stat.hpp"
#include "AST/while.hpp"
#include "AST/for.hpp"
#include "AST/compound_statement.hpp"













class ASTNodeVisitorBase
{
public:
    virtual void visit(ProgramNode *e) = 0;
	virtual void visit(DeclarationNode *e) =0;
	virtual void visit(ConstantValueNode *e) =0;
	virtual void visit(VariableNode *e) =0;
	virtual void visit(BinaryOperatorNode *e) =0;
	virtual void visit(ExpressionNode *e) =0;
	virtual void visit(FunctionCallNode *e) =0;
	virtual void visit(VariableReferenceNode *e) =0;
	virtual void visit(UnaryOperatorNode *e) =0;
	virtual void visit(PrintNode *e) =0;
	virtual void visit(ReadNode *e) =0;
	virtual void visit(AssignmentNode *e) =0;
	virtual void visit(ReturnNode *e) =0;
	virtual void visit(StatementNode *e) =0;
	virtual void visit(FunctionCallStatNode *e) =0;
	virtual void visit(WhileNode *e) =0;
	virtual void visit(ForNode *e) =0;
	virtual void visit(CompoundStatementNode *e) =0;




	





	
};