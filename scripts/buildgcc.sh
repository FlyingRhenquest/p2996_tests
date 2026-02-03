#!/bin/bash
#
#  * Clone gcc source repo down from the git mirror or download from a gnu.org mirror.
#  * make a build directory in the top level directory of the clone/detar
#  * run this buildgcc.sh script. This assumes it's gcc16.

../configure --prefix=/usr/local/gcc-16 --enable-languages=c,c++ --disable-multilib --with-local-prefix=/usr/local/gcc-16 --with-arch=native --with-tune=native
make -j4
