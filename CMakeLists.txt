cmake_minimum_required(VERSION 3.4)
project(yFlux)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS} include)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++14)
set(SRC)
add_subdirectory(source)
add_executable(yfx ${SRC})

llvm_map_components_to_libnames(llvm_libs core mcjit native passes)
target_link_libraries(yfx ${llvm_libs})

