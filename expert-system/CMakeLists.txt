cmake_minimum_required(VERSION 3.17)
project(expert_system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_STANDARD 20)

add_executable(expert_system)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
        include
        ../imgui/imgui-github
        ../imgui/imgui-github/backends
        ${OPENGL_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS})
add_subdirectory(src)

target_link_libraries(expert_system
        imgui
        glfw
        GLEW::GLEW
        OpenGL::GL)