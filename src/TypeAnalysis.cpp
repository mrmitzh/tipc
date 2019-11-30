#include "TypeAnalysis.h"

void CollectAppearingFields::calculateResult(std::shared_ptr<TIPtree::Program> program)
{
  for(auto function:program->FUNCTIONS)
  {
    visit(function);
  }
}

std::vector<std::string> CollectAppearingFields::getCalculatedResult()
{
  std::vector<std::string> result;
  for(const auto& str:fields)
  {
    result.push_back(str);
  }
  std::sort(result.begin(),result.end());
  return result;
}

void CollectAppearingFields::visitAccessExpr(std::shared_ptr<AccessExpr> root)
{
  fields.insert(root->FIELD);
  visitChildren(root);
}

void CollectAppearingFields::visitRecordExpr(std::shared_ptr<RecordExpr> root)
{
  std::vector<std::string> new_fields;
  for(auto field:root->FIELDS)
  {
    new_fields.push_back(field->FIELD);
  }
  for(const auto& str:new_fields)
  {
    fields.insert(str);
  }
  visitChildren(root);
}


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
    std::vector<std::shared_ptr<Term>> params;
    for(auto arg:root->ACTUALS)
    {
      params.push_back(ast2typevar(arg));
    }
    solver.unify(ast2typevar(root->FUN),std::make_shared<TipFunction>(params,ast2typevar(root)));
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
  solver.unify(ast2typevar(root),std::make_shared<TipRef>(ast2typevar(root->ARG)));
  // visit children 
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
      new_args.push_back(std::make_shared<TipVar>(root));
    }else
    {
      new_args.push_back(std::make_shared<TipAlpha>(root,fieldName));
    }
  }
  solver.unify(ast2typevar(root->RECORD),std::make_shared<TipRecord>(new_args,allFieldNames));

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

void  TypeAnalysis::visitFunction(std::shared_ptr<Function> root)
{
  if(root->NAME == "main")
  {
    if(!root->BODY.empty())
    {
      auto retStmt = root->BODY.back();
      solver.unify(ast2typevar(retStmt),std::make_shared<TipInt>());
      for(auto arg:root->dummyFORMALS)
      {
        solver.unify(ast2typevar(arg),std::make_shared<TipInt>());
      }
    }
  }
  auto retStmt = root->BODY.back();
  std::vector<std::shared_ptr<Term>> params;
  for(auto arg:root->dummyFORMALS)
  {
    params.push_back(ast2typevar(arg));
  }
  solver.unify(ast2typevar(root),std::make_shared<TipFunction>(params,ast2typevar(retStmt)));
  visitChildren(root);
}

void  TypeAnalysis::visit(std::shared_ptr<Node> root)
{
  root->accept(*this);
}

std::unordered_map<std::shared_ptr<Node>,std::shared_ptr<TipType>> TypeAnalysis::analysis(std::shared_ptr<TIPtree::Program> program)
{
  CollectAppearingFields collectAppearingFields;
  collectAppearingFields.calculateResult(program);
  allFieldNames = collectAppearingFields.getCalculatedResult();

  // dfs to generate constrains
  for(auto function:program->FUNCTIONS)
  {
    visit(function);
  }

  // TODO: collect constains 



}


std::shared_ptr<Var> TypeAnalysis::ast2typevar(std::shared_ptr<Node> root)
{
  return std::make_shared<TipVar>(root);
}