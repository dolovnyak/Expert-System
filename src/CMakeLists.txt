cmake_minimum_required(VERSION 3.17)

target_sources(expert_system PUBLIC
        main.cpp
        imgui_test.cpp
        ExpertSystem.cpp
        NodeFactory.cpp
        )

add_subdirectory(Parse)