# skeleton module pass

## Notes
The first pass was to just get something basic working to make sure LLVM is set up right, and we have no issues writing and running a pass.

This pass is very incremental from the [skeleton function pass](../skeleton-function-pass/) but we get into the details.

[Basic code required](https://llvm.org/docs/WritingAnLLVMPass.html#basic-code-required) explains

1. the headers we included
2. namespacing
3. Various `Pass` classes
4. the `runOn*` function
5. pass initialization and registration
6. the arguments to `RegisterPass`
7. and finally the specifying when to run the pass

Another change we make in this is use a `ModulePass` instead of a `FunctionPass`.
LLVM has the following pass classes:
1. ImmutablePass
2. ModulePass
3. CallGraphSCCPass
4. FunctionPass
5. LoopPass
6. RegionPass
7. MachineFunctionPass

More on that in [Pass classes and requirements](https://llvm.org/docs/WritingAnLLVMPass.html#pass-classes-and-requirements)

## Build:
```sh
cd skeleton-module-pass
mkdir build && cd build && cmake .. && make
cd ../..
```


## Run:

```sh
clang -Xclang -load -Xclang skeleton-module-pass/build/skeleton/libSkeletonPass.so ./sample/prog_1.c
```


## Reference
[Writing an LLVM Pass](https://llvm.org/docs/WritingAnLLVMPass.html#introduction-what-is-a-pass)
[ModulePasses with Auto Registration](https://github.com/sampsyo/llvm-pass-skeleton/issues/7)
