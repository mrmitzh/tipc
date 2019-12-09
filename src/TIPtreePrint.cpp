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

std::string FieldExpr::type()
{
  return "FieldExpr";
}

std::string FieldExpr::get_type()
{
  return FieldExpr::type();
}

std::string DeclStmt::type()
{
  return "Declstmt";
}

std::string DeclStmt::get_type()
{
  return DeclStmt::type();
}

std::string BlockStmt::type()
{
  return "BlockStmt";
}

std::string BlockStmt::get_type()
{
  return BlockStmt::type();
}

std::string ErrorStmt::type()
{
  return "ErrorStmt";
}

std::string ErrorStmt::get_type()
{
  return ErrorStmt::type();
}

std::string IdentifierDeclaration::type()
{
  return "IdentifierDeclaration";
}

std::string IdentifierDeclaration::get_type()
{
  return IdentifierDeclaration::type();
}


void NumberExpr::accept(TIPAstVisitor& visitor) 
{
  visitor.visitNumExpr(shared_from_this());
}

void VariableExpr::accept(TIPAstVisitor& visitor)
{
  visitor.visitVarExpr(shared_from_this());
}

void BinaryExpr::accept(TIPAstVisitor& visitor)
{
  visitor.visitBinaryExpr(shared_from_this());
}

void FunAppExpr::accept(TIPAstVisitor& visitor)
{
  visitor.visitFunAppExpr(shared_from_this());
}

void InputExpr::accept(TIPAstVisitor& visitor)
{
  visitor.visitInputExpr(shared_from_this());
}

void AllocExpr::accept(TIPAstVisitor& visitor)
{
  visitor.visitAllocExpr(shared_from_this());
}

void RefExpr::accept(TIPAstVisitor& visitor)
{
  visitor.visitRefExpr(shared_from_this());
}

void DeRefExpr::accept(TIPAstVisitor& visitor)
{
  visitor.visitDeRefExpr(shared_from_this());
}

void NullExpr::accept(TIPAstVisitor& visitor)
{
  visitor.visitNullExpr(shared_from_this());
}

void FieldExpr::accept(TIPAstVisitor& visitor)
{
  visitor.visitFieldExpr(shared_from_this());
}

void RecordExpr::accept(TIPAstVisitor& visitor)
{
  visitor.visitRecordExpr(shared_from_this());
}

void AccessExpr::accept(TIPAstVisitor& visitor)
{
  visitor.visitAccessExpr(shared_from_this());
}

void DeclStmt::accept(TIPAstVisitor& visitor)
{
  visitor.visitDeclaration(shared_from_this());
}

void BlockStmt::accept(TIPAstVisitor& visitor)
{
  visitor.visitBlockStmt(shared_from_this());
}

void AssignStmt::accept(TIPAstVisitor& visitor)
{
  visitor.visitAssignmentStmt(shared_from_this());
}

void WhileStmt::accept(TIPAstVisitor& visitor)
{
  visitor.visitWhileStmt(shared_from_this());
}

void IfStmt::accept(TIPAstVisitor& visitor)
{
  visitor.visitIfStmt(shared_from_this());
}

void OutputStmt::accept(TIPAstVisitor& visitor)
{
  visitor.visitOutputStmt(shared_from_this());
}

void ErrorStmt::accept(TIPAstVisitor& visitor)
{
  visitor.visitErrorStmt(shared_from_this());
}

void ReturnStmt::accept(TIPAstVisitor& visitor)
{
  visitor.visitReturnStmt(shared_from_this());
}

void Function::accept(TIPAstVisitor& visitor)
{
  visitor.visitFunction(shared_from_this());
}

void IdentifierDeclaration::accept(TIPAstVisitor& visitor)
{
  visitor.visitIdentifierDeclaration(shared_from_this());
}


void NumberExpr::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env) 
{
  visitor.visitNumExpr(shared_from_this(),env);
}

void VariableExpr::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitVarExpr(shared_from_this(),env);
}

void BinaryExpr::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitBinaryExpr(shared_from_this(),env);
}

void FunAppExpr::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitFunAppExpr(shared_from_this(),env);
}

void InputExpr::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitInputExpr(shared_from_this(),env);
}

void AllocExpr::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitAllocExpr(shared_from_this(),env);
}

void RefExpr::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitRefExpr(shared_from_this(),env);
}

void DeRefExpr::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitDeRefExpr(shared_from_this(),env);
}

void NullExpr::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitNullExpr(shared_from_this(),env);
}

void FieldExpr::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitFieldExpr(shared_from_this(),env);
}

void RecordExpr::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitRecordExpr(shared_from_this(),env);
}

void AccessExpr::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitAccessExpr(shared_from_this(),env);
}

void DeclStmt::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitDeclaration(shared_from_this(),env);
}

void BlockStmt::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitBlockStmt(shared_from_this(),env);
}

void AssignStmt::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitAssignmentStmt(shared_from_this(),env);
}

void WhileStmt::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitWhileStmt(shared_from_this(),env);
}

void IfStmt::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitIfStmt(shared_from_this(),env);
}

void OutputStmt::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitOutputStmt(shared_from_this(),env);
}

void ErrorStmt::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitErrorStmt(shared_from_this(),env);
}

void ReturnStmt::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitReturnStmt(shared_from_this(),env);
}

void Function::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitFunction(shared_from_this(),env);
}

void IdentifierDeclaration::accept(TIPAstVisitorWithEnv& visitor,std::unordered_map<std::string, std::shared_ptr<Declaration>> env)
{
  visitor.visitIdentifierDeclaration(shared_from_this(),env);
}



std::string Program::print(std::string i, bool pl = false,bool withType = false) {
  indent = i;      // initialize namespace global for indent stride
  printLines = pl; // print line numbers
  std::string pp;
  for (auto const &fn : FUNCTIONS) {
    pp += fn->print(withType) + "\n";
  }
  return pp;
}

std::string Function::print(bool withType) {
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
  if (withType && inferredType)
  {
    pp += ": " + inferredType->toString();
  }
  if (printLines) {
    pp += " // @" + std::to_string(LINE);
  }
  pp += "\n";

  indentLevel++;
  pp += indentation() + "{\n";
  indentLevel++;

  for (auto const &decl : DECLS) {
    pp += indentation() + decl->print(withType) + "\n";
  }

  for (auto const &stmt : BODY) {
    pp += indentation() + stmt->print(withType) + "\n";
  }

  indentLevel--;
  pp += indentation() + "}\n";
  indentLevel--;

  return pp;
}
std::string Function::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string NumberExpr::print(bool withType) { return std::to_string(VAL); }
std::string NumberExpr::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string VariableExpr::print(bool withType) { return NAME; }
std::string VariableExpr::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string BinaryExpr::print(bool withType) {
  return "(" + LHS->print(withType) + " " + OP + " " + RHS->print(withType) + ")";
}
std::string BinaryExpr::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string InputExpr::print(bool withType) { return "input"; }
std::string InputExpr::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string FunAppExpr::print(bool withType) {
  std::string pp = FUN->print(withType) + "(";
  // comma separated argument list
  bool skip = true;
  for (auto const &arg : ACTUALS) {
    if (skip) {
      skip = false;
      pp += arg->print(withType);
    } else {
      pp += ", " + arg->print(withType);
    }
  }
  pp += ")";
  return pp;
}
std::string FunAppExpr::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string IdentifierDeclaration::print(bool withType) 
{ 
  std::string pp = value;
  if(withType)
  {
    if(inferredType)
    {
      pp += ": " + inferredType->toString();
    }
  } 
  return pp;
}
std::string IdentifierDeclaration::printWithLine() { return print() + " : " +  std::to_string(LINE); }

std::string AllocExpr::print(bool withType) { return "alloc " + ARG->print(withType); }
std::string AllocExpr::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string RefExpr::print(bool withType) { return "&" + NAME; }
std::string RefExpr::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string DeRefExpr::print(bool withType) { return "*" + ARG->print(withType); }
std::string DeRefExpr::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string NullExpr::print(bool withType) { return "null"; }
std::string NullExpr::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string FieldExpr::print(bool withType) { return FIELD + ":" + INIT->print(withType); }
std::string FieldExpr::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string RecordExpr::print(bool withType) {
  std::string pp = "{";
  // comma separated argument list
  bool skip = true;
  for (auto const &field : FIELDS) {
    if (skip) {
      skip = false;
      pp += field->print(withType);
    } else {
      pp += ", " + field->print(withType);
    }
  }
  pp += "}";
  return pp;
}
std::string RecordExpr::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string AccessExpr::print(bool withType) { return RECORD->print(withType) + "." + FIELD; }
std::string AccessExpr::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string DeclStmt::print(bool withType) {
  std::string pp = "var ";
  // comma separated variable names list
  bool skip = true;
  for (auto dummyId : dummyVars) {
    if (skip) {
      skip = false;
      pp += dummyId->print(withType);
    } else {
      pp += ", " + dummyId->print(withType);
    }
  }
  pp += ";";
  if (printLines)
    pp += " // @" + std::to_string(LINE);
  return pp;
}
std::string DeclStmt::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string AssignStmt::print(bool withType) {
  return LHS->print(withType) + " = " + RHS->print(withType) + ";";
}
std::string AssignStmt::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string BlockStmt::print(bool withType) {
  std::string pp = "{\n";
  indentLevel++;
  for (auto const &s : STMTS) {
    pp += indentation() + s->print(withType) + "\n";
  }
  indentLevel--;
  pp += indentation() + "}";
  return pp;
}
std::string BlockStmt::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string WhileStmt::print(bool withType) {
  std::string pp = "while (" + COND->print(withType) + ") \n";
  indentLevel++;
  pp += indentation() + BODY->print(withType);
  indentLevel--;
  return pp;
}
std::string WhileStmt::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string IfStmt::print(bool withType) {
  std::string pp = "if (" + COND->print(withType) + ") \n";
  indentLevel++;
  pp += indentation() + THEN->print(withType);

  if (ELSE != nullptr) {
    indentLevel--;
    pp += "\n" + indentation() + "else\n";
    indentLevel++;
    pp += indentation() + ELSE->print(withType);
  }
  indentLevel--;
  return pp;
}
std::string IfStmt::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string OutputStmt::print(bool withType) { return "output " + ARG->print(withType) + ";"; }
std::string OutputStmt::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string ErrorStmt::print(bool withType) { return "error " + ARG->print(withType) + ";"; }
std::string ErrorStmt::printWithLine() { return print() + " : " +  std::to_string(LINE); }


std::string ReturnStmt::print(bool withType) { return "return " + ARG->print(withType) + ";"; }
std::string ReturnStmt::printWithLine() { return print() + " : " +  std::to_string(LINE); }


} // namespace TIPtree
