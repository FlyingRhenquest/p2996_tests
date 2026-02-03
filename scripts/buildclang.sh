#!/bin/bash

CLANG_INSTALL_PREFIX=/usr/local/clang-p2996
CLANG_SOURCE=/home/greyfox/sandbox/clang-p2996

mkdir -p /tmp/build
cd /tmp/build

cmake -G Ninja ${CLANG_SOURCE}/llvm \
      -DLLVM_ENABLE_PROJECTS="clang" \
      -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" \
      -DCMAKE_INSTALL_PREFIX=${CLANG_INSTALL_PREFIX} \
      -DCMAKE_BUILD_TYPE=Release \
      -DLLVM_TARGETS_TO_BUIILD="X86" \
      -DLLVM_ENABLE_ASSERTIONS=ON                                                                                                                                              

ninja

echo "Build complete. Run sudo ninja install to install the compiler"
