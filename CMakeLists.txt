cmake_minimum_required(VERSION 3.17)
project(expert_system)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_STANDARD 17)

#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
#set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

add_executable(${PROJECT_NAME})

# replaced executable file to root dir
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

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

#add sources
set(YACC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include) #for copy yacc output .hpp
include_directories(include)
add_subdirectory(src)

#add tests
add_subdirectory(tests)
