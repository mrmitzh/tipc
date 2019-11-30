#pragma once

#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

/******************************************************************
 * Abstract Syntax Tree for TIP
 *****************************************************************/

namespace TIPtree {

class TIPAstVisitor;

// Node - this is a base class for all tree nodes
class Node {
public:
  virtual ~Node() = default;
  virtual llvm::Value *codegen() = 0;
  virtual std::string print() = 0;
  virtual std::string get_type();
  virtual void accept(TIPAstVisitor& visitor) = 0;
};
/******************* Declaration AST Nodes *********************/
class Declaration: public Node
{
public:
  ~Declaration() = default;
};

class IdentifierDeclaration: public Declaration, public std::enable_shared_from_this<IdentifierDeclaration>
{
public:
  std::string value;
  int line;
  IdentifierDeclaration(std::string value,int line):value(value),line(line){};
  ~IdentifierDeclaration() = default;
  static std::string type();
  std::string get_type() override;
  llvm::Value *codegen() override {};
  std::string print() override {};
  void accept(TIPAstVisitor& visitor) override;
};

/******************* Expression AST Nodes *********************/

// Expr - Base class for all expression nodes.
class Expr : public Node {
public:
  ~Expr() = default;
  // delegating the obligation to override the functions
};

// NumberExpr - Expression class for numeric literals
class NumberExpr : public Expr, public std::enable_shared_from_this<NumberExpr>
{
public:
  int VAL;

  NumberExpr(int VAL) : VAL(VAL) {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

/// VariableExpr - class for referencing a variable
class VariableExpr : public Expr, public std::enable_shared_from_this<VariableExpr>
{
public:
  std::string NAME;

  VariableExpr(const std::string &NAME) : NAME(NAME) {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  // Getter to distinguish LHS of assigment for codegen
  std::string getName() { return NAME; };
  void accept(TIPAstVisitor& visitor) override;
};

/// BinaryExpr - class for a binary operator.
class BinaryExpr : public Expr, public std::enable_shared_from_this<BinaryExpr>
{
public:
  std::string OP;
  std::shared_ptr<Expr> LHS, RHS;

  BinaryExpr(const std::string &OP, std::shared_ptr<Expr> LHS,
             std::shared_ptr<Expr> RHS)
      : OP(OP), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

/// FunAppExpr - class for function calls.
class FunAppExpr : public Expr, public std::enable_shared_from_this<FunAppExpr>
{
public:
  std::shared_ptr<Expr> FUN;
  std::vector<std::shared_ptr<Expr>> ACTUALS;

  FunAppExpr(std::shared_ptr<Expr> FUN,
             std::vector<std::shared_ptr<Expr>> ACTUALS)
      : FUN(std::move(FUN)), ACTUALS(std::move(ACTUALS)) {}
  static std::string type();
  std::string get_type() override;
  llvm::Value *codegen() override;
  std::string print() override;
  void accept(TIPAstVisitor& visitor) override;
};

/// InputExpr - class for input expression
class InputExpr : public Expr, public std::enable_shared_from_this<InputExpr>
{

public:
  InputExpr() {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

// AllocExpr - class for alloc expression
class AllocExpr : public Expr, public std::enable_shared_from_this<AllocExpr>
{
public:
  std::shared_ptr<Expr> ARG;

  AllocExpr(std::shared_ptr<Expr> ARG) : ARG(std::move(ARG)) {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

// RefExpr - class for referencing the address of a variable
class RefExpr : public Expr, public std::enable_shared_from_this<RefExpr>
{
public:
  std::string NAME;
  std::shared_ptr<Expr> ARG;

  RefExpr(const std::string &NAME, std::shared_ptr<Expr> ARG) : NAME(NAME),ARG(std::move(ARG)) {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

// DeRefExpr - class for dereferencing a pointer expression
class DeRefExpr : public Expr, public std::enable_shared_from_this<DeRefExpr>
{
public:
  std::shared_ptr<Expr> ARG;

  DeRefExpr(std::shared_ptr<Expr> ARG) : ARG(std::move(ARG)) {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

/// NullExpr - class for a null expression
class NullExpr : public Expr, public std::enable_shared_from_this<NullExpr>
{

public:
  NullExpr() {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

// FieldExpr - class for the field of a structure
class FieldExpr : public Expr, public std::enable_shared_from_this<FieldExpr>
{
public:
  std::string FIELD;
  std::shared_ptr<Expr> INIT;

  FieldExpr(const std::string &FIELD, std::shared_ptr<Expr> INIT)
      : FIELD(FIELD), INIT(std::move(INIT)) {}
  llvm::Value *codegen() override;
  static std::string type();
  std::string get_type() override;
  std::string print() override;
  void accept(TIPAstVisitor& visitor) override;
};

// RecordExpr - class for defining a record
class RecordExpr : public Expr, public std::enable_shared_from_this<RecordExpr>
{
public:
  std::vector<std::shared_ptr<FieldExpr>> FIELDS;

  RecordExpr(std::vector<std::shared_ptr<FieldExpr>> FIELDS)
      : FIELDS(std::move(FIELDS)) {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

// AccessExpr - class for a record field access
class AccessExpr : public Expr, public std::enable_shared_from_this<AccessExpr>
{
public:
  std::shared_ptr<Expr> RECORD;
  std::string FIELD;

  AccessExpr(std::shared_ptr<Expr> RECORD, const std::string &FIELD)
      : RECORD(std::move(RECORD)), FIELD(FIELD) {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

// Identifier
class Identifier: public Expr, public std::enable_shared_from_this<Identifier>
{
public:
  std::string value;
  int line;
  Identifier(std::string value,int line):value(value),line(line){};
  ~Identifier() = default;
  static std::string type();
  std::string get_type() override;
  llvm::Value *codegen() override {};
  std::string print() override {};
  void accept(TIPAstVisitor& visitor) override;
};

/******************* Statement AST Nodes *********************/

// Stmt - Base class for all statement nodes.
class Stmt : public Node {
public:
  ~Stmt() = default;
  // delegating the obligation to override the functions
};

// DeclStmt - class for declaration
class DeclStmt : public Stmt, public std::enable_shared_from_this<DeclStmt>
{
public:
  std::vector<std::string> VARS;
  int LINE; // line on which decl statement occurs

  DeclStmt(std::vector<std::string> VARS, int LINE)
      : VARS(std::move(VARS)), LINE(LINE) {}
  llvm::Value *codegen() override;
  static std::string type();
  std::string get_type() override;
  std::string print() override;
  void accept(TIPAstVisitor& visitor) override;
};

// BlockStmt - class for block of statements
class BlockStmt : public Stmt, public std::enable_shared_from_this<BlockStmt>
{
public:
  std::vector<std::shared_ptr<Stmt>> STMTS;

  BlockStmt(std::vector<std::shared_ptr<Stmt>> STMTS)
      : STMTS(std::move(STMTS)) {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

// AssignStmt - class for assignment
class AssignStmt : public Stmt, public std::enable_shared_from_this<AssignStmt>
{
public:
  std::shared_ptr<Expr> LHS, RHS;

  AssignStmt(std::shared_ptr<Expr> LHS, std::shared_ptr<Expr> RHS)
      : LHS(std::move(LHS)), RHS(std::move(RHS)) {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

// WhileStmt - class for a while loop
class WhileStmt : public Stmt, public std::enable_shared_from_this<WhileStmt>
{
public:
  std::shared_ptr<Expr> COND;
  std::shared_ptr<Stmt> BODY;

  WhileStmt(std::shared_ptr<Expr> COND, std::shared_ptr<Stmt> BODY)
      : COND(std::move(COND)), BODY(std::move(BODY)) {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

/// IfStmt - class for if-then-else
class IfStmt : public Stmt, public std::enable_shared_from_this<IfStmt>
{
public:
  std::shared_ptr<Expr> COND;
  std::shared_ptr<Stmt> THEN, ELSE;

  IfStmt(std::shared_ptr<Expr> COND, std::shared_ptr<Stmt> THEN,
         std::shared_ptr<Stmt> ELSE)
      : COND(std::move(COND)), THEN(std::move(THEN)), ELSE(std::move(ELSE)) {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

/// OutputStmt - class for a output statement
class OutputStmt : public Stmt, public std::enable_shared_from_this<OutputStmt>
{
public:
  std::shared_ptr<Expr> ARG;

  OutputStmt(std::shared_ptr<Expr> ARG) : ARG(std::move(ARG)) {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

/// ErrorStmt - class for a error statement
class ErrorStmt : public Stmt, public std::enable_shared_from_this<ErrorStmt>
{
public:
  std::shared_ptr<Expr> ARG;

  ErrorStmt(std::shared_ptr<Expr> ARG) : ARG(std::move(ARG)) {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

/// ReturnStmt - class for a return statement
class ReturnStmt : public Stmt, public std::enable_shared_from_this<ReturnStmt>
{
public:
  std::shared_ptr<Expr> ARG;

  ReturnStmt(std::shared_ptr<Expr> ARG) : ARG(std::move(ARG)) {}
  llvm::Value *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
};

/******************* Program and Function Nodes *********************/

// Function - signature, local declarations, and a body
class Function: public Expr, public std::enable_shared_from_this<Function>
{
public:
  std::string NAME;
  std::vector<std::string> FORMALS;
  std::vector<std::shared_ptr<DeclStmt>> DECLS;
  std::vector<std::shared_ptr<Stmt>> BODY;
  int LINE; // line on which function definition occurs

  Function(const std::string &NAME, std::vector<std::string> FORMALS,
           std::vector<std::shared_ptr<DeclStmt>> DECLS,
           std::vector<std::shared_ptr<Stmt>> BODY, int LINE)
      : NAME(NAME), FORMALS(std::move(FORMALS)), DECLS(std::move(DECLS)),
        BODY(std::move(BODY)), LINE(LINE) {}
  llvm::Function *codegen() override;
  std::string print() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;

  /*
   * These getters are needed because we perform two passes over
   * functions during code generation:
   *   1) a shallow pass that declares all function signatures
   *   2) a deep pass that generates function implementations
   * The getters support first pass.
   */
  std::string getName() { return NAME; };
  std::vector<std::string> getFormals() { return FORMALS; };
};

// Program - just a list of functions
class Program {
public:
  std::vector<std::shared_ptr<Function>> FUNCTIONS;
  Program(std::vector<std::shared_ptr<Function>> FUNCTIONS)
      : FUNCTIONS(std::move(FUNCTIONS)) {}
  std::unique_ptr<llvm::Module> codegen(std::string programName);
  std::string print(std::string i, bool pl);
};


class TIPAstVisitor
{
public:
  virtual ~TIPAstVisitor() = default;
  virtual void  visitNumExpr(std::shared_ptr<NumberExpr> root);
  virtual void  visitVarExpr(std::shared_ptr<VariableExpr> root);
  virtual void  visitBinaryExpr(std::shared_ptr<BinaryExpr> root);
  virtual void  visitFunAppExpr(std::shared_ptr<FunAppExpr> root);
  virtual void  visitInputExpr(std::shared_ptr<InputExpr> root);
  virtual void  visitAllocExpr(std::shared_ptr<AllocExpr> root);
  virtual void  visitRefExpr(std::shared_ptr<RefExpr> root);
  virtual void  visitDeRefExpr(std::shared_ptr<DeRefExpr> root);
  virtual void  visitNullExpr(std::shared_ptr<NullExpr> root);
  virtual void  visitFieldExpr(std::shared_ptr<FieldExpr> root);
  virtual void  visitRecordExpr(std::shared_ptr<RecordExpr> root);
  virtual void  visitAccessExpr(std::shared_ptr<AccessExpr> root);
  virtual void  visitDeclaration(std::shared_ptr<DeclStmt> root);
  virtual void  visitBlockStmt(std::shared_ptr<BlockStmt> root);
  virtual void  visitAssignmentStmt(std::shared_ptr<AssignStmt> root);
  virtual void  visitWhileStmt(std::shared_ptr<WhileStmt> root);
  virtual void  visitIfStmt(std::shared_ptr<IfStmt> root);
  virtual void  visitOutputStmt(std::shared_ptr<OutputStmt> root);
  virtual void  visitErrorStmt(std::shared_ptr<ErrorStmt> root);
  virtual void  visitReturnStmt(std::shared_ptr<ReturnStmt> root);
  virtual void  visitFunction(std::shared_ptr<Function> root);
  virtual void  visitIdentifierDeclaration(std::shared_ptr<IdentifierDeclaration> root);
  virtual void  visitIdentifier(std::shared_ptr<Identifier> root);
  virtual void  visit(std::shared_ptr<Node> root);
protected:
  void  visitChildren(std::shared_ptr<Node> root);
};



} // namespace TIPtree
