#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Debug.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace
{
  struct BasicBlockInstrumentationPass : public ModulePass
  {
    static char ID;
    BasicBlockInstrumentationPass() : ModulePass(ID) {}

    virtual bool runOnModule(Module &M) override;
  };
}


bool BasicBlockInstrumentationPass::runOnModule(Module &M)
{
  Constant *hookFunc = M.getFunction("bb_tracer");
  int mbblid = 0;

  errs() << "In module called: " << M.getName() << "!\n";

  for (auto &F : M)
  {
    errs() << "Saw a function called: " << F.getName() << "!\n";
    if ( hookFunc->getName().compare(F.getName()) == 0) {
      continue;
    }
    for (auto &BB : F)
    {
      errs() << "in a basic block\n";
      mbblid++;
      Instruction *lins = BB.getTerminator();
      IRBuilder<> Builder(lins);
      std::vector<Value *> args;
      args.push_back((Value *)ConstantInt::get(Type::getInt32Ty(M.getContext()), mbblid));
      Builder.CreateCall(hookFunc, args);
    }
  }

  errs() << "bb id = " << mbblid << " !\n";

  return true;
}

char BasicBlockInstrumentationPass::ID = 0;
static void registerBasicBlockInstrumentationPass(const PassManagerBuilder &,
                                                  legacy::PassManagerBase &PM)
{
  PM.add(new BasicBlockInstrumentationPass());
}

static RegisterPass<BasicBlockInstrumentationPass> X("baaasic-block-instrumentation", "Basic Block Instrumentation Pass",
                                                     false /* Only looks at CFG */,
                                                     false /* Analysis Pass */);

static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_ModuleOptimizerEarly, registerBasicBlockInstrumentationPass);

static RegisterStandardPasses
    RegisterMyPass0(PassManagerBuilder::EP_EnabledOnOptLevel0, registerBasicBlockInstrumentationPass);
