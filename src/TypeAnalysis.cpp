#include "TypeAnalysis.h"




// Type Analysis
void TypeAnalysis::visitNumExpr(std::shared_ptr<NumberExpr> root)
{
  solver.unify(ast2typevar(root),std::make_shared<TipInt>());
  visitChildren(root);
}

void  TypeAnalysis::visitVarExpr(std::shared_ptr<VariableExpr> root)
{
  visitChildren(root);
}

void  TypeAnalysis::visitBinaryExpr(std::shared_ptr<BinaryExpr> root)
{
  if(root->OP == "==")
  {
    solver.unify(ast2typevar(root->LHS),ast2typevar(root->RHS));
    solver.unify(ast2typevar(root),std::make_shared<TipInt>());
  }else
  {
    solver.unify(ast2typevar(root->LHS),std::make_shared<TipInt>());
    solver.unify(ast2typevar(root->RHS),std::make_shared<TipInt>());
    solver.unify(ast2typevar(root),std::make_shared<TipInt>());
  }
  visitChildren(root);
}

void  TypeAnalysis::visitFunAppExpr(std::shared_ptr<FunAppExpr> root)
{


  // visit children
  visitChildren(root);
}

void  TypeAnalysis::visitInputExpr(std::shared_ptr<InputExpr> root)
{
  solver.unify(ast2typevar(root),std::make_shared<TipInt>());
  visitChildren(root);
}

void  TypeAnalysis::visitAllocExpr(std::shared_ptr<AllocExpr> root)
{
  solver.unify(ast2typevar(root),std::make_shared<TipRef>(ast2typevar(root->ARG)));
  visitChildren(root);
}

void  TypeAnalysis::visitRefExpr(std::shared_ptr<RefExpr> root)
{
  solver.unify(ast2typevar(root),std::make_shared<TipRef>(ast2typevar(root->reference_node)));
  // visit children 
  // must run the other analysis first ! 
  visitChildren(root);
}

void  TypeAnalysis::visitDeRefExpr(std::shared_ptr<DeRefExpr> root)
{
  solver.unify(ast2typevar(root->ARG),std::make_shared<TipRef>(ast2typevar(root)));
  // visit children
  visitChildren(root);
}

void  TypeAnalysis::visitNullExpr(std::shared_ptr<NullExpr> root)
{
  solver.unify(ast2typevar(root),std::make_shared<TipRef>(std::make_shared<TipAlpha>(root)));  
  visitChildren(root);
}

void  TypeAnalysis::visitFieldExpr(std::shared_ptr<FieldExpr> root)
{
  visitChildren(root);
}

void  TypeAnalysis::visitRecordExpr(std::shared_ptr<RecordExpr> root)
{
  std::unordered_map<std::string,std::shared_ptr<Term>> a;
  for(const auto& b:root->FIELDS)
  {
    a[b->FIELD] = ast2typevar(b->INIT);
  }
  for(const auto& field:allFieldNames)
  {
    if(a.find(field) != a.end())
    {
      solver.unify(ast2typevar(root),a[field]);
    }else
    {
      solver.unify(ast2typevar(root),std::make_shared<TipAlpha>(root,field));
    }
  }
  //visit children
  visitChildren(root);
}

void  TypeAnalysis::visitAccessExpr(std::shared_ptr<AccessExpr> root)
{
  std::vector<std::shared_ptr<Term>> new_args;
  for(const auto& fieldName:allFieldNames)
  {
    if(fieldName == root->FIELD)
    {
      // TODO: reduce make_shared
      auto temp = std::shared_ptr<AccessExpr>(root);
      new_args.push_back(std::make_shared<TipVar>(std::static_pointer_cast<Node>(temp)));
    }else
    {
      new_args.push_back(std::make_shared<TipAlpha>(root,fieldName));
    }
  }
  // solver.unify(ast2typevar(root->RECORD),std::make_shared<TipRecord>(new_args,allFieldNames));

  visitChildren(root);
}

void  TypeAnalysis::visitDeclaration(std::shared_ptr<DeclStmt> root)
{
  visitChildren(root);
}

void  TypeAnalysis::visitBlockStmt(std::shared_ptr<BlockStmt> root)
{
  // visit children
  visitChildren(root);
}

void  TypeAnalysis::visitAssignmentStmt(std::shared_ptr<AssignStmt> root)
{
  solver.unify(ast2typevar(root->LHS),ast2typevar(root->RHS));
  // visit children
  // visit RHS first
  visitChildren(root);
}

void  TypeAnalysis::visitWhileStmt(std::shared_ptr<WhileStmt> root)
{
  solver.unify(ast2typevar(root->COND),std::make_shared<TipInt>());
  visitChildren(root);
}

void  TypeAnalysis::visitIfStmt(std::shared_ptr<IfStmt> root)
{
  solver.unify(ast2typevar(root->COND),std::make_shared<TipInt>());
  // visit children
  visitChildren(root);
}

void  TypeAnalysis::visitOutputStmt(std::shared_ptr<OutputStmt> root)
{
  solver.unify(ast2typevar(root->ARG),std::make_shared<TipInt>());
  // visit children
  visitChildren(root);
}

void  TypeAnalysis::visitErrorStmt(std::shared_ptr<ErrorStmt> root)
{
  // visit children
  visitChildren(root);
}

void  TypeAnalysis::visitReturnStmt(std::shared_ptr<ReturnStmt> root)
{
  // visit children
  visitChildren(root);
}

void  TypeAnalysis::visit(std::shared_ptr<Node> root)
{
  root->accept(this);
}

// std::unordered_map<std::shared_ptr<Var>,std::shared_ptr<Term>> TypeAnalysis::analysis(const std::shared_ptr<TIPtree::Program>& program)
// {
  // step1 generate constraint
  // for(const auto& function:program->FUNCTIONS)
  // {
  //   if(function->NAME == "main")
  //   {
  //     // TODO: unify arugment for FORMALS in Main.. 
  //     if(!function->BODY.empty())
  //     {
  //       const auto& back = function->BODY.back();
  //       if(back->get_type() == ReturnStmt::type())
  //       {
  //         solver.unify(ast2typevar(back.get()),std::make_shared<TipInt>());
  //       }else
  //       {
  //         std::cerr << "The last statement of main is not return statement" << "\n";
  //       }
  //     }else
  //     {
  //         std::cerr << "The statement of main is empty" << "\n";        
  //     }
  //   }else
  //   {
  //     //TODO: for other function type 

  //   }
  //   //TODO: deal with function type

  //   for(const auto& body:function->BODY)
  //   {
  //     visit(body.get());
  //   }
  // }
// }


std::shared_ptr<Var> TypeAnalysis::ast2typevar(std::shared_ptr<Node> root)
{
  //TODO: write useful statement on ast2typevar
  return std::make_shared<TipVar>(root);
}