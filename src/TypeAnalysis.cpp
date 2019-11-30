#include "TypeAnalysis.h"

void  TIPAstVisitorWithEnv::visitNumExpr(std::shared_ptr<NumberExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{

  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitVarExpr(std::shared_ptr<VariableExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitBinaryExpr(std::shared_ptr<BinaryExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitFunAppExpr(std::shared_ptr<FunAppExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitInputExpr(std::shared_ptr<InputExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitAllocExpr(std::shared_ptr<AllocExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitRefExpr(std::shared_ptr<RefExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitDeRefExpr(std::shared_ptr<DeRefExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitNullExpr(std::shared_ptr<NullExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitFieldExpr(std::shared_ptr<FieldExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitRecordExpr(std::shared_ptr<RecordExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitAccessExpr(std::shared_ptr<AccessExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitDeclaration(std::shared_ptr<DeclStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitBlockStmt(std::shared_ptr<BlockStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitAssignmentStmt(std::shared_ptr<AssignStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitWhileStmt(std::shared_ptr<WhileStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitIfStmt(std::shared_ptr<IfStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitOutputStmt(std::shared_ptr<OutputStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitErrorStmt(std::shared_ptr<ErrorStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitReturnStmt(std::shared_ptr<ReturnStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitFunction(std::shared_ptr<Function> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitIdentifierDeclaration(std::shared_ptr<IdentifierDeclaration> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visitIdentifier(std::shared_ptr<Identifier> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitChildren(root,env);
}

void  TIPAstVisitorWithEnv::visit(std::shared_ptr<Node> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  root->accept(*this,env); 
}

void  TIPAstVisitorWithEnv::visitChildren(std::shared_ptr<Node> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
   if(root->get_type() == NumberExpr::type() || 
    root->get_type() == VariableExpr::type() || 
    root->get_type() == InputExpr::type() ||
    root->get_type() == NullExpr::type() ||
    root->get_type() == DeclStmt::type() ||
    root->get_type() == IdentifierDeclaration::type() ||
    root->get_type() == Identifier::type())
  {
    //EMPTY
  }else if(root->get_type() == BinaryExpr::type())
  {
    auto binaryExpr = std::dynamic_pointer_cast<BinaryExpr>(root);
    visit(binaryExpr->LHS,env);
    visit(binaryExpr->RHS,env);
  }else if(root->get_type() == FunAppExpr::type())
  {
    auto funApp = std::dynamic_pointer_cast<FunAppExpr>(root);
    visit(funApp->FUN,env);
    for(auto actual:funApp->ACTUALS)
    {
        visit(actual,env);
    }
  }else if(root->get_type() == AllocExpr::type())
  {
    auto alloc = std::dynamic_pointer_cast<AllocExpr>(root);
    visit(alloc->ARG,env);
  }else if(root->get_type() == RefExpr::type())
  {
    auto refExpr = std::dynamic_pointer_cast<RefExpr>(root);
    visit(refExpr->ARG,env);
  }else if(root->get_type() == DeRefExpr::type())
  {
    auto deRef = std::dynamic_pointer_cast<DeRefExpr>(root);
    visit(deRef->ARG,env);
  }else if(root->get_type() == FieldExpr::type())
  {
    auto fieldExpr = std::dynamic_pointer_cast<FieldExpr>(root);
    visit(fieldExpr->INIT,env);
  }else if(root->get_type() == RecordExpr::type())
  {
    auto recordExpr = std::dynamic_pointer_cast<RecordExpr>(root);
    for(auto field:recordExpr->FIELDS)
    {
      visit(field,env);
    }
  }else if(root->get_type() == AccessExpr::type())
  {
    auto accessExpr = std::dynamic_pointer_cast<AccessExpr>(root);
    visit(accessExpr->RECORD,env);
  }else if(root->get_type() == BlockStmt::type())
  {
    auto blockStmt = std::dynamic_pointer_cast<BlockStmt>(root);
    for(auto statement:blockStmt->STMTS)
    {
      visit(statement,env);
    }
  }else if(root->get_type() == AssignStmt::type())
  {
    auto assignStmt = std::dynamic_pointer_cast<AssignStmt>(root);
    visit(assignStmt->RHS,env);
    visit(assignStmt->LHS,env);
  }else if(root->get_type() == WhileStmt::type())
  {
    auto whileStmt = std::dynamic_pointer_cast<WhileStmt>(root);
    visit(whileStmt->COND,env);
    visit(whileStmt->BODY,env);
  }else if(root->get_type() == IfStmt::type())
  {
    auto ifStmt = std::dynamic_pointer_cast<IfStmt>(root);
    visit(ifStmt->COND,env);
    visit(ifStmt->THEN,env);
    visit(ifStmt->ELSE,env);
  }else if(root->get_type() == OutputStmt::type())
  {
    auto outputStmt = std::dynamic_pointer_cast<OutputStmt>(root);
    visit(outputStmt->ARG,env);
  }else if(root->get_type() == ErrorStmt::type())
  {
    auto errorStmt = std::dynamic_pointer_cast<ErrorStmt>(root);
    visit(errorStmt->ARG,env);
  }else if(root->get_type() == ReturnStmt::type())
  {
    auto returnStmt = std::dynamic_pointer_cast<ReturnStmt>(root);
    visit(returnStmt->ARG,env);
  }else if(root->get_type() == TIPtree::Function::type())
  {
    auto function = std::dynamic_pointer_cast<TIPtree::Function>(root);
    for(auto decl:function->DECLS)
    {
      visit(decl,env);
    }
    for(auto statement:function->BODY)
    {
      visit(statement,env);
    }
  }
}



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
  if(root->get_type() == Identifier::type())
  {
    auto id = std::dynamic_pointer_cast<Identifier>(root);
    return std::make_shared<TipVar>(declData[id]);
  }else
  {
    return std::make_shared<TipVar>(root);
  }
}