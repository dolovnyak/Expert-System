cmake_minimum_required(VERSION 3.17)

target_sources(expert_system_tests PUBLIC
        FindAllImpliesExpressionsTests.cpp
        AndTests.cpp
        OrTests.cpp
        XorTests.cpp
        NotTests.cpp
        SameConclusionInMultipleRulesTests.cpp
        ParenthesesTests.cpp)