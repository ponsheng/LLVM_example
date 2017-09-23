#include <cstdlib>
#include <ctime>
#include <string>
#include "llvm/ADT/Statistic.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"

//#include "name.h"

using namespace llvm;

const char *adjectives[26] = { 
    "antsy", "blind", "crafty", "dreary", "eloquent",
    "fast", "green", "hefty", "ignoble", "jaunty",
    "krufty", "lewd", "minor", "nice", "old",
    "poor", "quiet", "red", "stoic", "taut",
    "ugly", "vibrant", "waning", "extreme",
    "young", "zonky" };

// captialize these nouns, the result is camelCased
const char *nouns[26] = {
    "Adam", "Bag", "Cobra", "Dude", "Eve",
    "Frog", "Ghost", "Hat", "Ide", "Jug",
    "Keg", "Lug", "Maid", "Night", "Oort",
    "Pig", "Quag", "Rag", "Stupor", "Tug",
    "Uzi", "Velo", "Wheat", "Oxo",
    "Yurt", "Zag" };


namespace {
struct RenameBB : public FunctionPass {
  static char ID;
  RenameBB() : FunctionPass(ID) {
    std::srand(std::time(0));
  }

  bool runOnFunction(Function &F) override {
    for (Function::iterator iter1 = F.begin(); iter1 != F.end(); iter1++) {
        BasicBlock &bb = *iter1;
        // Change the name of bb by random
        std::string s = std::string(adjectives[std::rand()%26]) + std::string(nouns[std::rand()%26]);
        bb.setName(s);

        errs().write_escaped(F.getName()) << ":";
        errs().write_escaped(bb.getName()) << '\n';
        // bb.getName().str()

    }

    return false;
  }
}; // end of struct Hello
}  // end of anonymous namespace

char RenameBB::ID = 0;
static RegisterPass<RenameBB> RBB_RP("RenameBB", "Rename BasicBlock",
                             false, false );

namespace {
struct PrintBB : public FunctionPass {
  static char ID;
  PrintBB() : FunctionPass(ID) {
    //std::srand(std::time(0));
  }

  bool runOnFunction(Function &F) override {
            for (auto &basic_block : F) {
            StringRef bbName(basic_block.getName());
                errs() << "BasicBlock: "  << bbName << "\n";
            } return true;

    for (Function::iterator iter1 = F.begin(); iter1 != F.end(); iter1++) {
        BasicBlock &bb = *iter1;

        errs().write_escaped(F.getName()) << ":";
        errs().write_escaped(iter1->getName()) << '\n';
		//BasicBlock& BB = ...
        for (Instruction &I : bb) {
   	        errs() << I.getOpcodeName() << "\n";
        }
        // The next statement works since operator<<(ostream&,...)
   	    // is overloaded for Instruction&
    }

    return false;
  }
}; // end of struct Hello
}  // end of anonymous namespace

char PrintBB::ID = 0;
static RegisterPass<PrintBB> PBB_RP("PrintBB", "Print BasicBlock",
                             false ,
                             false );
