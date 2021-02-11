cmake_minimum_required(VERSION 3.17)
project(expert_system)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_STANDARD 17)

add_executable(expert_system)

include_directories(include)
add_subdirectory(src)

# add GLWF
add_subdirectory(libs/glfw)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} glfw)

#add GLEW
add_definitions(-DGLEW_STATIC)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} GLEW::GLEW)

# add IMGUI
add_subdirectory(libs/imgui)
include_directories(${IMGUI_INCLUDE_DIRS})
