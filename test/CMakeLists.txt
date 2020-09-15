cmake_minimum_required(VERSION 3.0.0)
project(task-allocation-monitor-test VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(helper)

find_package(rapidjson REQUIRED)
find_package(gtest REQUIRED)

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../modules/alica-message-protos/src
        ${CMAKE_CURRENT_SOURCE_DIR}/helper/include
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        alica_message_processor
        alica-message-protos
        rapidjson::rapidjson
        gtest::gtest
        kj
        test-helper
        )