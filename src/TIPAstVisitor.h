#pragma once 

#include <memory>
#include "TIPtree.h"

using namespace TIPtree;

class TIPAstVisitor
{
public:
  virtual ~TIPAstVisitor() = default;
  virtual void  visitNumExpr(std::shared_ptr<NumberExpr> root);
  virtual void  visitVarExpr(std::shared_ptr<VariableExpr> root);
  virtual void  visitBinaryExpr(std::shared_ptr<BinaryExpr> root);
  virtual void  visitFunAppExpr(std::shared_ptr<FunAppExpr> root);
  virtual void  visitInputExpr(std::shared_ptr<InputExpr> root);
  virtual void  visitAllocExpr(std::shared_ptr<AllocExpr> root);
  virtual void  visitRefExpr(std::shared_ptr<RefExpr> root);
  virtual void  visitDeRefExpr(std::shared_ptr<DeRefExpr> root);
  virtual void  visitNullExpr(std::shared_ptr<NullExpr> root);
  virtual void  visitFieldExpr(std::shared_ptr<FieldExpr> root);
  virtual void  visitRecordExpr(std::shared_ptr<RecordExpr> root);
  virtual void  visitAccessExpr(std::shared_ptr<AccessExpr> root);
  virtual void  visitDeclaration(std::shared_ptr<DeclStmt> root);
  virtual void  visitBlockStmt(std::shared_ptr<BlockStmt> root);
  virtual void  visitAssignmentStmt(std::shared_ptr<AssignStmt> root);
  virtual void  visitWhileStmt(std::shared_ptr<WhileStmt> root);
  virtual void  visitIfStmt(std::shared_ptr<IfStmt> root);
  virtual void  visitOutputStmt(std::shared_ptr<OutputStmt> root);
  virtual void  visitErrorStmt(std::shared_ptr<ErrorStmt> root);
  virtual void  visitReturnStmt(std::shared_ptr<ReturnStmt> root);
  virtual void  visit(std::shared_ptr<Node> root);

private:
  void  visitChildren(std::shared_ptr<NumberExpr> root);
  void  visitChildren(std::shared_ptr<VariableExpr> root);
  void  visitChildren(std::shared_ptr<BinaryExpr> root);
  void  visitChildren(std::shared_ptr<FunAppExpr> root);
  void  visitChildren(std::shared_ptr<InputExpr> root);
  void  visitChildren(std::shared_ptr<AllocExpr> root);
  void  visitChildren(std::shared_ptr<RefExpr> root);
  void  visitChildren(std::shared_ptr<DeRefExpr> root);
  void  visitChildren(std::shared_ptr<NullExpr> root);
  void  visitChildren(std::shared_ptr<FieldExpr> root);
  void  visitChildren(std::shared_ptr<RecordExpr> root);
  void  visitChildren(std::shared_ptr<AccessExpr> root);
  void  visitChildren(std::shared_ptr<DeclStmt> root);
  void  visitChildren(std::shared_ptr<BlockStmt> root);
  void  visitChildren(std::shared_ptr<AssignStmt> root);
  void  visitChildren(std::shared_ptr<WhileStmt> root);
  void  visitChildren(std::shared_ptr<IfStmt> root);
  void  visitChildren(std::shared_ptr<OutputStmt> root);
  void  visitChildren(std::shared_ptr<ErrorStmt> root);
  void  visitChildren(std::shared_ptr<ReturnStmt> root);
};