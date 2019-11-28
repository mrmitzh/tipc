#include "TIPtree.h"

using namespace TIPtree;

void  TIPAstVisitor::visitNumExpr(std::shared_ptr<NumberExpr> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitVarExpr(std::shared_ptr<VariableExpr> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitBinaryExpr(std::shared_ptr<BinaryExpr> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitFunAppExpr(std::shared_ptr<FunAppExpr> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitInputExpr(std::shared_ptr<InputExpr> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitAllocExpr(std::shared_ptr<AllocExpr> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitRefExpr(std::shared_ptr<RefExpr> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitDeRefExpr(std::shared_ptr<DeRefExpr> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitNullExpr(std::shared_ptr<NullExpr> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitFieldExpr(std::shared_ptr<FieldExpr> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitRecordExpr(std::shared_ptr<RecordExpr> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitAccessExpr(std::shared_ptr<AccessExpr> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitDeclaration(std::shared_ptr<DeclStmt> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitBlockStmt(std::shared_ptr<BlockStmt> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitAssignmentStmt(std::shared_ptr<AssignStmt> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitWhileStmt(std::shared_ptr<WhileStmt> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitIfStmt(std::shared_ptr<IfStmt> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitOutputStmt(std::shared_ptr<OutputStmt> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitErrorStmt(std::shared_ptr<ErrorStmt> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitReturnStmt(std::shared_ptr<ReturnStmt> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visitFunction(std::shared_ptr<Function> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visit(std::shared_ptr<Node> root)
{
    root->accept(*this);
}


void  TIPAstVisitor::visitChildren(std::shared_ptr<Node> root)
{
  if(root->get_type() == NumberExpr::type() || 
    root->get_type() == VariableExpr::type() || 
    root->get_type() == InputExpr::type() ||
    root->get_type() == NullExpr::type() ||
    root->get_type() == DeclStmt::type())
  {
    //EMPTY
  }else if(root->get_type() == BinaryExpr::type())
  {
    auto binaryExpr = std::dynamic_pointer_cast<BinaryExpr>(root);
    visit(binaryExpr->LHS);
    visit(binaryExpr->RHS);
  }else if(root->get_type() == FunAppExpr::type())
  {
    auto funApp = std::dynamic_pointer_cast<FunAppExpr>(root);
    visit(funApp->FUN);
    for(auto actual:funApp->ACTUALS)
    {
        visit(actual);
    }
  }else if(root->get_type() == AllocExpr::type())
  {
    auto alloc = std::dynamic_pointer_cast<AllocExpr>(root);
    visit(alloc->ARG);
  }else if(root->get_type() == RefExpr::type())
  {
    auto refExpr = std::dynamic_pointer_cast<RefExpr>(root);
    visit(refExpr->ARG);
  }else if(root->get_type() == DeRefExpr::type())
  {
    auto deRef = std::dynamic_pointer_cast<DeRefExpr>(root);
    visit(deRef->ARG);
  }else if(root->get_type() == FieldExpr::type())
  {
    auto fieldExpr = std::dynamic_pointer_cast<FieldExpr>(root);
    visit(fieldExpr->INIT);
  }else if(root->get_type() == RecordExpr::type())
  {
    auto recordExpr = std::dynamic_pointer_cast<RecordExpr>(root);
    for(auto field:recordExpr->FIELDS)
    {
      visit(field);
    }
  }else if(root->get_type() == AccessExpr::type())
  {
    auto accessExpr = std::dynamic_pointer_cast<AccessExpr>(root);
    visit(accessExpr->RECORD);
  }else if(root->get_type() == BlockStmt::type())
  {
    auto blockStmt = std::dynamic_pointer_cast<BlockStmt>(root);
    for(auto statement:blockStmt->STMTS)
    {
      visit(statement);
    }
  }else if(root->get_type() == AssignStmt::type())
  {
    auto assignStmt = std::dynamic_pointer_cast<AssignStmt>(root);
    visit(assignStmt->RHS);
    visit(assignStmt->LHS);
  }else if(root->get_type() == WhileStmt::type())
  {
    auto whileStmt = std::dynamic_pointer_cast<WhileStmt>(root);
    visit(whileStmt->COND);
    visit(whileStmt->BODY);
  }else if(root->get_type() == IfStmt::type())
  {
    auto ifStmt = std::dynamic_pointer_cast<IfStmt>(root);
    visit(ifStmt->COND);
    visit(ifStmt->THEN);
    visit(ifStmt->ELSE);
  }else if(root->get_type() == OutputStmt::type())
  {
    auto outputStmt = std::dynamic_pointer_cast<OutputStmt>(root);
    visit(outputStmt->ARG);
  }else if(root->get_type() == ErrorStmt::type())
  {
    auto errorStmt = std::dynamic_pointer_cast<ErrorStmt>(root);
    visit(errorStmt->ARG);
  }else if(root->get_type() == ReturnStmt::type())
  {
    auto returnStmt = std::dynamic_pointer_cast<ReturnStmt>(root);
    visit(returnStmt->ARG);
  }else if(root->get_type() == TIPtree::Function::type())
  {
    auto function = std::dynamic_pointer_cast<TIPtree::Function>(root);
    for(auto decl:function->DECLS)
    {
      visit(decl);
    }
    for(auto statement:function->BODY)
    {
      visit(statement);
    }
  }
}
