# p2996 tests


This is just a test template for testing p2996 features in real time. Feel free to adapt it to your needs.
The bits I wrote will generally have an apache license on them but I'm not going to enforce anything in there.
Would appreciate a shout out if you find it useful or use the tests I write in a larger project.


## What's here


There's a top level cmake file here that just builds the tests. 


There are scripts in the scripts directory to build gcc and the clang Bloomberg fork. These will build to
an out-of-the-way install prefix so they don't interfere with your system binaries. There are also a couple
of toolchain files at the top level of this project which you can use to build with the compilers the
scripts build. You just specify the toolchain file you want, IE:


    cmake project-dir -DCMAKE_TOOLCHAIN_FILE=/path/to/gcc16-reflection.cmake
    

Will use the toolchain to build the project. Check out what's in there before you use it to make
sure directories and stuff are correct if you changed them.


The toolchain enables reflection and has a couple of statements at the end to try to enable CMake's
experimental module support as well. I'm using a bleeding edge CMake built from github. If you're
using a packaged one from your OS, you may need to change the uuid in CMAKE\_EXPERIMENTAL\_CXX\_IMPORT\_STD,
assuming your CMake supports modules at all. Your mileage may vary if you attempt to use import std
in the same project with reflection. It should work by the time the standard is finalized.


Using the toolchains enables testing multiple compilers just by varying the toolchain. The CMakeLists.txt
files in here are quite bare-bones, as the compiler config is being done in the toolchains.
