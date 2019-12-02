#include "TIPtreeBuild.h"
#include <vector>

using namespace antlrcpp;

using namespace TIPtree;

TIPtreeBuild::TIPtreeBuild(TIPParser *p) : parser{p} {}

/*
 * Questions:
 *   ? when exactly do I need to use std::move
 *   ? seems like Kaleidoscope is using it too frequently
 *        (in ctor and in ctor invocatin)
 */

std::string TIPtreeBuild::opString(int op) {
  std::string opStr;
  switch (op) {
  case TIPParser::MUL:
    opStr = "*";
    break;
  case TIPParser::DIV:
    opStr = "/";
    break;
  case TIPParser::ADD:
    opStr = "+";
    break;
  case TIPParser::SUB:
    opStr = "-";
    break;
  case TIPParser::GT:
    opStr = ">";
    break;
  case TIPParser::EQ:
    opStr = "==";
    break;
  default:
    std::runtime_error(
        "unknown operator :" +
        TIPtreeBuild::parser->getVocabulary().getLiteralName(op));
  }
  return opStr;
}

/*
 * Globals for communicating information up from visited subtrees
 * These are overwritten by every visit call.
 * We use multiple variables here since downcasting of unique smart pointers
 * is not supported.
 */
static std::shared_ptr<Stmt> visitedStmt = nullptr;
static std::shared_ptr<DeclStmt> visitedDeclStmt = nullptr;
static std::shared_ptr<Expr> visitedExpr = nullptr;
static std::shared_ptr<FieldExpr> visitedFieldExpr = nullptr;
static std::shared_ptr<Function> visitedFunction = nullptr;

/**********************************************************************
 * These methods override selected methods in the TIPBaseVisitor.
 *
 * For each rule name in an ANTLR4 grammar a visit method and a
 * "context" class is generated.  The visit methods are defined in
 * TIPBaseVisitor.h and the context classes in TIPParser.h
 *
 * Only the methods for grammar rules that "directly" contain
 * content that must be processed need to be overridden.  For example,
 * for strings that match "program" you need to process the list of
 * functions.
 *
 * If you are new to visitors, it is very important to understand
 * that since you are selectively overriding methods you cannot
 * rely on the call stack to return values (since the values will
 * be lost by the methods you don't override).  Instead you must create
 * your own structure that is local to the visitor to communicate between
 * the calls during the visit.  In the case of this visitor it is the
 * visitedX variables above.
 *
 * Note that the visit methods are required to return a value, but
 * we make no use of that value, so we simply return the empty string ("")
 * since we cannot return a nullptr (leads to a crash in the visitor).
 *
 * Consult context class definitions to understand the type definitions
 * of the fields that contain the program elements captured during the parse.
 * You will access these from the method overrides in your visitor.
 *
 * Note that we use llvm::make_unique here instead of std::make_unique
 * to have a bit of consistency with the other parts of the compiler
 * that interact with LLVM and are thus constrained to C++ 11.
 */

std::shared_ptr<TIPtree::Program> TIPtreeBuild::build(TIPParser::ProgramContext *ctx) {
  std::vector<std::shared_ptr<Function>> pFunctions;
  for (auto fn : ctx->function()) {
    visit(fn);
    pFunctions.push_back(std::move(visitedFunction));
  }
  return std::make_shared<Program>(std::move(pFunctions));
}

Any TIPtreeBuild::visitFunction(TIPParser::FunctionContext *ctx) {
  std::string fName; // always initialized in the "count == 0" case
  std::vector<std::string> fParams;
  std::vector<std::shared_ptr<DeclStmt>> fDecls;
  std::vector<std::shared_ptr<Stmt>> fBody;
  int fLine;

  /*
   * The structure of the g4 grammar causes the names of the function
   * and the formal parameters to be collected into a single vector
   * named IDENTIFIER.  Consequently, we special case the iteration
   * over that vector.
   */
  bool firstId = true;
  for (auto id : ctx->IDENTIFIER()) {
    if (firstId) {
      firstId = !firstId;
      fName = id->getText();
      fLine = id->getSymbol()->getLine();
    } else {
      fParams.push_back(std::move(id->getText()));
    }
  }

  for (auto decl : ctx->declaration()) {
    visit(decl);
    fDecls.push_back(std::move(visitedDeclStmt));
  }

  for (auto stmt : ctx->statement()) {
    visit(stmt);
    fBody.push_back(std::move(visitedStmt));
  }

  // return statement is always the last statement in a TIP function body
  visit(ctx->returnStmt());
  fBody.push_back(std::move(visitedStmt));

  visitedFunction = std::make_shared<Function>(
      fName, std::move(fParams), std::move(fDecls), std::move(fBody), fLine);
  return "";
}

Any TIPtreeBuild::visitNegNumber(TIPParser::NegNumberContext *ctx) {
  int val = std::stoi(ctx->NUMBER()->getText());
  val = -val;
  visitedExpr = std::make_shared<NumberExpr>(val);
  return "";
}

/*
 * Unfortunately, the context types for binary expressions generated
 * by ANTLR are not organized into a sub-type hierarchy.  If they were
 * we could have a single method to construct binary expression nodes,
 * but as it stands we have some repetitive code to handle the different
 * context types.
 *
 * This might be improved by restructuring the grammar, but then another
 * mechanism for handling operator precedence would be needed.
 */
Any TIPtreeBuild::visitAdditiveExpr(TIPParser::AdditiveExprContext *ctx) {
  std::string op = opString(ctx->op->getType());

  visit(ctx->expr(0));
  std::shared_ptr<Expr> lhs = std::move(visitedExpr);

  visit(ctx->expr(1));
  std::shared_ptr<Expr> rhs = std::move(visitedExpr);

  visitedExpr =
      std::make_shared<BinaryExpr>(op, std::move(lhs), std::move(rhs));
  return "";
}

Any TIPtreeBuild::visitRelationalExpr(TIPParser::RelationalExprContext *ctx) {
  std::string op = opString(ctx->op->getType());

  visit(ctx->expr(0));
  std::shared_ptr<Expr> lhs = std::move(visitedExpr);

  visit(ctx->expr(1));
  std::shared_ptr<Expr> rhs = std::move(visitedExpr);

  visitedExpr =
      std::make_shared<BinaryExpr>(op, std::move(lhs), std::move(rhs));
  return "";
}

Any TIPtreeBuild::visitMultiplicativeExpr(
    TIPParser::MultiplicativeExprContext *ctx) {
  std::string op = opString(ctx->op->getType());

  visit(ctx->expr(0));
  std::shared_ptr<Expr> lhs = std::move(visitedExpr);

  visit(ctx->expr(1));
  std::shared_ptr<Expr> rhs = std::move(visitedExpr);

  visitedExpr =
      std::make_shared<BinaryExpr>(op, std::move(lhs), std::move(rhs));
  return "";
}

Any TIPtreeBuild::visitEqualityExpr(TIPParser::EqualityExprContext *ctx) {
  std::string op = opString(ctx->op->getType());

  visit(ctx->expr(0));
  std::shared_ptr<Expr> lhs = std::move(visitedExpr);

  visit(ctx->expr(1));
  std::shared_ptr<Expr> rhs = std::move(visitedExpr);

  visitedExpr =
      std::make_shared<BinaryExpr>(op, std::move(lhs), std::move(rhs));
  return "";
}

Any TIPtreeBuild::visitParenExpr(TIPParser::ParenExprContext *ctx) {
  visit(ctx->expr());
  // leave visitedExpr from expr unchanged
  return "";
}

Any TIPtreeBuild::visitNumExpr(TIPParser::NumExprContext *ctx) {
  int val = std::stoi(ctx->NUMBER()->getText());
  visitedExpr = std::make_shared<NumberExpr>(val);
  return "";
}

Any TIPtreeBuild::visitIdExpr(TIPParser::IdExprContext *ctx) {
  std::string name = ctx->IDENTIFIER()->getText();
  visitedExpr = std::make_shared<VariableExpr>(name);
  return "";
}

Any TIPtreeBuild::visitInputExpr(TIPParser::InputExprContext *ctx) {
  visitedExpr = std::make_shared<InputExpr>();
  return "";
}

Any TIPtreeBuild::visitFunAppExpr(TIPParser::FunAppExprContext *ctx) {
  std::shared_ptr<Expr> fExpr = nullptr;
  std::vector<std::shared_ptr<Expr>> fArgs;

  // function determined by name or computed expression
  if (ctx->IDENTIFIER() != nullptr) {
    std::string name = ctx->IDENTIFIER()->getText();
    fExpr = std::make_shared<VariableExpr>(name);
  } else if (ctx->parenExpr() != nullptr) {
    visit(ctx->parenExpr());
    fExpr = std::move(visitedExpr);
  } else {
    // one of these alternative must be defined
    assert(false);
  }

  for (auto e : ctx->expr()) {
    visit(e);
    fArgs.push_back(std::move(visitedExpr));
  }

  visitedExpr =
      std::make_shared<FunAppExpr>(std::move(fExpr), std::move(fArgs));
  return "";
}

Any TIPtreeBuild::visitAllocExpr(TIPParser::AllocExprContext *ctx) {
  visit(ctx->expr());
  visitedExpr = std::make_shared<AllocExpr>(std::move(visitedExpr));
  return "";
}

Any TIPtreeBuild::visitRefExpr(TIPParser::RefExprContext *ctx) {
  std::string vName = ctx->IDENTIFIER()->getText();
  int line = ctx->IDENTIFIER()->getSymbol()->getLine();
  visitedExpr = std::make_shared<RefExpr>(vName,std::make_shared<Identifier>(vName,line));
  return "";
}

Any TIPtreeBuild::visitDeRefExpr(TIPParser::DeRefExprContext *ctx) {
  visit(ctx->atom());
  visitedExpr = std::make_shared<DeRefExpr>(std::move(visitedExpr));
  return "";
}

Any TIPtreeBuild::visitNullExpr(TIPParser::NullExprContext *ctx) {
  visitedExpr = std::make_shared<NullExpr>();
  return "";
}

Any TIPtreeBuild::visitRecordExpr(TIPParser::RecordExprContext *ctx) {
  std::vector<std::shared_ptr<FieldExpr>> rFields;
  for (auto fn : ctx->fieldExpr()) {
    visit(fn);
    rFields.push_back(std::move(visitedFieldExpr));
  }

  visitedExpr = std::make_shared<RecordExpr>(std::move(rFields));
  return "";
}

Any TIPtreeBuild::visitFieldExpr(TIPParser::FieldExprContext *ctx) {
  std::string fName = ctx->IDENTIFIER()->getText();
  visit(ctx->expr());
  visitedFieldExpr =
      std::make_shared<FieldExpr>(fName, std::move(visitedExpr));
  return "";
}

Any TIPtreeBuild::visitAccessExpr(TIPParser::AccessExprContext *ctx) {
  std::shared_ptr<Expr> rExpr = nullptr;
  std::string fName; // will be initialized below based on record expr

  // If the base of the access is an identifier, then there will be two
  // elements in the IDENTIFIER vector in this context.
  if (ctx->IDENTIFIER().size() == 2) {
    std::string rName = ctx->IDENTIFIER(0)->getText();
    rExpr = std::make_shared<VariableExpr>(rName);
  } else if (ctx->deRefExpr() != nullptr) {
    visit(ctx->deRefExpr());
    rExpr = std::move(visitedExpr);
  } else if (ctx->parenExpr() != nullptr) {
    visit(ctx->parenExpr());
    rExpr = std::move(visitedExpr);
  } else {
    // one of these alternative must be defined
    assert(false);
  }

  fName = ctx->IDENTIFIER(ctx->IDENTIFIER().size() - 1)->getText();

  visitedExpr = std::make_shared<AccessExpr>(std::move(rExpr), fName);
  return "";
}

Any TIPtreeBuild::visitAssignableExpr(TIPParser::AssignableExprContext *ctx) {
  if (ctx->IDENTIFIER() != nullptr) {
    std::string aName = ctx->IDENTIFIER()->getText();
    visitedExpr = std::make_shared<VariableExpr>(aName);
  } else if (ctx->deRefExpr() != nullptr) {
    visit(ctx->deRefExpr());
    // leave visitedExpr from deRefExpr unchanged
  } else {
    // one of these alternative must be defined
    assert(false);
  }
  return "";
}

Any TIPtreeBuild::visitDeclaration(TIPParser::DeclarationContext *ctx) {
  std::vector<std::string> dVars;
  int dLine = -1;
  for (auto id : ctx->IDENTIFIER()) {
    dLine = id->getSymbol()->getLine();
    dVars.push_back(std::move(id->getText()));
  }
  std::cout << "-----" << "\n";
  std::cout << dLine << "\n";
  for (auto text:dVars)
  {
    std::cout << text << "\n";
  }
  std::cout << "-----" << "\n";
  visitedDeclStmt = std::make_shared<DeclStmt>(std::move(dVars), dLine);
  return "";
}

Any TIPtreeBuild::visitAssignmentStmt(TIPParser::AssignmentStmtContext *ctx) {
  visit(ctx->assignableExpr());
  std::shared_ptr<Expr> lhs = std::move(visitedExpr);
  visit(ctx->expr());
  std::shared_ptr<Expr> rhs = std::move(visitedExpr);
  visitedStmt = std::make_shared<AssignStmt>(std::move(lhs), std::move(rhs));
  return "";
}

Any TIPtreeBuild::visitBlockStmt(TIPParser::BlockStmtContext *ctx) {
  std::vector<std::shared_ptr<Stmt>> bStmts;
  for (auto s : ctx->statement()) {
    visit(s);
    bStmts.push_back(std::move(visitedStmt));
  }
  visitedStmt = std::make_shared<BlockStmt>(std::move(bStmts));
  return "";
}

Any TIPtreeBuild::visitWhileStmt(TIPParser::WhileStmtContext *ctx) {
  visit(ctx->expr());
  std::shared_ptr<Expr> cond = std::move(visitedExpr);

  visit(ctx->statement());
  std::shared_ptr<Stmt> body = std::move(visitedStmt);

  visitedStmt = std::make_shared<WhileStmt>(std::move(cond), std::move(body));
  return "";
}

Any TIPtreeBuild::visitIfStmt(TIPParser::IfStmtContext *ctx) {
  visit(ctx->expr());
  std::shared_ptr<Expr> cond = std::move(visitedExpr);

  visit(ctx->statement(0));
  std::shared_ptr<Stmt> thenBody = std::move(visitedStmt);

  // else is optional
  std::shared_ptr<Stmt> elseBody = nullptr;
  if (ctx->statement().size() == 2) {
    visit(ctx->statement(1));
    elseBody = std::move(visitedStmt);
  }

  visitedStmt = std::make_shared<IfStmt>(std::move(cond), std::move(thenBody),
                                          std::move(elseBody));
  return "";
}

Any TIPtreeBuild::visitOutputStmt(TIPParser::OutputStmtContext *ctx) {
  visit(ctx->expr());
  visitedStmt = std::make_shared<OutputStmt>(std::move(visitedExpr));
  return "";
}

Any TIPtreeBuild::visitErrorStmt(TIPParser::ErrorStmtContext *ctx) {
  visit(ctx->expr());
  visitedStmt = std::make_shared<ErrorStmt>(std::move(visitedExpr));
  return "";
}

Any TIPtreeBuild::visitReturnStmt(TIPParser::ReturnStmtContext *ctx) {
  visit(ctx->expr());
  visitedStmt = std::make_shared<ReturnStmt>(std::move(visitedExpr));
  return "";
}
