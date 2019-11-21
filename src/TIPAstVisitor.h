#pragma once 

#include <memory>
#include "TIPtree.h"


class TIPAstVisitor
{
public:
  // TODO: check if we add all the ast node in visitor.. 
  void  visitFunction(std::unique_ptr<TIPtree::Function> root) override;
  void  visitNumExpr(std::unique_ptr<TIPtree::NumberExpr> root) override;
  void  visitInputExpr(std::unique_ptr<TIPtree::InputExpr> root) override;
  void  visitFunAppExpr(std::unique_ptr<TIPtree::FunAppExpr> root) override;
  void  visitAllocExpr(std::unique_ptr<TIPtree::AllocExpr> root) override;
  void  visitRefExpr(std::unique_ptr<TIPtree::RefExpr> root) override;
  void  visitDeRefExpr(std::unique_ptr<TIPtree::DeRefExpr> root) override;
  void  visitNullExpr(std::unique_ptr<TIPtree::NullExpr> root) override;
  void  visitRecordExpr(std::unique_ptr<TIPtree::RecordExpr> root) override;
  void  visitFieldExpr(std::unique_ptr<TIPtree::FieldExpr> root) override;
  void  visitAccessExpr(std::unique_ptr<TIPtree::AccessExpr> root) override;
  void  visitAssignableExpr(std::unique_ptr<TIPtree::AssignStmt> root) override;
  void  visitDeclaration(std::unique_ptr<TIPtree::DeclStmt> root) override;
  void  visitAssignmentStmt(std::unique_ptr<TIPtree::AssignStmt> root) override;
  void  visitBlockStmt(std::unique_ptr<TIPtree::BlockStmt> root) override;
  void  visitWhileStmt(std::unique_ptr<TIPtree::WhileStmt> root) override;
  void  visitIfStmt(std::unique_ptr<TIPtree::IfStmt> root) override;
  void  visitOutputStmt(std::unique_ptr<TIPtree::OutputStmt> root) override;
  void  visitErrorStmt(std::unique_ptr<TIPtree::ErrorStmt> root) override;
  void  visitReturnStmt(std::unique_ptr<TIPtree::ReturnStmt> root) override;

};