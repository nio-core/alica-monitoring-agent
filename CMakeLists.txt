cmake_minimum_required(VERSION 3.0.0)
project(task-allocation-monitor VERSION 0.1.0 LANGUAGES CXX)

execute_process(COMMAND bash -c "conan install .. -if ${CMAKE_CURRENT_BINARY_DIR}")
include("${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake")
find_package(rapidjson REQUIRED)

add_subdirectory(modules/alica-message-protos)
add_subdirectory(modules/capnzero/capnzero)

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SRCS})
target_compile_definitions(${PROJECT_NAME} PRIVATE std_cxx_17)
target_include_directories(${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/modules/capnzero/capnzero/include
            ${CMAKE_CURRENT_SOURCE_DIR}/modules/alica-message-protos/src
        )
target_link_libraries(${PROJECT_NAME}
        PRIVATE
            capnzero
            alica-message-protos
            rapidjson::rapidjson
        )