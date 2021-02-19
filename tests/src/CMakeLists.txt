cmake_minimum_required(VERSION 3.17)

target_sources(expert_system_tests PUBLIC
        Find_All_Implies_Expressions_Tests.cpp
        Not_Correct_Input_Tests.cpp
        Correct_XOR_Operations_Tests.cpp
        And_Tests.cpp
        Or_Tests.cpp
        Xor_Tests.cpp
        Not_Tests.cpp
        Same_Conclusion_In_Multiple_Rules_Tests.cpp
        Parentheses_Tests.cpp)