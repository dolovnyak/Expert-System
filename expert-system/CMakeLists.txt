cmake_minimum_required(VERSION 3.17)
project(expert_system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_STANDARD 20)

add_executable(expert_system)

include_directories(include)

add_subdirectory(src)