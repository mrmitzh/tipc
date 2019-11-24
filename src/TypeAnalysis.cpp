#include "TypeAnalysis.h"


// CollectRefNodeInfo
void  CollectRefNodeInfo::visitNumExpr(NumberExpr* root)
{

}

void  CollectRefNodeInfo::visitVarExpr(VariableExpr* root)
{

}

void  CollectRefNodeInfo::visitBinaryExpr(BinaryExpr* root)
{

}

void  CollectRefNodeInfo::visitFunAppExpr(FunAppExpr* root)
{

}

void  CollectRefNodeInfo::visitInputExpr(InputExpr* root)
{

}

void  CollectRefNodeInfo::visitAllocExpr(AllocExpr* root)
{

}

void  CollectRefNodeInfo::visitRefExpr(RefExpr* root)
{

}

void  CollectRefNodeInfo::visitDeRefExpr(DeRefExpr* root)
{

}

void  CollectRefNodeInfo::visitNullExpr(NullExpr* root)
{

}

void  CollectRefNodeInfo::visitFieldExpr(FieldExpr* root)
{

}

void  CollectRefNodeInfo::visitRecordExpr(RecordExpr* root)
{

}

void  CollectRefNodeInfo::visitAccessExpr(AccessExpr* root)
{

}

void  CollectRefNodeInfo::visitDeclaration(DeclStmt* root)
{

}

void  CollectRefNodeInfo::visitBlockStmt(BlockStmt* root)
{

}

void  CollectRefNodeInfo::visitAssignmentStmt(AssignStmt* root)
{

}

void  CollectRefNodeInfo::visitWhileStmt(WhileStmt* root)
{

}

void  CollectRefNodeInfo::visitIfStmt(IfStmt* root)
{

}

void  CollectRefNodeInfo::visitOutputStmt(OutputStmt* root)
{

}

void  CollectRefNodeInfo::visitErrorStmt(ErrorStmt* root)
{

}

void  CollectRefNodeInfo::visitReturnStmt(ReturnStmt* root)
{

}

void  CollectRefNodeInfo::visit(Node* root)
{
  return root->accept(this);
}

void  CollectRefNodeInfo::collect(const std::unique_ptr<TIPtree::Program>& program)
{
  for(const auto& function:program->FUNCTIONS)
  {
    namedValues.clear();
    // TODO: collect info
    for(const auto& body:function->BODY)
    {
      visit(body.get());
    }
  }
}

// CollectInferResult

void  CollectInferResult::visitNumExpr(NumberExpr* root) 
{
  auto tipTypeOps = llvm::make_unique<TipTypeOps>();
  
}
void  CollectInferResult::visitVarExpr(VariableExpr* root) {}
void  CollectInferResult::visitBinaryExpr(BinaryExpr* root) {}
void  CollectInferResult::visitFunAppExpr(FunAppExpr* root) {}
void  CollectInferResult::visitInputExpr(InputExpr* root) {}
void  CollectInferResult::visitAllocExpr(AllocExpr* root) {}
void  CollectInferResult::visitRefExpr(RefExpr* root) {}
void  CollectInferResult::visitDeRefExpr(DeRefExpr* root) {}
void  CollectInferResult::visitNullExpr(NullExpr* root) {}
void  CollectInferResult::visitFieldExpr(FieldExpr* root) {}
void  CollectInferResult::visitRecordExpr(RecordExpr* root) {}
void  CollectInferResult::visitAccessExpr(AccessExpr* root) {}
void  CollectInferResult::visitDeclaration(DeclStmt* root) 
{

}
void  CollectInferResult::visitBlockStmt(BlockStmt* root) {}
void  CollectInferResult::visitAssignmentStmt(AssignStmt* root) {}
void  CollectInferResult::visitWhileStmt(WhileStmt* root) {}
void  CollectInferResult::visitIfStmt(IfStmt* root) {}
void  CollectInferResult::visitOutputStmt(OutputStmt* root) {}
void  CollectInferResult::visitErrorStmt(ErrorStmt* root) {}
void  CollectInferResult::visitReturnStmt(ReturnStmt* root) {}

void  CollectInferResult::visit(Node* root) 
{
  root->accept(this);
}

std::unordered_map<Node*,std::unique_ptr<TipType>> CollectInferResult::getInferResult()
{

}


// Type Analysis
void TypeAnalysis::visitNumExpr(NumberExpr* root)
{
  solver.makeUnion(ast2typevar(root),llvm::make_unique<TipInt>());
}

void  TypeAnalysis::visitVarExpr(VariableExpr* root)
{

}

void  TypeAnalysis::visitBinaryExpr(BinaryExpr* root)
{
  if(root->OP == "==")
  {
    solver.makeUnion(ast2typevar(root->LHS.get()),ast2typevar(root->RHS.get()));
    solver.makeUnion(ast2typevar(root),llvm::make_unique<TipInt>());
  }else
  {
    solver.makeUnion(ast2typevar(root->LHS.get()),llvm::make_unique<TipInt>());
    solver.makeUnion(ast2typevar(root->RHS.get()),llvm::make_unique<TipInt>());
    solver.makeUnion(ast2typevar(root),llvm::make_unique<TipInt>());
  }
}

void  TypeAnalysis::visitFunAppExpr(FunAppExpr* root)
{

}

void  TypeAnalysis::visitInputExpr(InputExpr* root)
{
  solver.makeUnion(ast2typevar(root),llvm::make_unique<TipInt>());
}

void  TypeAnalysis::visitAllocExpr(AllocExpr* root)
{
  solver.makeUnion(ast2typevar(root),llvm::make_unique<TipRef>(ast2typevar(root->ARG.get())));
}

void  TypeAnalysis::visitRefExpr(RefExpr* root)
{

}

void  TypeAnalysis::visitDeRefExpr(DeRefExpr* root)
{

}

void  TypeAnalysis::visitNullExpr(NullExpr* root)
{

}
void  TypeAnalysis::visitFieldExpr(FieldExpr* root)
{

}
void  TypeAnalysis::visitRecordExpr(RecordExpr* root)
{

}

void  TypeAnalysis::visitAccessExpr(AccessExpr* root)
{

}

void  TypeAnalysis::visitDeclaration(DeclStmt* root)
{

}

void  TypeAnalysis::visitBlockStmt(BlockStmt* root)
{
  for(const auto& statement:root->STMTS)
  {
    visit(statement.get());
  }
}

void  TypeAnalysis::visitAssignmentStmt(AssignStmt* root)
{
  solver.makeUnion(ast2typevar(root->LHS.get()),ast2typevar(root->RHS.get()));
}

void  TypeAnalysis::visitWhileStmt(WhileStmt* root)
{
  solver.makeUnion(ast2typevar(root->COND.get()),llvm::make_unique<TipInt>());
  visit(root->BODY.get());
}

void  TypeAnalysis::visitIfStmt(IfStmt* root)
{
  solver.makeUnion(ast2typevar(root->COND.get()),llvm::make_unique<TipInt>());
  visit(root->THEN.get());
  visit(root->ELSE.get());
}

void  TypeAnalysis::visitOutputStmt(OutputStmt* root)
{
  solver.makeUnion(ast2typevar(root->ARG.get()),llvm::make_unique<TipInt>());
}

void  TypeAnalysis::visitErrorStmt(ErrorStmt* root)
{
  // EMPTY
}

void  TypeAnalysis::visitReturnStmt(ReturnStmt* root)
{
  // EMPTY
}

void  TypeAnalysis::visit(Node* root)
{
  return root->accept(this);
}



std::unordered_map<std::unique_ptr<Var>,std::unique_ptr<Term>> TypeAnalysis::analysis(const std::unique_ptr<TIPtree::Program>& program)
{
  // step1 generate constraint
  for(const auto& function:program->FUNCTIONS)
  {
    for(const auto& body:function->BODY)
    {
      visit(body.get());
    }
  }
  
  // 
}


std::unique_ptr<Var> TypeAnalysis::ast2typevar(Node* root)
{
  return std::unique_ptr<Var>();
}