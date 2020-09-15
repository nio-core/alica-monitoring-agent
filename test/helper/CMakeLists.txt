cmake_minimum_required(VERSION 3.0.0)
project(test-helper VERSION 0.1.0 LANGUAGES CXX)

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_CURRENT_SOURCE_DIR}/../../modules/alica-message-protos/src
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            alica-message-protos
            kj
)