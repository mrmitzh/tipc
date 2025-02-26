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
#include <unordered_map>
#include <memory>
#include <iostream>
#include <string>
#include <vector>

/******************************************************************
 * Abstract Syntax Tree for TIP
 *****************************************************************/

namespace TIPtree {

class TIPAstVisitor;
class TIPAstVisitorWithEnv;
class Declaration;

class TipType
{
public:
    TipType() = default;
    virtual ~TipType() = default;
    static std::string type();
    virtual std::string getType() = 0;
    virtual std::string toString();
};

// Node - this is a base class for all tree nodes
class Node {
public:
  std::shared_ptr<TipType> inferredType;
  virtual ~Node() = default;
  virtual llvm::Value *codegen() = 0;
  virtual std::string print(bool withType = false) = 0;
  virtual std::string printWithLine() = 0;
  virtual std::string get_type();
  virtual void accept(TIPAstVisitor& visitor) = 0;
  virtual void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) = 0;
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
  int LINE;
  IdentifierDeclaration(std::string value,int LINE):value(value),LINE(LINE){};
  ~IdentifierDeclaration() = default;
  static std::string type();
  std::string get_type() override;
  llvm::Value *codegen() override { return nullptr; };
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;
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
  int LINE;
  NumberExpr(int VAL,int LINE) : VAL(VAL),LINE(LINE) {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;
};

/// VariableExpr - class for referencing a variable
class VariableExpr : public Expr, public std::enable_shared_from_this<VariableExpr>
{
public:
  std::string NAME;
  int LINE;
  VariableExpr(const std::string &NAME,int LINE ) : NAME(NAME),LINE(LINE) {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  // Getter to distinguish LHS of assigment for codegen
  std::string getName() { return NAME; };
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;
};

/// BinaryExpr - class for a binary operator.
class BinaryExpr : public Expr, public std::enable_shared_from_this<BinaryExpr>
{
public:
  std::string OP;
  std::shared_ptr<Expr> LHS, RHS;
  int LINE;
  BinaryExpr(const std::string &OP, std::shared_ptr<Expr> LHS,
             std::shared_ptr<Expr> RHS,int LINE)
      : OP(OP), LHS(std::move(LHS)), RHS(std::move(RHS)),LINE(LINE) {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;
};

/// FunAppExpr - class for function calls.
class FunAppExpr : public Expr, public std::enable_shared_from_this<FunAppExpr>
{
public:
  std::shared_ptr<Expr> FUN;
  std::vector<std::shared_ptr<Expr>> ACTUALS;
  int LINE;
  FunAppExpr(std::shared_ptr<Expr> FUN,
             std::vector<std::shared_ptr<Expr>> ACTUALS,
             int LINE)
      : FUN(std::move(FUN)), ACTUALS(std::move(ACTUALS)),LINE(LINE) {}
  static std::string type();
  std::string get_type() override;
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;
};

/// InputExpr - class for input expression
class InputExpr : public Expr, public std::enable_shared_from_this<InputExpr>
{
public:
  int LINE;
  InputExpr(int LINE) : LINE(LINE) {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;

};

// AllocExpr - class for alloc expression
class AllocExpr : public Expr, public std::enable_shared_from_this<AllocExpr>
{
public:
  std::shared_ptr<Expr> ARG;
  int LINE;
  AllocExpr(std::shared_ptr<Expr> ARG,int LINE) : ARG(std::move(ARG)),LINE(LINE) {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;

};

// RefExpr - class for referencing the address of a variable
class RefExpr : public Expr, public std::enable_shared_from_this<RefExpr>
{
public:
  std::string NAME;
  std::shared_ptr<Expr> ARG;
  int LINE;
  RefExpr(const std::string &NAME, std::shared_ptr<Expr> ARG,int LINE) : NAME(NAME),ARG(std::move(ARG)),LINE(LINE) {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;

};

// DeRefExpr - class for dereferencing a pointer expression
class DeRefExpr : public Expr, public std::enable_shared_from_this<DeRefExpr>
{
public:
  std::shared_ptr<Expr> ARG;
  int LINE;
  DeRefExpr(std::shared_ptr<Expr> ARG,int LINE) : ARG(std::move(ARG)),LINE(LINE) {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;

};

/// NullExpr - class for a null expression
class NullExpr : public Expr, public std::enable_shared_from_this<NullExpr>
{
public:
  int LINE;
  NullExpr(int LINE) :LINE(LINE) {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;

};

// FieldExpr - class for the field of a structure
class FieldExpr : public Expr, public std::enable_shared_from_this<FieldExpr>
{
public:
  std::string FIELD;
  std::shared_ptr<VariableExpr> dummyFIELD;
  std::shared_ptr<Expr> INIT;
  int LINE;
  FieldExpr(const std::string &FIELD, std::shared_ptr<Expr> INIT,int LINE)
      : FIELD(FIELD), INIT(std::move(INIT)), LINE(LINE) {
        dummyFIELD = std::make_shared<VariableExpr>(FIELD,LINE);
      }
  llvm::Value *codegen() override;
  static std::string type();
  std::string get_type() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;

};

// RecordExpr - class for defining a record
class RecordExpr : public Expr, public std::enable_shared_from_this<RecordExpr>
{
public:
  std::vector<std::shared_ptr<FieldExpr>> FIELDS;
  int LINE;
  RecordExpr(std::vector<std::shared_ptr<FieldExpr>> FIELDS,int LINE)
      : FIELDS(std::move(FIELDS)),LINE(LINE)  {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;

};

// AccessExpr - class for a record field access
class AccessExpr : public Expr, public std::enable_shared_from_this<AccessExpr>
{
public:
  std::shared_ptr<Expr> RECORD;
  std::string FIELD;
  std::shared_ptr<VariableExpr> dummyFIELD;
  int LINE;
  AccessExpr(std::shared_ptr<Expr> RECORD, const std::string &FIELD,int LINE)
      : RECORD(std::move(RECORD)), FIELD(FIELD), LINE(LINE) 
      {
        dummyFIELD = std::make_shared<VariableExpr>(this->FIELD,LINE);
      }
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;

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
  std::vector<std::shared_ptr<IdentifierDeclaration>> dummyVars;
  int LINE; // line on which decl statement occurs

  DeclStmt(std::vector<std::string> VARS, int LINE)
      : VARS(std::move(VARS)), LINE(LINE) {
        for(const auto& arg:this->VARS)
        {
          dummyVars.push_back(std::make_shared<IdentifierDeclaration>(arg,LINE));
        }
      }
  llvm::Value *codegen() override;
  static std::string type();
  std::string get_type() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;

};

// BlockStmt - class for block of statements
class BlockStmt : public Stmt, public std::enable_shared_from_this<BlockStmt>
{
public:
  std::vector<std::shared_ptr<Stmt>> STMTS;
  int LINE;
  BlockStmt(std::vector<std::shared_ptr<Stmt>> STMTS, int LINE)
      : STMTS(std::move(STMTS)), LINE(LINE) {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  static std::string type();
  std::string get_type() override;
  std::string printWithLine() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;
};

// AssignStmt - class for assignment
class AssignStmt : public Stmt, public std::enable_shared_from_this<AssignStmt>
{
public:
  std::shared_ptr<Expr> LHS, RHS;
  int LINE;
  AssignStmt(std::shared_ptr<Expr> LHS, std::shared_ptr<Expr> RHS, int LINE)
      : LHS(std::move(LHS)), RHS(std::move(RHS)), LINE(LINE) {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  static std::string type();
  std::string get_type() override;
  std::string printWithLine() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;
};

// WhileStmt - class for a while loop
class WhileStmt : public Stmt, public std::enable_shared_from_this<WhileStmt>
{
public:
  std::shared_ptr<Expr> COND;
  std::shared_ptr<Stmt> BODY;
  int LINE;
  WhileStmt(std::shared_ptr<Expr> COND, std::shared_ptr<Stmt> BODY,int LINE)
      : COND(std::move(COND)), BODY(std::move(BODY)), LINE(LINE) {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;
};

/// IfStmt - class for if-then-else
class IfStmt : public Stmt, public std::enable_shared_from_this<IfStmt>
{
public:
  std::shared_ptr<Expr> COND;
  std::shared_ptr<Stmt> THEN, ELSE;
  int LINE;
  IfStmt(std::shared_ptr<Expr> COND, std::shared_ptr<Stmt> THEN,
         std::shared_ptr<Stmt> ELSE, int LINE)
      : COND(std::move(COND)), THEN(std::move(THEN)), ELSE(std::move(ELSE)), LINE(LINE) {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;
};

/// OutputStmt - class for a output statement
class OutputStmt : public Stmt, public std::enable_shared_from_this<OutputStmt>
{
public:
  std::shared_ptr<Expr> ARG;
  int LINE;
  OutputStmt(std::shared_ptr<Expr> ARG,int LINE) : ARG(std::move(ARG)),LINE(LINE) {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;
};

/// ErrorStmt - class for a error statement
class ErrorStmt : public Stmt, public std::enable_shared_from_this<ErrorStmt>
{
public:
  std::shared_ptr<Expr> ARG;
  int LINE;
  ErrorStmt(std::shared_ptr<Expr> ARG,int LINE) : ARG(std::move(ARG)),LINE(LINE) {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;
};

/// ReturnStmt - class for a return statement
class ReturnStmt : public Stmt, public std::enable_shared_from_this<ReturnStmt>
{
public:
  std::shared_ptr<Expr> ARG;
  int LINE;
  ReturnStmt(std::shared_ptr<Expr> ARG,int LINE) : ARG(std::move(ARG)),LINE(LINE) {}
  llvm::Value *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;
};

/******************* Program and Function Nodes *********************/

// Function - signature, local declarations, and a body
class Function: public Declaration, public std::enable_shared_from_this<Function>
{
public:
  std::string NAME;
  std::shared_ptr<VariableExpr> dummyNAME;
  // dummy version of FORMALS
  std::vector<std::shared_ptr<IdentifierDeclaration>> dummyFORMALS;
  std::vector<std::string> FORMALS;
  std::vector<std::shared_ptr<DeclStmt>> DECLS;
  std::vector<std::shared_ptr<Stmt>> BODY;
  int LINE; // line on which function definition occurs

  Function(const std::string &NAME, std::vector<std::string> FORMALS,
           std::vector<std::shared_ptr<DeclStmt>> DECLS,
           std::vector<std::shared_ptr<Stmt>> BODY, int LINE)
      : NAME(NAME), FORMALS(std::move(FORMALS)), DECLS(std::move(DECLS)),
        BODY(std::move(BODY)), LINE(LINE) 
        {
          dummyNAME = std::make_shared<VariableExpr>(this->NAME,LINE);
          for(const auto& arg:this->FORMALS)
          {
            dummyFORMALS.push_back(std::make_shared<IdentifierDeclaration>(arg,LINE));
          }
        }
  llvm::Function *codegen() override;
  std::string print(bool withType = false) override;
  std::string printWithLine() override;
  static std::string type();
  std::string get_type() override;
  void accept(TIPAstVisitor& visitor) override;
  void accept(TIPAstVisitorWithEnv& visitor, std::unordered_map<std::string, std::shared_ptr<Declaration>> env) override;

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
  std::string print(std::string i, bool pl, bool withType);
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
  virtual void  visit(std::shared_ptr<Node> root);
protected:
  void  visitChildren(std::shared_ptr<Node> root);
};

class TIPAstVisitorWithEnv
{
public:
  void  visitNumExpr(std::shared_ptr<NumberExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitVarExpr(std::shared_ptr<VariableExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitBinaryExpr(std::shared_ptr<BinaryExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitFunAppExpr(std::shared_ptr<FunAppExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitInputExpr(std::shared_ptr<InputExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitAllocExpr(std::shared_ptr<AllocExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitRefExpr(std::shared_ptr<RefExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitDeRefExpr(std::shared_ptr<DeRefExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitNullExpr(std::shared_ptr<NullExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitFieldExpr(std::shared_ptr<FieldExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitRecordExpr(std::shared_ptr<RecordExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitAccessExpr(std::shared_ptr<AccessExpr> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitDeclaration(std::shared_ptr<DeclStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitBlockStmt(std::shared_ptr<BlockStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitAssignmentStmt(std::shared_ptr<AssignStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitWhileStmt(std::shared_ptr<WhileStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitIfStmt(std::shared_ptr<IfStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitOutputStmt(std::shared_ptr<OutputStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitErrorStmt(std::shared_ptr<ErrorStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitReturnStmt(std::shared_ptr<ReturnStmt> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitFunction(std::shared_ptr<Function> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitIdentifierDeclaration(std::shared_ptr<IdentifierDeclaration> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visit(std::shared_ptr<Node> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);
  void  visitChildren(std::shared_ptr<Node> root,std::unordered_map<std::string, std::shared_ptr<Declaration>> env);

  std::unordered_map<std::shared_ptr<VariableExpr>,std::shared_ptr<Declaration>>  analysis(std::shared_ptr<Program> root);

private:
  std::unordered_map<std::string,std::shared_ptr<Declaration>> extendEnv(std::unordered_map<std::string,std::shared_ptr<Declaration>> env, std::unordered_map<std::string,std::shared_ptr<Declaration>> ext);
  std::unordered_map<std::string,std::shared_ptr<Declaration>> extendEnv(std::unordered_map<std::string,std::shared_ptr<Declaration>> env, std::pair<std::string,std::shared_ptr<Declaration>> ext);
  std::unordered_map<std::string,std::shared_ptr<Declaration>> peekDecl(std::vector<std::shared_ptr<DeclStmt>> decls);
  std::unordered_map<std::shared_ptr<VariableExpr>,std::shared_ptr<Declaration>> declResult;
};


} // namespace TIPtree
