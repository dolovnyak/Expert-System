cmake_minimum_required(VERSION 3.17)

target_sources(expert_system PUBLIC
        main.cpp
        imgui_graph_test.cpp
        ExpertSystem.cpp
        MainExpressionsList.cpp
        ExpressionSharedPtr.cpp
        Visualizer.cpp
        )

add_subdirectory(Expressions)
add_subdirectory(Parse)