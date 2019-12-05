#pragma once
#include "visitor/visitor.hpp"

class DumpVisitor : public ASTNodeVisitorBase
{
public:
    void visit(ProgramNode *e) override;
    void visit(DeclarationNode *e) override;
    void visit(ConstantValueNode *e) override;
    void visit(VariableNode *e) override;
    void visit(BinaryOperatorNode *e) override;
    void visit(ExpressionNode *e) override;
    void visit(FunctionCallNode *e) override;
    void visit(VariableReferenceNode *e) override;
    void visit(UnaryOperatorNode *e) override;
    void visit(PrintNode *e) override;
    void visit(ReadNode *e) override;
    void visit(AssignmentNode *e) override;
    void visit(ReturnNode *e) override;
    void visit(StatementNode *e) override;
    void visit(FunctionCallStatNode *e) override;
    void visit(WhileNode *e) override;
    void visit(ForNode *e) override;
    void visit(CompoundStatementNode *e) override;
    void visit(ElseNode *e) override;
    void visit(IfNode *e) override;
    void visit(FunctionNode *e) override;
    
    



    



};