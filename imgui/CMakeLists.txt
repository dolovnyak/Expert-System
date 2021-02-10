cmake_minimum_required(VERSION 3.17)
project(expert_system)

set(CMAKE_CXX_STANDARD 17)

add_library(imgui)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

find_package(OpenGL REQUIRED)

include_directories(imgui-github
        ${OPENGL_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIRS})

target_sources(imgui PUBLIC
        imgui-github/imgui_demo.cpp
        imgui-github/imgui_draw.cpp
        imgui-github/imgui_tables.cpp
        imgui-github/imgui_widgets.cpp
        imgui-github/imgui.cpp
        imgui-github/backends/imgui_impl_glfw.cpp)

target_link_libraries(imgui
        ${OPENGL_gl_LIBRARY}
        ${GLFW_LIBRARIES})