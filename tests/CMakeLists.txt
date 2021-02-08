cmake_minimum_required(VERSION 3.17)
project(expert_system)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(expert_system_tests)

include_directories(include
        ../expert-system/include)

target_link_libraries(expert_system_tests
        GTest::GTest
        GTest::Main)

add_subdirectory(src)