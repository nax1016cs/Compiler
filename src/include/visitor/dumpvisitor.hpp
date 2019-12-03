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

};