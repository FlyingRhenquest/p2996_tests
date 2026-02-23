cmake_minimum_required(VERSION 4.2)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest REQUIRED)
include(GoogleTest)

set(TEST_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/Annotations.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/EnumToString.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PrivateMemberReflection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/OperatorRefTests.cpp
)

add_executable(test
  ${TEST_SRC}
)

add_executable(standalone
  ${CMAKE_CURRENT_SOURCE_DIR}/SimpleStringAnnotation.cpp
)

# Turning this on currently fails with an internal compiler error
set(COMPILE_DEF_LIST)
if (BUILD_REF_MEMBERS)
  list(APPEND COMPILE_DEF_LIST "BUILD_REF_MEMBERS")
endif()

target_compile_definitions(test PUBLIC "${COMPILE_DEF_LIST}")

target_link_libraries(test PUBLIC
  GTest::GTest
  GTest::Main
)

target_compile_options(standalone PRIVATE -Wall -Wextra -save-temps -fno-strict-aliasing -fwrapv -fno-aggressive-loop-optimizations )
