# This is a cmake toolchain to build with the experimental reflection support in
# gcc-16. I built the compiler from their github mirror into /usr/local/gcc-16.

# To build with this toolchain file, call "cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/this/file " ...
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER /usr/local/gcc-16/bin/gcc-16)
set(CMAKE_CXX_COMPILER /usr/local/gcc-16/bin/g++-16)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(WARNING "Reflection is enabled by this toolchain. If you see errors with import std, you will likely not be able to use it at the same time as reflection right now. You should still be able to use your own modules and import smaller parts of the std library.")
set(CMAKE_CXX_FLAGS_INIT "-freflection")
# -- Module Stuff --
# Your mileage may vary on how "import std;" and other module stuff works at
# this point, especially with reflection enabled. But I'll put it in here
# if you want to give it a try.
#
# CMAKE_EXPERIMENTAL_CXX_IMPORT_STD is needed to enable import std in cmake.
# The uuid may change depending on what version of CMake you're using. I'm
# using a bleeding edge build out of github and this is working for me right
# now.
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")

#
# You also need to tell it where the std modules json is
#
set(CMAKE_CXX_STD_MODULES_JSON "/usr/local/gcc-16/lib64/libstdc++.modules.json")
