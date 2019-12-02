// #pragma once

#include <unordered_map>
#include "TIPtree.h"
#include "TIPtype.h"
#include "UnionFindSolver.h"


class CollectAppearingFields: public TIPAstVisitor
{
private:
  std::unordered_set<std::string> fields;
public:
  CollectAppearingFields() = default;
  ~CollectAppearingFields() = default;

  void visitAccessExpr(std::shared_ptr<AccessExpr> root) override;
  void visitRecordExpr(std::shared_ptr<RecordExpr> root) override;


  void calculateResult(std::shared_ptr<TIPtree::Program> program);
  std::vector<std::string> getCalculatedResult();
};

class CollectSolution: public TIPAstVisitor
{
private:
  std::unordered_map<std::shared_ptr<Node>,std::shared_ptr<TipType>> ret;
  std::unordered_map<std::shared_ptr<Var>,std::shared_ptr<Term>> sol;
public:
  CollectSolution(std::unordered_map<std::shared_ptr<Var>,std::shared_ptr<Term>> sol)
    :sol(sol)
  {}
  ~CollectSolution() = default;

  void  visitNumExpr(std::shared_ptr<NumberExpr> root) override;
  void  visitVarExpr(std::shared_ptr<VariableExpr> root) override;
  void  visitBinaryExpr(std::shared_ptr<BinaryExpr> root) override;
  void  visitFunAppExpr(std::shared_ptr<FunAppExpr> root) override;
  void  visitInputExpr(std::shared_ptr<InputExpr> root) override;
  void  visitAllocExpr(std::shared_ptr<AllocExpr> root) override;
  void  visitRefExpr(std::shared_ptr<RefExpr> root) override;
  void  visitDeRefExpr(std::shared_ptr<DeRefExpr> root) override;
  void  visitNullExpr(std::shared_ptr<NullExpr> root) override;
  void  visitFieldExpr(std::shared_ptr<FieldExpr> root) override;
  void  visitRecordExpr(std::shared_ptr<RecordExpr> root) override;
  void  visitAccessExpr(std::shared_ptr<AccessExpr> root) override;
  void  visitDeclaration(std::shared_ptr<DeclStmt> root) override;
  void  visitBlockStmt(std::shared_ptr<BlockStmt> root) override;
  void  visitAssignmentStmt(std::shared_ptr<AssignStmt> root) override;
  void  visitWhileStmt(std::shared_ptr<WhileStmt> root) override;
  void  visitIfStmt(std::shared_ptr<IfStmt> root) override;
  void  visitOutputStmt(std::shared_ptr<OutputStmt> root) override;
  void  visitErrorStmt(std::shared_ptr<ErrorStmt> root) override;
  void  visitReturnStmt(std::shared_ptr<ReturnStmt> root) override;
  void  visitFunction(std::shared_ptr<Function> root) override;
  void  visitIdentifierDeclaration(std::shared_ptr<IdentifierDeclaration> root) override;
  void  visitIdentifier(std::shared_ptr<Identifier> root) override;

  void collectResult(std::shared_ptr<TIPtree::Program> program);
  std::unordered_map<std::shared_ptr<Node>,std::shared_ptr<TipType>> getCollectedResult();  
};

class TypeAnalysis:public TIPAstVisitor
{
private:
  UnionFindSolver solver;
  bool visitingFromMain = false;
  std::vector<std::string> allFieldNames;
  std::unordered_map<std::shared_ptr<Identifier>, std::shared_ptr<Declaration>> declData;
public:
  TypeAnalysis() = default;
  ~TypeAnalysis() = default;
  void  visitNumExpr(std::shared_ptr<NumberExpr> root) override;
  void  visitVarExpr(std::shared_ptr<VariableExpr> root) override;
  void  visitBinaryExpr(std::shared_ptr<BinaryExpr> root) override;
  void  visitFunAppExpr(std::shared_ptr<FunAppExpr> root) override;
  void  visitInputExpr(std::shared_ptr<InputExpr> root) override;
  void  visitAllocExpr(std::shared_ptr<AllocExpr> root) override;
  void  visitRefExpr(std::shared_ptr<RefExpr> root) override;
  void  visitDeRefExpr(std::shared_ptr<DeRefExpr> root) override;
  void  visitNullExpr(std::shared_ptr<NullExpr> root) override;
  void  visitFieldExpr(std::shared_ptr<FieldExpr> root) override;
  void  visitRecordExpr(std::shared_ptr<RecordExpr> root) override;
  void  visitAccessExpr(std::shared_ptr<AccessExpr> root) override;
  void  visitDeclaration(std::shared_ptr<DeclStmt> root) override;
  void  visitBlockStmt(std::shared_ptr<BlockStmt> root) override;
  void  visitAssignmentStmt(std::shared_ptr<AssignStmt> root) override;
  void  visitWhileStmt(std::shared_ptr<WhileStmt> root) override;
  void  visitIfStmt(std::shared_ptr<IfStmt> root) override;
  void  visitOutputStmt(std::shared_ptr<OutputStmt> root) override;
  void  visitErrorStmt(std::shared_ptr<ErrorStmt> root) override;
  void  visitReturnStmt(std::shared_ptr<ReturnStmt> root) override;
  void  visitFunction(std::shared_ptr<Function> root) override;
  void  visit(std::shared_ptr<Node> root);

  std::unordered_map<std::shared_ptr<Node>,std::shared_ptr<TipType>> analysis(std::shared_ptr<TIPtree::Program> program);

  std::shared_ptr<Var> ast2typevar(std::shared_ptr<Node> root);
};