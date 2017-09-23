cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_COMPILER  /usr/bin/g++)
project(SimpleProject)

# LLVM
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Using : ${LLVM_LIBRARIES} ,${LLVM_LIBRARIES} ,${LLVM_LIBS}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

add_subdirectory(src)
