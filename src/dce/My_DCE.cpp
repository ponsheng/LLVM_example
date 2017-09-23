#include <cstdlib>
#include <ctime>
#include <string>
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Value.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;
// Run Value->dump() in gdb

namespace {
struct My_DCE : public FunctionPass {
  static char ID;
  My_DCE() : FunctionPass(ID) {
    std::srand(std::time(0));
  }

  bool runOnFunction(Function &F) override {
    bool change = false;
    SmallVector<Instruction *, 16> dead;

    errs() << "================\n FUNC: "<< F.getName() << "\n";
    for (inst_iterator FI = inst_begin(F), FE = inst_end(F); FI != FE;) {
        //errs() << FI->getName() << " "<< &*FI << ": " << FI->getOpcodeName() << "\n";
        Instruction *I = &*FI;
        FI++;
        errs() << *I;
        errs() << "  sideeffect: "<< I->mayHaveSideEffects() ;
        errs() << "  maywriteto memory: "<< I->mayWriteToMemory();
        errs() << "  maythrow: "<< I->mayThrow();
        errs() << "\n\n";

		if(!I->mayHaveSideEffects() && !dyn_cast<ReturnInst>(&*I) && !dyn_cast<BranchInst>(&*I) && I->use_empty() ) {
			 dead.push_back(&*I);
		}

	    while (!dead.empty()) {
        errs() << "Dead:";
        Instruction *I = dead.front();
        errs() << *I << "\n";

            dead.erase(dead.begin());
            I->eraseFromParent();
            change = true;
        }

    }
    return change;
  }
}; // end of struct Hello
}  // end of anonymous namespace

char My_DCE::ID = 0;
static RegisterPass<My_DCE> my_dce("My_DCE", "My Dead Code Elimination",
                             false, false );

