#include "visitor/dumpvisitor.hpp"

void DumpVisitor::visit(ProgramNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(DeclarationNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(ConstantValueNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(VariableNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(BinaryOperatorNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(ExpressionNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(FunctionCallNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(VariableReferenceNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(UnaryOperatorNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(PrintNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(ReadNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(AssignmentNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(ReturnNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(StatementNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(FunctionCallStatNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(WhileNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(ForNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(CompoundStatementNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(ElseNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(IfNode *e)
{
    e->printNode();
}

void DumpVisitor::visit(FunctionNode *e)
{
    e->printNode();
}