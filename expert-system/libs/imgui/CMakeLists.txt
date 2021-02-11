cmake_minimum_required(VERSION 3.17)
project(IMGUI)
set(CMAKE_CXX_STANDARD 17)

target_sources(expert_system PUBLIC
        imgui.cpp
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_widgets.cpp
        imgui_tables.cpp
        imgui_internal.h
        backends/imgui_impl_glfw.cpp
        backends/imgui_impl_opengl3.cpp
        )

set(${PROJECT_NAME}_INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/backends
        CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})

