// #pragma once

#include <unordered_map>
#include "TIPtree.h"
#include "TIPtype.h"
#include "UnionFindSolver.h"

// using namespace TIPtree;

// // class CollectRefNodeInfo:public TIPAstVisitor
// // {
// // private:
// //   std::unordered_map<std::string,Node*> namedValues;
// // public:
// //   CollectRefNodeInfo() = default;
// //   ~CollectRefNodeInfo() = default;
// //   virtual void  visitNumExpr(NumberExpr* root) override;
// //   virtual void  visitVarExpr(VariableExpr* root) override;
// //   virtual void  visitBinaryExpr(BinaryExpr* root) override;
// //   virtual void  visitFunAppExpr(FunAppExpr* root) override;
// //   virtual void  visitInputExpr(InputExpr* root) override;
// //   virtual void  visitAllocExpr(AllocExpr* root) override;
// //   virtual void  visitRefExpr(RefExpr* root) override;
// //   virtual void  visitDeRefExpr(DeRefExpr* root) override;
// //   virtual void  visitNullExpr(NullExpr* root) override;
// //   virtual void  visitFieldExpr(FieldExpr* root) override;
// //   virtual void  visitRecordExpr(RecordExpr* root) override;
// //   virtual void  visitAccessExpr(AccessExpr* root) override;
// //   virtual void  visitDeclaration(DeclStmt* root) override;
// //   virtual void  visitBlockStmt(BlockStmt* root) override;
// //   virtual void  visitAssignmentStmt(AssignStmt* root) override;
// //   virtual void  visitWhileStmt(WhileStmt* root) override;
// //   virtual void  visitIfStmt(IfStmt* root) override;
// //   virtual void  visitOutputStmt(OutputStmt* root) override;
// //   virtual void  visitErrorStmt(ErrorStmt* root) override;
// //   virtual void  visitReturnStmt(ReturnStmt* root) override;
// //   virtual void  visit(Node* root) override;
// //   void collect(const std::shared_ptr<TIPtree::Program>& program);
// // };

// // class CollectInferResult:public TIPAstVisitor
// // {
// // private:
// //   std::unordered_map<Node*,std::shared_ptr<TipType>> infer;
// // public:
// //   CollectInferResult() = default;
// //   ~CollectInferResult() = default;
// //   virtual void  visitNumExpr(NumberExpr* root) override;
// //   virtual void  visitVarExpr(VariableExpr* root) override;
// //   virtual void  visitBinaryExpr(BinaryExpr* root) override;
// //   virtual void  visitFunAppExpr(FunAppExpr* root) override;
// //   virtual void  visitInputExpr(InputExpr* root) override;
// //   virtual void  visitAllocExpr(AllocExpr* root) override;
// //   virtual void  visitRefExpr(RefExpr* root) override;
// //   virtual void  visitDeRefExpr(DeRefExpr* root) override;
// //   virtual void  visitNullExpr(NullExpr* root) override;
// //   virtual void  visitFieldExpr(FieldExpr* root) override;
// //   virtual void  visitRecordExpr(RecordExpr* root) override;
// //   virtual void  visitAccessExpr(AccessExpr* root) override;
// //   virtual void  visitDeclaration(DeclStmt* root) override;
// //   virtual void  visitBlockStmt(BlockStmt* root) override;
// //   virtual void  visitAssignmentStmt(AssignStmt* root) override;
// //   virtual void  visitWhileStmt(WhileStmt* root) override;
// //   virtual void  visitIfStmt(IfStmt* root) override;
// //   virtual void  visitOutputStmt(OutputStmt* root) override;
// //   virtual void  visitErrorStmt(ErrorStmt* root) override;
// //   virtual void  visitReturnStmt(ReturnStmt* root) override;
// //   virtual void  visit(Node* root) override;

// //   std::unordered_map<Node*,std::shared_ptr<TipType>> getInferResult(); 
// // };

class TypeAnalysis:public TIPAstVisitor
{
private:
  UnionFindSolver solver;
  // CollectRefNodeInfo info_collector;
  bool visitingFromMain = false;
  std::vector<std::string> allFieldNames;
public:
  TypeAnalysis() = default;
  ~TypeAnalysis() = default;
  virtual void  visitNumExpr(std::shared_ptr<NumberExpr> root) override;
  virtual void  visitVarExpr(std::shared_ptr<VariableExpr> root) override;
  virtual void  visitBinaryExpr(std::shared_ptr<BinaryExpr> root) override;
  virtual void  visitFunAppExpr(std::shared_ptr<FunAppExpr> root) override;
  virtual void  visitInputExpr(std::shared_ptr<InputExpr> root) override;
  virtual void  visitAllocExpr(std::shared_ptr<AllocExpr> root) override;
  virtual void  visitRefExpr(std::shared_ptr<RefExpr> root) override;
  virtual void  visitDeRefExpr(std::shared_ptr<DeRefExpr> root) override;
  virtual void  visitNullExpr(std::shared_ptr<NullExpr> root) override;
  virtual void  visitFieldExpr(std::shared_ptr<FieldExpr> root) override;
  virtual void  visitRecordExpr(std::shared_ptr<RecordExpr> root) override;
  virtual void  visitAccessExpr(std::shared_ptr<AccessExpr> root) override;
  virtual void  visitDeclaration(std::shared_ptr<DeclStmt> root) override;
  virtual void  visitBlockStmt(std::shared_ptr<BlockStmt> root) override;
  virtual void  visitAssignmentStmt(std::shared_ptr<AssignStmt> root) override;
  virtual void  visitWhileStmt(std::shared_ptr<WhileStmt> root) override;
  virtual void  visitIfStmt(std::shared_ptr<IfStmt> root) override;
  virtual void  visitOutputStmt(std::shared_ptr<OutputStmt> root) override;
  virtual void  visitErrorStmt(std::shared_ptr<ErrorStmt> root) override;
  virtual void  visitReturnStmt(std::shared_ptr<ReturnStmt> root) override;
  virtual void  visit(std::shared_ptr<Node> root);

  // std::unordered_map<std::shared_ptr<Node>,std::shared_ptr<TipType>> analysis(const std::shared_ptr<TIPtree::Program>& program);

  std::shared_ptr<Var> ast2typevar(std::shared_ptr<Node> root);
};