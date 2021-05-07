# basic block instrumentation pass

## Notes
This pass is a very simple example of a basic block instumentation using LLVM.
What this pass does is it inserts a function call to `bb_tracer` a function that
takes an integer value to identify the call site. By tracking the argument to
`bb_tracer` we can identify the control flow of the program.

## Build:
```sh
cd basic-block-instrumentation-pass
mkdir build && cd build && cmake .. && make
cd ../..
```


## Run:

```sh
clang -Xclang -load -Xclang basic-block-instrumentation-pass/build/basic-block-instrumentation/libBasicBlockInstrumentationPass.so ./sample/bb_instrumentation_input.c
```


## Reference
[Writing an LLVM Pass](https://llvm.org/docs/WritingAnLLVMPass.html#introduction-what-is-a-pass)
[ModulePasses with Auto Registration](https://github.com/sampsyo/llvm-pass-skeleton/issues/7)
