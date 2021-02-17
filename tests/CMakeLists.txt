cmake_minimum_required(VERSION 3.17)
project(expert_system)

find_package(GTest REQUIRED)

add_executable(expert_system_tests
        ../src/ExpertSystem.cpp
        ../src/ExpertSystemData.cpp
        ../src/Expressions/Expression.cpp
        ../src/Expressions/BinaryExpression.cpp
        ../src/Expressions/UnaryExpression.cpp
        ../src/Expressions/FactExpression.cpp
        ../src/Parse/Grammar.yy.cpp
        ../src/Parse/Lexer.ll.cpp
        )

include_directories(include
        ../expert-system/include)

target_link_libraries(expert_system_tests
        GTest::GTest
        GTest::Main)

add_subdirectory(src)
