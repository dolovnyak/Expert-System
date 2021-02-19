cmake_minimum_required(VERSION 3.17)

target_sources(expert_system_tests PUBLIC
        Find_All_Implies_Expressions_Tests.cpp
        Not_Correct_Input_Tests.cpp
        Correct_XOR_Operations_Tests.cpp
        AndTests.cpp
        OrTests.cpp
        XorTests.cpp
        NotTests.cpp
        SameConclusionInMultipleRulesTests.cpp
        ParenthesesTests.cpp)