# Bootstrapping


To write passes with LLVM we will first need to install the LLVM infrastructure.
Some operating systems already come with some of it already installed, but LLVM
is very actively developed and releases made [very
frequently](https://github.com/llvm/llvm-project/releases). So I highly
recommend installing from [source](https://github.com/llvm/llvm-project).

A few quirks with the installation include, running out of memory during
installation. This is a linker issue. A solution that i;ve found that works is,
first install just the `lld` — The LLVM linker, then use it to compile rest of
the tool chain.

`./bootstrap.sh` should take care of all the above. We use version
`llvmorg-10.0.1`.
