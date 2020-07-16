cmake_minimum_required(VERSION 3.0.0)
project(task-allocation-monitor VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(modules/alica-message-protos)
add_subdirectory(modules/capnzero/capnzero)

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SRCS})
target_compile_definitions(${PROJECT_NAME} PRIVATE std_cxx_17)
