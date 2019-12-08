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

void  TIPAstVisitor::visitIdentifierDeclaration(std::shared_ptr<IdentifierDeclaration> root)
{
    visitChildren(root);
}

void  TIPAstVisitor::visit(std::shared_ptr<Node> root)
{
    root->accept(*this);
}


void  TIPAstVisitor::visitChildren(std::shared_ptr<Node> root)
{
  if(std::dynamic_pointer_cast<NumberExpr>(root) ||
    std::dynamic_pointer_cast<VariableExpr>(root) ||
    std::dynamic_pointer_cast<InputExpr>(root) ||
    std::dynamic_pointer_cast<NullExpr>(root) ||
    std::dynamic_pointer_cast<IdentifierDeclaration>(root))
  {

  }else if(std::dynamic_pointer_cast<DeclStmt>(root))
  {
    auto decl = std::dynamic_pointer_cast<DeclStmt>(root);
    for(auto dummyVar:decl->dummyVars)
    {
      visit(dummyVar);
    }
  }else if(std::dynamic_pointer_cast<BinaryExpr>(root))
  {
    auto binaryExpr = std::dynamic_pointer_cast<BinaryExpr>(root);
    visit(binaryExpr->LHS);
    visit(binaryExpr->RHS);
  }else if(std::dynamic_pointer_cast<FunAppExpr>(root))
  {
    auto funApp = std::dynamic_pointer_cast<FunAppExpr>(root);
    visit(funApp->FUN);
    for(auto actual:funApp->ACTUALS)
    {
        visit(actual);
    }
  }else if(std::dynamic_pointer_cast<AllocExpr>(root))
  {
    auto alloc = std::dynamic_pointer_cast<AllocExpr>(root);
    visit(alloc->ARG);
  }else if(std::dynamic_pointer_cast<RefExpr>(root))
  {
    auto refExpr = std::dynamic_pointer_cast<RefExpr>(root);
    visit(refExpr->ARG);
  }else if(std::dynamic_pointer_cast<DeRefExpr>(root))
  {
    auto deRef = std::dynamic_pointer_cast<DeRefExpr>(root);
    visit(deRef->ARG);
  }else if(std::dynamic_pointer_cast<FieldExpr>(root))
  {
    auto fieldExpr = std::dynamic_pointer_cast<FieldExpr>(root);
    visit(fieldExpr->dummyFIELD);
    visit(fieldExpr->INIT);
  }else if(std::dynamic_pointer_cast<RecordExpr>(root))
  {
    auto recordExpr = std::dynamic_pointer_cast<RecordExpr>(root);
    for(auto field:recordExpr->FIELDS)
    {
      visit(field);
    }
  }else if(std::dynamic_pointer_cast<AccessExpr>(root))
  {
    auto accessExpr = std::dynamic_pointer_cast<AccessExpr>(root);
    visit(accessExpr->dummyFIELD);
    visit(accessExpr->RECORD);
  }else if(std::dynamic_pointer_cast<BlockStmt>(root))
  {
    auto blockStmt = std::dynamic_pointer_cast<BlockStmt>(root);
    for(auto statement:blockStmt->STMTS)
    {
      visit(statement);
    }
  }else if(std::dynamic_pointer_cast<AssignStmt>(root))
  {
    auto assignStmt = std::dynamic_pointer_cast<AssignStmt>(root);
    visit(assignStmt->RHS);
    visit(assignStmt->LHS);
  }else if(std::dynamic_pointer_cast<WhileStmt>(root))
  {
    auto whileStmt = std::dynamic_pointer_cast<WhileStmt>(root);
    visit(whileStmt->COND);
    visit(whileStmt->BODY);
  }else if(std::dynamic_pointer_cast<IfStmt>(root))
  {
    auto ifStmt = std::dynamic_pointer_cast<IfStmt>(root);
    visit(ifStmt->COND);
    if(ifStmt->THEN)
      visit(ifStmt->THEN);
    if(ifStmt->ELSE)
      visit(ifStmt->ELSE);
  }else if(std::dynamic_pointer_cast<OutputStmt>(root))
  {
    auto outputStmt = std::dynamic_pointer_cast<OutputStmt>(root);
    visit(outputStmt->ARG);
  }else if(std::dynamic_pointer_cast<ErrorStmt>(root))
  {
    auto errorStmt = std::dynamic_pointer_cast<ErrorStmt>(root);
    visit(errorStmt->ARG);
  }else if(std::dynamic_pointer_cast<ReturnStmt>(root))
  {
    auto returnStmt = std::dynamic_pointer_cast<ReturnStmt>(root);
    visit(returnStmt->ARG);
  }else if(std::dynamic_pointer_cast<TIPtree::Function>(root))
  {
    auto function = std::dynamic_pointer_cast<TIPtree::Function>(root);
    visit(function->dummyNAME);
    for(auto formal:function->dummyFORMALS)
    {
      visit(formal);
    }
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
