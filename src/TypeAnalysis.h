#pragma once

#include <unordered_map>
#include "TIPtree.h"
#include "TIPtype.h"
#include "UnionFindSolver.h"

using namespace TIPtree;

class CollectRefNodeInfo:public TIPAstVisitor
{
private:
  std::unordered_map<std::string,Node*> namedValues;
public:
  CollectRefNodeInfo() = default;
  ~CollectRefNodeInfo() = default;
  virtual void  visitNumExpr(NumberExpr* root) override;
  virtual void  visitVarExpr(VariableExpr* root) override;
  virtual void  visitBinaryExpr(BinaryExpr* root) override;
  virtual void  visitFunAppExpr(FunAppExpr* root) override;
  virtual void  visitInputExpr(InputExpr* root) override;
  virtual void  visitAllocExpr(AllocExpr* root) override;
  virtual void  visitRefExpr(RefExpr* root) override;
  virtual void  visitDeRefExpr(DeRefExpr* root) override;
  virtual void  visitNullExpr(NullExpr* root) override;
  virtual void  visitFieldExpr(FieldExpr* root) override;
  virtual void  visitRecordExpr(RecordExpr* root) override;
  virtual void  visitAccessExpr(AccessExpr* root) override;
  virtual void  visitDeclaration(DeclStmt* root) override;
  virtual void  visitBlockStmt(BlockStmt* root) override;
  virtual void  visitAssignmentStmt(AssignStmt* root) override;
  virtual void  visitWhileStmt(WhileStmt* root) override;
  virtual void  visitIfStmt(IfStmt* root) override;
  virtual void  visitOutputStmt(OutputStmt* root) override;
  virtual void  visitErrorStmt(ErrorStmt* root) override;
  virtual void  visitReturnStmt(ReturnStmt* root) override;
  virtual void  visit(Node* root) override;
  void collect(const std::shared_ptr<TIPtree::Program>& program);
};

class CollectInferResult:public TIPAstVisitor
{
private:
  std::unordered_map<Node*,std::shared_ptr<TipType>> infer;
public:
  CollectInferResult() = default;
  ~CollectInferResult() = default;
  virtual void  visitNumExpr(NumberExpr* root) override;
  virtual void  visitVarExpr(VariableExpr* root) override;
  virtual void  visitBinaryExpr(BinaryExpr* root) override;
  virtual void  visitFunAppExpr(FunAppExpr* root) override;
  virtual void  visitInputExpr(InputExpr* root) override;
  virtual void  visitAllocExpr(AllocExpr* root) override;
  virtual void  visitRefExpr(RefExpr* root) override;
  virtual void  visitDeRefExpr(DeRefExpr* root) override;
  virtual void  visitNullExpr(NullExpr* root) override;
  virtual void  visitFieldExpr(FieldExpr* root) override;
  virtual void  visitRecordExpr(RecordExpr* root) override;
  virtual void  visitAccessExpr(AccessExpr* root) override;
  virtual void  visitDeclaration(DeclStmt* root) override;
  virtual void  visitBlockStmt(BlockStmt* root) override;
  virtual void  visitAssignmentStmt(AssignStmt* root) override;
  virtual void  visitWhileStmt(WhileStmt* root) override;
  virtual void  visitIfStmt(IfStmt* root) override;
  virtual void  visitOutputStmt(OutputStmt* root) override;
  virtual void  visitErrorStmt(ErrorStmt* root) override;
  virtual void  visitReturnStmt(ReturnStmt* root) override;
  virtual void  visit(Node* root) override;

  std::unordered_map<Node*,std::shared_ptr<TipType>> getInferResult(); 
};

class TypeAnalysis:public TIPAstVisitor
{
private:
  UnionFindSolver solver;
  CollectRefNodeInfo info_collector;
  bool visitingFromMain = false;
  std::vector<std::string> allFieldNames;
public:
  using result_type = std::unordered_map<Node*,std::shared_ptr<TipType>>;
  TypeAnalysis() = default;
  ~TypeAnalysis() = default;
  virtual void  visitNumExpr(NumberExpr* root) override;
  virtual void  visitVarExpr(VariableExpr* root) override;
  virtual void  visitBinaryExpr(BinaryExpr* root) override;
  virtual void  visitFunAppExpr(FunAppExpr* root) override;
  virtual void  visitInputExpr(InputExpr* root) override;
  virtual void  visitAllocExpr(AllocExpr* root) override;
  virtual void  visitRefExpr(RefExpr* root) override;
  virtual void  visitDeRefExpr(DeRefExpr* root) override;
  virtual void  visitNullExpr(NullExpr* root) override;
  virtual void  visitFieldExpr(FieldExpr* root) override;
  virtual void  visitRecordExpr(RecordExpr* root) override;
  virtual void  visitAccessExpr(AccessExpr* root) override;
  virtual void  visitDeclaration(DeclStmt* root) override;
  virtual void  visitBlockStmt(BlockStmt* root) override;
  virtual void  visitAssignmentStmt(AssignStmt* root) override;
  virtual void  visitWhileStmt(WhileStmt* root) override;
  virtual void  visitIfStmt(IfStmt* root) override;
  virtual void  visitOutputStmt(OutputStmt* root) override;
  virtual void  visitErrorStmt(ErrorStmt* root) override;
  virtual void  visitReturnStmt(ReturnStmt* root) override;
  virtual void  visit(Node* root) override;

  std::unordered_map<std::shared_ptr<Var>,std::shared_ptr<Term>> analysis(const std::shared_ptr<TIPtree::Program>& program);

  std::shared_ptr<Var> ast2typevar(Node* root);
};