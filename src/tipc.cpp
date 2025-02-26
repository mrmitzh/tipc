#include <iostream>
#include <stdlib.h>
#include <fstream>

#include "TIPLexer.h"
#include "TIPParser.h"
#include "TIPtreeBuild.h"
#include "TIPtreeGen.h"
#include "TypeAnalysis.h"
#include "antlr4-runtime.h"
#include "llvm/Support/CommandLine.h"

using namespace std;
using namespace antlr4;
using namespace TIPtree;
using namespace llvm;

/*
static bool pretty = false;
static bool disableOpt = true;
static std::string sourceFile;
*/

/*
static bool typeanalysis = false
*/

static cl::OptionCategory
    TIPcat("tipc Options",
           "Options for controlling the TIP compilation process.");
static cl::opt<bool> pp("p", cl::desc("pretty print"), cl::cat(TIPcat));
static cl::opt<bool> ppWlines("l", cl::desc("pretty print with line numbers"),
                              cl::cat(TIPcat));
static cl::opt<bool> ta("t", cl::desc("pretty print with type analysis"), cl::cat(TIPcat));
static cl::opt<bool> noOpt("d", cl::desc("disable bitcode optimization"),
                           cl::cat(TIPcat));
static cl::opt<std::string> sourceFile(cl::Positional,
                                       cl::desc("<tip source file>"),
                                       cl::Required, cl::cat(TIPcat));

int main(int argc, const char *argv[]) {
  cl::HideUnrelatedOptions(TIPcat); // suppress non TIP options
  cl::ParseCommandLineOptions(argc, argv, "tipc - a TIP to llvm compiler\n");

  std::ifstream stream;
  stream.open(sourceFile);

  ANTLRInputStream input(stream);
  TIPLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  TIPParser parser(&tokens);

  TIPParser::ProgramContext *tree = parser.program();

  TIPtreeBuild tb(&parser);
  auto ast = tb.build(tree);

  if(ta){
    std::cout << "Type Analysis" << std::endl;
    TypeAnalysis typeAnalysis;
    auto typeData = typeAnalysis.analysis(ast);
    PutTypeToAst putTypeToAst(typeData);
    putTypeToAst.put(ast);
    auto printWithType = ast->print("  ", ppWlines,true);
    std::string value = sourceFile.getValue();
    size_t pos = value.find_last_of('.');
    if(pos != std::string::npos)
    {
      std::string fileName = value.substr(0,pos);
      ofstream of;
      of.open(fileName + "_types.ttip");
      std::cout << "Results of type analysis of " + fileName + " written to " + fileName + "_types.ttip"<< std::endl;
      of << printWithType;
      of.close();
    }
  }

  if (pp || ppWlines) {
    std::cout << ast->print("  ", ppWlines,false);
  } else {
    auto theModule = ast->codegen(sourceFile);
    if (!noOpt) {
      // Create a pass manager to simplify generated module
      auto TheFPM =
          llvm::make_unique<legacy::FunctionPassManager>(theModule.get());

      // Promote allocas to registers.
      TheFPM->add(createPromoteMemoryToRegisterPass());
      // Do simple "peephole" optimizations
      TheFPM->add(createInstructionCombiningPass());
      // Reassociate expressions.
      TheFPM->add(createReassociatePass());
      // Eliminate Common SubExpressions.
      TheFPM->add(createGVNPass());
      // Simplify the control flow graph (deleting unreachable blocks, etc).
      TheFPM->add(createCFGSimplificationPass());
      TheFPM->doInitialization();

      // run simplification pass on each function
      for (auto &fun : theModule->getFunctionList()) {
        TheFPM->run(fun);
      }
    }

    std::error_code ec;
    ToolOutputFile result(sourceFile + ".bc", ec, sys::fs::F_None);
    WriteBitcodeToFile(*theModule, result.os());
    result.keep();
  }
}
