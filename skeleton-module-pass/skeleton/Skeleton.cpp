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
  struct SkeletonPass : public ModulePass
  {
    static char ID;
    SkeletonPass() : ModulePass(ID) {}

    virtual bool runOnModule(Module &M) override;
  };
}


bool SkeletonPass::runOnModule(Module &M)
{
  errs() << "In module called: " << M.getName() << "!\n";

  for (auto &F : M)
  {
    errs() << "Saw a function called: " << F.getName() << "!\n";
  }

  return false;
}

char SkeletonPass::ID = 0;
static void registerSkeletonPass(const PassManagerBuilder &,
                                 legacy::PassManagerBase &PM)
{
  PM.add(new SkeletonPass());
}

static RegisterPass<SkeletonPass> X("skeleton-module", "Skeleton Module Pass",
                                    false /* Only looks at CFG */,
                                    false /* Analysis Pass */);

static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_ModuleOptimizerEarly, registerSkeletonPass);

static RegisterStandardPasses
    RegisterMyPass0(PassManagerBuilder::EP_EnabledOnOptLevel0, registerSkeletonPass);
