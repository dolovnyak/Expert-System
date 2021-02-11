cmake_minimum_required(VERSION 3.17)
project(IMGUI)
set(CMAKE_CXX_STANDARD 17)

target_sources(expert_system PUBLIC
        imgui-github/imgui.cpp
        imgui-github/imgui_demo.cpp
        imgui-github/imgui_draw.cpp
        imgui-github/imgui_widgets.cpp
        imgui-github/imgui_tables.cpp
        imgui-github/backends/imgui_impl_glfw.cpp
        imgui-github/backends/imgui_impl_opengl3.cpp
        )

#set(${PROJECT_NAME}_INCLUDE_DIRS
#        imgui-github/
#        imgui-github/backends
#        )
#
#include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})

include_directories(
        imgui-github/
        imgui-github/backends
)