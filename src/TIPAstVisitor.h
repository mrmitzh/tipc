#pragma once 

#include <memory>
#include "TIPtree.h"


class TIPAstVisitor
{
public:
  // TODO: add Function and Program attached to the syntax tree?? 
  virtual ~TIPTypeAstVisitor() = default;
  virtual void  visitFunction(TIPtree::Function* root) = 0;
  virtual void  visitNumExpr(TIPtree::NumberExpr* root) = 0;
  virtual void  visitVarExpr(TIPtree::VariableExpr* root) = 0;
  virtual void  visitBinaryExpr(TIPtree::BinaryExpr* root) = 0;
  virtual void  visitFunAppExpr(TIPtree::FunAppExpr* root) = 0;
  virtual void  visitInputExpr(TIPtree::InputExpr* root) = 0;
  virtual void  visitAllocExpr(TIPtree::AllocExpr* root) = 0;
  virtual void  visitRefExpr(TIPtree::RefExpr* root) = 0;
  virtual void  visitDeRefExpr(TIPtree::DeRefExpr* root) = 0;
  virtual void  visitNullExpr(TIPtree::NullExpr* root) = 0;
  virtual void  visitFieldExpr(TIPtree::FieldExpr* root) = 0;
  virtual void  visitRecordExpr(TIPtree::RecordExpr* root) = 0;
  virtual void  visitAccessExpr(TIPtree::AccessExpr* root) = 0;
  virtual void  visitDeclaration(TIPtree::DeclStmt* root) = 0;
  virtual void  visitBlockStmt(TIPtree::BlockStmt* root) = 0;
  virtual void  visitAssignmentStmt(TIPtree::AssignStmt* root) = 0;
  virtual void  visitWhileStmt(TIPtree::WhileStmt* root) = 0;
  virtual void  visitIfStmt(TIPtree::IfStmt* root) = 0;
  virtual void  visitOutputStmt(TIPtree::OutputStmt* root) = 0;
  virtual void  visitErrorStmt(TIPtree::ErrorStmt* root) = 0;
  virtual void  visitReturnStmt(TIPtree::ReturnStmt* root) = 0;
};

class TIPTypeAstVisitor:public TIPTypeAstVisitor
{
  void  visitFunction(TIPtree::Function* root)  override;
  void  visitNumExpr(TIPtree::NumberExpr* root)  override;
  void  visitVarExpr(TIPtree::VariableExpr* root) override;
  void  visitBinaryExpr(TIPtree::BinaryExpr* root) override;
  void  visitFunAppExpr(TIPtree::FunAppExpr* root) override;
  void  visitInputExpr(TIPtree::InputExpr* root) override;
  void  visitAllocExpr(TIPtree::AllocExpr* root) override;
  void  visitRefExpr(TIPtree::RefExpr* root) override;
  void  visitDeRefExpr(TIPtree::DeRefExpr* root) override;
  void  visitNullExpr(TIPtree::NullExpr* root) override;
  void  visitFieldExpr(TIPtree::FieldExpr* root) override;
  void  visitRecordExpr(TIPtree::RecordExpr* root) override;
  void  visitAccessExpr(TIPtree::AccessExpr* root) override;
  void  visitDeclaration(TIPtree::DeclStmt* root) override;
  void  visitBlockStmt(TIPtree::BlockStmt* root) override;
  void  visitAssignmentStmt(TIPtree::AssignStmt* root) override;
  void  visitWhileStmt(TIPtree::WhileStmt* root) override;
  void  visitIfStmt(TIPtree::IfStmt* root) override;
  void  visitOutputStmt(TIPtree::OutputStmt* root) override;
  void  visitErrorStmt(TIPtree::ErrorStmt* root) override;
  void  visitReturnStmt(TIPtree::ReturnStmt* root) override;
};
