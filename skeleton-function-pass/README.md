# skeleton function pass

## Notes
The are basically two types of passes.
1. Analysis Pass - computes information. Used for debugging, visualization etc.
2. Transformation Pass - Mutates the program in some way.


In this example and a couple more we will just be writing analysis passes to
understand how LLVM processes various program components.

One common way to write a pass is to deal with one function at a time. This lets
us do things local to the function. Here we do not have access to global values.

In this specific pass we simply iterate through: Functions > Basic Blocks >
Instructions and logs them to stdout.

This demonstrates a couple of things.
1. Writing a simple function pass.
2. Registering the function pass with the `PassManager`
3. Most importantly getting some usable `cmake` files that work.

Getting the `cmake` files can be hard. For now we'll use them as is. But will
soon get into the details.


## Build:
```sh
cd skeleton-function-pass
mkdir build && cd build && cmake .. && make
cd ../..
```

## Run:

```sh
clang -Xclang -load -Xclang skeleton-function-pass/build/skeleton/libSkeletonPass.so ./sa
```


## Reference
- [LLVM for Grad Students](https://www.cs.cornell.edu/~asampson/blog/llvm.html)
- [sampsyo/llvm-pass-skeleton](https://github.com/sampsyo/llvm-pass-skeleton)
- [LLVM’s Analysis and Transform Passes](https://llvm.org/docs/Passes.html#introduction)
