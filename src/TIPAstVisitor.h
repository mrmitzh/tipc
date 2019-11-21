#pragma once 

#include <memory>
#include "TIPtree.h"


class TIPAstVisitor
{
public:
  // TODO: add Function and Program attached to the syntax tree?? 
  virtual void  visitFunction(std::unique_ptr<TIPtree::Function>& root) = 0;
  virtual void  visitNumExpr(std::unique_ptr<TIPtree::NumberExpr>& root) = 0;
  virtual void  visitVarExpr(std::unique_ptr<TIPtree::VariableExpr>& root) = 0;
  virtual void  visitBinaryExpr(std::unique_ptr<TIPtree::BinaryExpr>& root) = 0;
  virtual void  visitFunAppExpr(std::unique_ptr<TIPtree::FunAppExpr>& root) = 0;
  virtual void  visitInputExpr(std::unique_ptr<TIPtree::InputExpr>& root) = 0;
  virtual void  visitAllocExpr(std::unique_ptr<TIPtree::AllocExpr>& root) = 0;
  virtual void  visitRefExpr(std::unique_ptr<TIPtree::RefExpr>& root) = 0;
  virtual void  visitDeRefExpr(std::unique_ptr<TIPtree::DeRefExpr>& root) = 0;
  virtual void  visitNullExpr(std::unique_ptr<TIPtree::NullExpr>& root) = 0;
  virtual void  visitFieldExpr(std::unique_ptr<TIPtree::FieldExpr>& root) = 0;
  virtual void  visitRecordExpr(std::unique_ptr<TIPtree::RecordExpr>& root) = 0;
  virtual void  visitAccessExpr(std::unique_ptr<TIPtree::AccessExpr>& root) = 0;
  virtual void  visitDeclaration(std::unique_ptr<TIPtree::DeclStmt>& root) = 0;
  virtual void  visitBlockStmt(std::unique_ptr<TIPtree::BlockStmt>& root) = 0;
  virtual void  visitAssignmentStmt(std::unique_ptr<TIPtree::AssignStmt>& root) = 0;
  virtual void  visitWhileStmt(std::unique_ptr<TIPtree::WhileStmt>& root) = 0;
  virtual void  visitIfStmt(std::unique_ptr<TIPtree::IfStmt>& root) = 0;
  virtual void  visitOutputStmt(std::unique_ptr<TIPtree::OutputStmt>& root) = 0;
  virtual void  visitErrorStmt(std::unique_ptr<TIPtree::ErrorStmt>& root) = 0;
  virtual void  visitReturnStmt(std::unique_ptr<TIPtree::ReturnStmt>& root) = 0;
};


