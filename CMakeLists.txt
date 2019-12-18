cmake_minimum_required(VERSION 3.14)
project(NetSim)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(include)

set(SOURCE_FILES
        src/package.cpp)

add_executable(NetSim ${SOURCE_FILES} main.cpp)

