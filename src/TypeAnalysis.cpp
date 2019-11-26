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

void  CollectRefNodeInfo::collect(const std::shared_ptr<TIPtree::Program>& program)
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
  auto tipTypeOps = std::make_shared<TipTypeOps>();
  
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

std::unordered_map<Node*,std::shared_ptr<TipType>> CollectInferResult::getInferResult()
{

}


// Type Analysis
void TypeAnalysis::visitNumExpr(NumberExpr* root)
{
  solver.makeUnion(ast2typevar(root),std::make_shared<TipInt>());
}

void  TypeAnalysis::visitVarExpr(VariableExpr* root)
{

}

void  TypeAnalysis::visitBinaryExpr(BinaryExpr* root)
{
  if(root->OP == "==")
  {
    solver.makeUnion(ast2typevar(root->LHS.get()),ast2typevar(root->RHS.get()));
    solver.makeUnion(ast2typevar(root),std::make_shared<TipInt>());
  }else
  {
    solver.makeUnion(ast2typevar(root->LHS.get()),std::make_shared<TipInt>());
    solver.makeUnion(ast2typevar(root->RHS.get()),std::make_shared<TipInt>());
    solver.makeUnion(ast2typevar(root),std::make_shared<TipInt>());
  }
  visit(root->LHS.get());
  visit(root->RHS.get());
}

void  TypeAnalysis::visitFunAppExpr(FunAppExpr* root)
{


  // visit children
  visit(root->FUN.get());
  for(const auto& actual:root->ACTUALS)
  {
    visit(actual.get());
  }
}

void  TypeAnalysis::visitInputExpr(InputExpr* root)
{
  solver.makeUnion(ast2typevar(root),std::make_shared<TipInt>());
}

void  TypeAnalysis::visitAllocExpr(AllocExpr* root)
{
  solver.makeUnion(ast2typevar(root),std::make_shared<TipRef>(ast2typevar(root->ARG.get())));
  visit(root->ARG.get());
}

void  TypeAnalysis::visitRefExpr(RefExpr* root)
{
  solver.makeUnion(ast2typevar(root),std::make_shared<TipRef>(ast2typevar(root->reference_node.get())));
  // visit children 
  // must run the other analysis first ! 
  visit(root->reference_node.get());
}

void  TypeAnalysis::visitDeRefExpr(DeRefExpr* root)
{
  solver.makeUnion(ast2typevar(root->ARG.get()),std::make_shared<TipRef>(ast2typevar(root)));
  // visit children
  visit(root->ARG.get());
}

void  TypeAnalysis::visitNullExpr(NullExpr* root)
{
  solver.makeUnion(ast2typevar(root),std::make_shared<TipRef>(std::make_shared<TipAlpha>(root)));  
}

void  TypeAnalysis::visitFieldExpr(FieldExpr* root)
{
  visit(root->INIT.get());
}

void  TypeAnalysis::visitRecordExpr(RecordExpr* root)
{
  std::unordered_map<std::string,std::shared_ptr<Term>> a;
  for(const auto& b:root->FIELDS)
  {
    a[b->FIELD] = ast2typevar(b->INIT.get());
  }
  for(const auto& field:allFieldNames)
  {
    if(a.find(field) != a.end())
    {
      solver.makeUnion(ast2typevar(root),a[field]);
    }else
    {
      solver.makeUnion(ast2typevar(root),std::make_shared<TipAlpha>(root,field));
    }
  }
  //visit children
  for(const auto& field:root->FIELDS)
  {
    visit(field->INIT.get());
  }
}

void  TypeAnalysis::visitAccessExpr(AccessExpr* root)
{
  std::vector<std::shared_ptr<Term>> new_args;
  for(const auto& fieldName:allFieldNames)
  {
    if(fieldName == root->FIELD)
    {
      // TODO reduce make_shared
      auto temp = std::shared_ptr<AccessExpr>(root);
      new_args.push_back(std::make_shared<TipVar>(std::static_pointer_cast<Node>(temp)));
    }else
    {
      new_args.push_back(std::make_shared<TipAlpha>(root,fieldName));
    }
  }
  // solver.makeUnion(ast2typevar(root->RECORD),std::make_shared<TipRecord>(new_args,allFieldNames));

  // visit(root->RECORD.get());  
}

void  TypeAnalysis::visitDeclaration(DeclStmt* root)
{
  
}

void  TypeAnalysis::visitBlockStmt(BlockStmt* root)
{
  // visit children
  for(const auto& statement:root->STMTS)
  {
    visit(statement.get());
  }
}

void  TypeAnalysis::visitAssignmentStmt(AssignStmt* root)
{
  solver.makeUnion(ast2typevar(root->LHS.get()),ast2typevar(root->RHS.get()));
  // visit children
  // visit RHS first
  visit(root->RHS.get());
  visit(root->LHS.get());
}

void  TypeAnalysis::visitWhileStmt(WhileStmt* root)
{
  solver.makeUnion(ast2typevar(root->COND.get()),std::make_shared<TipInt>());
  visit(root->COND.get());
  visit(root->BODY.get());
}

void  TypeAnalysis::visitIfStmt(IfStmt* root)
{
  solver.makeUnion(ast2typevar(root->COND.get()),std::make_shared<TipInt>());
  // visit children
  visit(root->COND.get());
  visit(root->THEN.get());
  visit(root->ELSE.get());
}

void  TypeAnalysis::visitOutputStmt(OutputStmt* root)
{
  solver.makeUnion(ast2typevar(root->ARG.get()),std::make_shared<TipInt>());
  // visit children
  visit(root->ARG.get());
}

void  TypeAnalysis::visitErrorStmt(ErrorStmt* root)
{
  // visit children
  visit(root->ARG.get());
}

void  TypeAnalysis::visitReturnStmt(ReturnStmt* root)
{
  // visit children
  visit(root->ARG.get());
}

void  TypeAnalysis::visit(Node* root)
{
  return root->accept(this);
}



std::unordered_map<std::shared_ptr<Var>,std::shared_ptr<Term>> TypeAnalysis::analysis(const std::shared_ptr<TIPtree::Program>& program)
{
  // step1 generate constraint
  for(const auto& function:program->FUNCTIONS)
  {
    if(function->NAME == "main")
    {
      // TODO: unify arugment for FORMALS in Main.. 
      if(!function->BODY.empty())
      {
        const auto& back = function->BODY.back();
        if(back->get_type() == ReturnStmt::type())
        {
          solver.makeUnion(ast2typevar(back.get()),std::make_shared<TipInt>());
        }else
        {
          std::cerr << "The last statement of main is not return statement" << "\n";
        }
      }else
      {
          std::cerr << "The statement of main is empty" << "\n";        
      }
    }else
    {
      //TODO: for other function type 

    }
    //TODO: deal with function type

    for(const auto& body:function->BODY)
    {
      visit(body.get());
    }
  }
}


std::shared_ptr<Var> TypeAnalysis::ast2typevar(Node* root)
{
  //TODO: write useful statement on ast2typevar
  return std::make_shared<TipVar>(std::shared_ptr<Node>(root));
}