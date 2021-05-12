cmake_minimum_required(VERSION 3.15)
project(expert_system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_STANDARD 17)

execute_process(COMMAND git submodule update --init --recursive)

# add expert eystem lib
set(EXPERT_SYSTEM_LIB "${PROJECT_NAME}_lib")
add_library(${EXPERT_SYSTEM_LIB})
set(YACC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include) #for copy yacc output .hpp
target_include_directories(${EXPERT_SYSTEM_LIB} PUBLIC include)
add_subdirectory(src)

# add GLWF to lib
add_subdirectory(libs/glfw)
target_include_directories(${EXPERT_SYSTEM_LIB} PUBLIC ${GLFW_INCLUDE_DIRS})
target_link_libraries(${EXPERT_SYSTEM_LIB} glfw)

#add GLEW to lib
execute_process(COMMAND brew install glew)
add_definitions(-DGLEW_STATIC)
find_package(GLEW REQUIRED)
target_include_directories(${EXPERT_SYSTEM_LIB} PUBLIC ${GLEW_INCLUDE_DIRS})
target_link_libraries(${EXPERT_SYSTEM_LIB} GLEW::GLEW)

# add IMGUI to lib
target_sources(${EXPERT_SYSTEM_LIB} PUBLIC
        libs/imgui/imgui.cpp
        libs/imgui/imgui_demo.cpp
        libs/imgui/imgui_draw.cpp
        libs/imgui/imgui_widgets.cpp
        libs/imgui/imgui_tables.cpp
        libs/imgui/backends/imgui_impl_glfw.cpp
        libs/imgui/backends/imgui_impl_opengl3.cpp
        )
target_include_directories(${EXPERT_SYSTEM_LIB} PUBLIC
        libs/imgui/imgui-github/
        libs/imgui/imgui-github/backends
        )

# add project target
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${EXPERT_SYSTEM_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC include)

# replaced executable file to root dir
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )


#add tests
set(EXPERT_SYSTEM_TESTS ${PROJECT_NAME}_tests)
add_subdirectory(libs/googletest)
add_executable(${EXPERT_SYSTEM_TESTS}
        tests/Find_All_Implies_Expressions_Tests.cpp
        tests/Not_Correct_Input_Tests.cpp
        tests/Correct_XOR_Operations_Tests.cpp
        tests/And_Tests.cpp
        tests/Or_Tests.cpp
        tests/Xor_Tests.cpp
        tests/Not_Tests.cpp
        tests/Same_Conclusion_In_Multiple_Rules_Tests.cpp
        tests/Parentheses_Tests.cpp)
target_include_directories(${EXPERT_SYSTEM_TESTS} PUBLIC
        libs/googletest/googletest/include
        include)
target_link_libraries(${EXPERT_SYSTEM_TESTS}
        gtest
        gtest_main
        ${EXPERT_SYSTEM_LIB}
        )
