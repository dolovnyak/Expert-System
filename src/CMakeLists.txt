cmake_minimum_required(VERSION 3.17)

target_sources(expert_system PUBLIC
        main.cpp
        ExpertSystem.cpp
        ExpertSystemData.cpp
        Visualizer.cpp
        )

add_subdirectory(Expressions)
add_subdirectory(Parse)