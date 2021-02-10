cmake_minimum_required(VERSION 3.17)

target_sources(expert_system PUBLIC
        main.cpp)
target_link_libraries(expert_system
        imgui)