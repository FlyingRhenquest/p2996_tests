# Build reflection-based code with clang-p2996
#
# Note: I'm not extremely familiar with clang, so this could probably be better.
# You will probably need to use LD_LIBRARY_PATH to /usr/local/clang-p2996/lib in order
# to run anything you build with it, if you don't want to modify your system library
# paths.

# To build with this toolchain file, call "cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/this/file " ...
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER /usr/local/clang-p2996/bin/clang)
set(CMAKE_CXX_COMPILER /usr/local/clang-p2996/bin/clang++)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_INIT "-stdlib=libc++ -freflection -isystem /usr/local/clang-p2996/include/c++/v1")
# Note: Reflection and "import std" may or may not play well together.
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
# TODO: Find correct JSON file for the clang modules
set(CMAKE_CXX_STD_MODULES_JSON "/usr/local/clang-p2996/lib/x86_64-unknown-linux-gnu/libc++.modules.json")
# Point linker to clang library dir
set(CMAKE_EXE_LINKER_FLAGS_INIT "-L/usr/local/clang-p2996/lib -Wl,-rpath,/usr/local/clang-p2996/lib")
