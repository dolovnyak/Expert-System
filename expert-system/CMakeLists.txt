cmake_minimum_required(VERSION 3.17)
project(expert_system)

add_executable(expert_system)

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

# copy examples dir into cmake-build-debug/${CMAKE_CURRENT_BINARY_DIR}
add_custom_target(copy_examples ALL
        COMMAND cp -R ${CMAKE_CURRENT_SOURCE_DIR}/examples ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "added examples dir into cmake-build-debug"
        VERBATIM
)
add_dependencies(${PROJECT_NAME} copy_examples)

#add sources
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include) #for copy yacc output .hpp file
include_directories(include)
add_subdirectory(src)
