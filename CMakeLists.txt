cmake_minimum_required(VERSION 4.2)

project(p2996Tests LANGUAGES CXX)

OPTION(BUILD_REF_MEMBERS "Build ref members test that throws an internal exception" OFF)

if (NOT DEFINED BUILD_REF_MEMBERS)
  set(BUILD_REF_MEMBERS OFF)
endif()

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(test)
