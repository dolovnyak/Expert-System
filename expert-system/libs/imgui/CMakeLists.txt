cmake_minimum_required(VERSION 3.17)
project(IMGUI)

target_sources(expert_system PUBLIC
        imgui-github/imgui.cpp
        imgui-github/imgui_demo.cpp
        imgui-github/imgui_draw.cpp
        imgui-github/imgui_widgets.cpp
        imgui-github/imgui_tables.cpp
        imgui-github/backends/imgui_impl_glfw.cpp
        imgui-github/backends/imgui_impl_opengl3.cpp
        )

set(${PROJECT_NAME}_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui-github/
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui-github/backends
        CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
        )

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})