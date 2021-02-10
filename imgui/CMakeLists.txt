cmake_minimum_required(VERSION 3.17)
project(expert_system)

set(CMAKE_CXX_STANDARD 17)

add_library(imgui)

include_directories(imgui-github)
target_sources(imgui PUBLIC
        imgui-github/imgui_demo.cpp
        imgui-github/imgui_draw.cpp
        imgui-github/imgui_tables.cpp
        imgui-github/imgui_widgets.cpp
        imgui-github/imgui.cpp)