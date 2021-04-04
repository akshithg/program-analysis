#!/bin/bash

set -eux

ROOT=$(git rev-parse --show-toplevel)
LLVM_INSTALL=$ROOT/bootstrap/llvm-prefix
mkdir -p $LLVM_INSTALL

# depending on llvm version may have out of memory (oom)  issues when compiling,
# it seems especially for this 10.0.1 version adding swap space or
# -DLLVM_PARALLEL_LINK_JOBS=1 or ninja -j # can help but may make compiling
# slower or still not work I found it best to compile lld first and use that as
# the linker for clang as well as the other command args below

#lld
pushd llvm-project
    git checkout  llvmorg-10.0.1
    mkdir -p build
    pushd build
        cmake -DLLVM_ENABLE_PROJECTS="lld" \
        -DLLVM_TARGETS_TO_BUILD=X86 \
        -DCMAKE_INSTALL_PREFIX=$LLVM_INSTALL \
        -DCMAKE_BUILD_TYPE=Debug \
        -DLLVM_USE_LINKER=gold \
        -DLLVM_ENABLE_ASSERTIONS=On \
        -DLLVM_OPTIMIZED_TABLEGEN=On \
        -LLVM_LINK_LLVM_DYLIB=On \
        -DLLVM_USE_SPLIT_DWARF=On \
        -G "Ninja" ../llvm

        ninja
        ninja install
    popd
popd

# everything else
pushd llvm-project
    git checkout  llvmorg-10.0.1
    mkdir -p build
    # makes everything else
    pushd build
        cmake -DLLVM_ENABLE_PROJECTS="all" \
        -DLLVM_TARGETS_TO_BUILD=X86 \
        -DCMAKE_INSTALL_PREFIX=$LLVM_INSTALL \
        -DCMAKE_BUILD_TYPE=Debug \
        -DLLVM_USE_LINKER=lld \
        -DLLVM_ENABLE_ASSERTIONS=On \
        -DLLVM_OPTIMIZED_TABLEGEN=On \
        -LLVM_LINK_LLVM_DYLIB=On \
        -DLLVM_USE_SPLIT_DWARF=On \
        -G "Ninja" ../llvm

        ninja
        ninja install
    popd
popd

# add llvm bin to your path
echo "Please add $LLVM_INSTALL/bin to your path"
echo "Installation done!"
