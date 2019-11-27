#include "TIPtree.h"

namespace TIPtree {

static std::string indent;
static int indentLevel = 0;
static bool printLines = false;

// indentation is the contatenation of "level" indent strings
std::string indentation() {
  std::string indStr;
  for (int i = 0; i < indentLevel; i++) {
    indStr += indent;
  }
  return indStr;
}

std::string Node::get_type()
{
  return "";
}

std::string NumberExpr::type()
{
  return "NumberExpr";
}

std::string NumberExpr::get_type()
{
  return NumberExpr::type();
}

std::string VariableExpr::type()
{
  return "VariableExpr";
}

std::string VariableExpr::get_type()
{
  return VariableExpr::type();
}

std::string InputExpr::type()
{
    return "InputExpr";
}

std::string InputExpr::get_type()
{
  return InputExpr::type();
}

std::string IfStmt::type()
{
  return "IfStmt";
}

std::string IfStmt::get_type()
{
  return IfStmt::type();
}

std::string OutputStmt::type()
{
  return "OutputStmt";
}

std::string OutputStmt::get_type()
{
  return OutputStmt::type();
}

std::string WhileStmt::type()
{
  return "WhileStmt";
}

std::string WhileStmt::get_type()
{
  return WhileStmt::type();
}

std::string AssignStmt::type()
{
  return "AssignStmt";
}

std::string AssignStmt::get_type()
{
  return AssignStmt::type();
}

std::string BinaryExpr::type()
{
  return "BinaryExpr";
}

std::string BinaryExpr::get_type()
{
  return BinaryExpr::type();
}

std::string RefExpr::type()
{
  return "RefExpr";
}

std::string RefExpr::get_type()
{
  return RefExpr::type();
}

std::string DeRefExpr::type()
{
  return "DeRefExpr";
}

std::string DeRefExpr::get_type()
{
  return DeRefExpr::type();
}

std::string AllocExpr::type()
{
  return "AllocExpr";
}

std::string AllocExpr::get_type()
{
  return AllocExpr::type();
}

std::string NullExpr::type()
{
  return "NullExpr";
}

std::string NullExpr::get_type()
{
  return NullExpr::type();
}

std::string FunAppExpr::type()
{
  return "FunAppExpr";
}

std::string FunAppExpr::get_type()
{
  return FunAppExpr::type();
}

std::string ReturnStmt::type()
{
  return "ReturnStmt";
}

std::string ReturnStmt::get_type()
{
  return ReturnStmt::type();
}

std::string RecordExpr::type()
{
  return "RecordExpr";
}

std::string RecordExpr::get_type()
{
  return RecordExpr::type();
}

std::string AccessExpr::type()
{
  return "AccessExpr";
}

std::string AccessExpr::get_type()
{
  return AccessExpr::type();
}

std::string Function::type()
{
  return "Function";
}

std::string Function::get_type()
{
  return Function::type();
}


void NumberExpr::accept(TIPAstVisitor* visitor) 
{
  visitor->visitNumExpr(this);
}

void VariableExpr::accept(TIPAstVisitor* visitor)
{
  visitor->visitVarExpr(this);
}

void BinaryExpr::accept(TIPAstVisitor* visitor)
{
  visitor->visitBinaryExpr(this);
}

void FunAppExpr::accept(TIPAstVisitor* visitor)
{
  visitor->visitFunAppExpr(this);
}

void InputExpr::accept(TIPAstVisitor* visitor)
{
  visitor->visitInputExpr(this);
}

void AllocExpr::accept(TIPAstVisitor* visitor)
{
  visitor->visitAllocExpr(this);
}

void RefExpr::accept(TIPAstVisitor* visitor)
{
  visitor->visitRefExpr(this);
}

void DeRefExpr::accept(TIPAstVisitor* visitor)
{
  visitor->visitDeRefExpr(this);
}

void NullExpr::accept(TIPAstVisitor* visitor)
{
  visitor->visitNullExpr(this);
}

void FieldExpr::accept(TIPAstVisitor* visitor)
{
  visitor->visitFieldExpr(this);
}

void RecordExpr::accept(TIPAstVisitor* visitor)
{
  visitor->visitRecordExpr(this);
}

void AccessExpr::accept(TIPAstVisitor* visitor)
{
  visitor->visitAccessExpr(this);
}

void DeclStmt::accept(TIPAstVisitor* visitor)
{
  visitor->visitDeclaration(this);
}

void BlockStmt::accept(TIPAstVisitor* visitor)
{
  visitor->visitBlockStmt(this);
}

void AssignStmt::accept(TIPAstVisitor* visitor)
{
  visitor->visitAssignmentStmt(this);
}

void WhileStmt::accept(TIPAstVisitor* visitor)
{
  visitor->visitWhileStmt(this);
}

void IfStmt::accept(TIPAstVisitor* visitor)
{
  visitor->visitIfStmt(this);
}

void OutputStmt::accept(TIPAstVisitor* visitor)
{
  visitor->visitOutputStmt(this);
}

void ErrorStmt::accept(TIPAstVisitor* visitor)
{
  visitor->visitErrorStmt(this);
}

void ReturnStmt::accept(TIPAstVisitor* visitor)
{
  visitor->visitReturnStmt(this);
}

void Function::accept(TIPAstVisitor* visitor)
{
  visitor->visitFunction(this);
}




std::string Program::print(std::string i, bool pl = false) {
  indent = i;      // initialize namespace global for indent stride
  printLines = pl; // print line numbers
  std::string pp;
  for (auto const &fn : FUNCTIONS) {
    pp += fn->print() + "\n";
  }
  return pp;
}

std::string Function::print() {
  std::string pp = NAME + "(";

  // comma separated parameter name list
  bool skip = true;
  for (auto param : FORMALS) {
    if (skip) {
      skip = false;
      pp += param;
    } else {
      pp += ", " + param;
    }
  }
  pp += ")";
  if (printLines) {
    pp += " // @" + std::to_string(LINE);
  }
  pp += "\n";

  indentLevel++;
  pp += indentation() + "{\n";
  indentLevel++;

  for (auto const &decl : DECLS) {
    pp += indentation() + decl->print() + "\n";
  }

  for (auto const &stmt : BODY) {
    pp += indentation() + stmt->print() + "\n";
  }

  indentLevel--;
  pp += indentation() + "}\n";
  indentLevel--;

  return pp;
}

std::string NumberExpr::print() { return std::to_string(VAL); }

std::string VariableExpr::print() { return NAME; }

std::string BinaryExpr::print() {
  return "(" + LHS->print() + " " + OP + " " + RHS->print() + ")";
}

std::string InputExpr::print() { return "input"; }

std::string FunAppExpr::print() {
  std::string pp = FUN->print() + "(";
  // comma separated argument list
  bool skip = true;
  for (auto const &arg : ACTUALS) {
    if (skip) {
      skip = false;
      pp += arg->print();
    } else {
      pp += ", " + arg->print();
    }
  }
  pp += ")";
  return pp;
}

std::string AllocExpr::print() { return "alloc " + ARG->print(); }

std::string RefExpr::print() { return "&" + NAME; }

std::string DeRefExpr::print() { return "*" + ARG->print(); }

std::string NullExpr::print() { return "null"; }

std::string FieldExpr::print() { return FIELD + ":" + INIT->print(); }

std::string RecordExpr::print() {
  std::string pp = "{";
  // comma separated argument list
  bool skip = true;
  for (auto const &field : FIELDS) {
    if (skip) {
      skip = false;
      pp += field->print();
    } else {
      pp += ", " + field->print();
    }
  }
  pp += "}";
  return pp;
}

std::string AccessExpr::print() { return RECORD->print() + "." + FIELD; }

std::string DeclStmt::print() {
  std::string pp = "var ";
  // comma separated variable names list
  bool skip = true;
  for (auto id : VARS) {
    if (skip) {
      skip = false;
      pp += id;
    } else {
      pp += ", " + id;
    }
  }
  pp += ";";
  if (printLines)
    pp += " // @" + std::to_string(LINE);
  return pp;
}

std::string AssignStmt::print() {
  return LHS->print() + " = " + RHS->print() + ";";
}

std::string BlockStmt::print() {
  std::string pp = "{\n";
  indentLevel++;
  for (auto const &s : STMTS) {
    pp += indentation() + s->print() + "\n";
  }
  indentLevel--;
  pp += indentation() + "}";
  return pp;
}

std::string WhileStmt::print() {
  std::string pp = "while (" + COND->print() + ") \n";
  indentLevel++;
  pp += indentation() + BODY->print();
  indentLevel--;
  return pp;
}

std::string IfStmt::print() {
  std::string pp = "if (" + COND->print() + ") \n";
  indentLevel++;
  pp += indentation() + THEN->print();

  if (ELSE != nullptr) {
    indentLevel--;
    pp += "\n" + indentation() + "else\n";
    indentLevel++;
    pp += indentation() + ELSE->print();
  }
  indentLevel--;
  return pp;
}

std::string OutputStmt::print() { return "output " + ARG->print() + ";"; }

std::string ErrorStmt::print() { return "error " + ARG->print() + ";"; }

std::string ReturnStmt::print() { return "return " + ARG->print() + ";"; }

} // namespace TIPtree
