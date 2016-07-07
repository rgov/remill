project (remill)
cmake_minimum_required (VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH "/Users/user/src/llvm/build/bin")

include(LLVMUtils)

add_subdirectory(remill)
