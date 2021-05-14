cmake_minimum_required(VERSION 3.15)
project(expert_system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_STANDARD 17)

################################################################################
# expert_system_lib target
################################################################################
set(EXPERT_SYSTEM_LIB "${PROJECT_NAME}_lib")
add_library(${EXPERT_SYSTEM_LIB}
        src/ExpertSystemLib/ExpertSystemData.cpp
        src/ExpertSystemLib/ExpertSystem.cpp
        src/ExpertSystemLib/Parse/Lexer.ll.cpp
        src/ExpertSystemLib/Parse/Grammar.yy.cpp
        src/ExpertSystemLib/Expressions/FactExpression.cpp
        src/ExpertSystemLib/Expressions/UnaryExpression.cpp
        src/ExpertSystemLib/Expressions/BinaryExpression.cpp
        src/ExpertSystemLib/Expressions/Expression.cpp
        )
INCLUDE(ParseGenerator.cmake)
target_include_directories(${EXPERT_SYSTEM_LIB} PUBLIC include)


################################################################################
# project target
################################################################################
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Visualizer.cpp
        )
target_link_libraries(${PROJECT_NAME} ${EXPERT_SYSTEM_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC include)

# replaced executable file to root dir
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )


################################################################################
# GLWF library to project target
################################################################################
add_subdirectory(libs/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} glfw)


################################################################################
# GLEW library to project target
################################################################################
if (INSTALL_DEPS)
    set(GLEW_LIB glew-glew-2.1.0)
    execute_process(
            COMMAND curl -O https://codeload.github.com/nigels-com/glew/tar.gz/glew-2.1.0
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)
    execute_process(
            COMMAND tar -xzvf glew-2.1.0
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)
    execute_process(
            COMMAND rm glew-2.1.0
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)
    execute_process(
            COMMAND make -C auto
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/libs/${GLEW_LIB})
    execute_process(
            COMMAND make -j4 glew.lib.static
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/libs/${GLEW_LIB})
endif()
add_definitions(-DGLEW_STATIC)
target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/libs/${GLEW_LIB}/include)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libs/${GLEW_LIB}/lib/libGLEW.a)


################################################################################
# IMGUI library
################################################################################
target_sources(${PROJECT_NAME} PUBLIC
        libs/imgui/imgui.cpp
        libs/imgui/imgui_demo.cpp
        libs/imgui/imgui_draw.cpp
        libs/imgui/imgui_widgets.cpp
        libs/imgui/imgui_tables.cpp
        libs/imgui/backends/imgui_impl_glfw.cpp
        libs/imgui/backends/imgui_impl_opengl3.cpp
        )
target_include_directories(${PROJECT_NAME} PUBLIC
        libs/imgui
        libs/imgui/backends
        )

################################################################################
# tests
################################################################################
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
# replaced executable file to root dir
set_target_properties(${EXPERT_SYSTEM_TESTS}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )
